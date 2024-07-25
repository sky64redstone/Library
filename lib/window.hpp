//
// Created by sky on 21.07.24.
//

#ifndef WINDOW_HPP
    #define WINDOW_HPP

    #ifdef _WIN32
        #include <windows.h>

        #if !defined(__MINGW32__)
            #pragma comment(lib, "user32.lib")
            #pragma comment(lib, "gdi32.lib")
        #endif

    #elif defined(__linux__)
        #include <X11/X.h>
        #include <X11/Xlib.h>
    #endif

    #include "vec.hpp"
    #include "bit.hpp"

    namespace lib {
        enum class mouse : int32 {
            left = 0,
            right = 1,
            middle = 2,
            x1 = 3,
            x2 = 4,
            count = 5
        };

        class window_data {
            vec2i mouse_pos{};
            vec2i window_size{};
            int32 mouse_wheel = 0;

            bitlist<256> keyboard{};
            bitlist<static_cast<uint64>(mouse::count)> mouse_buttons{};

            bool mouse_focus : 1 = false;
            bool key_focus   : 1 = false;

        public:
            void update_mouse(const int32 x, const int32 y) noexcept {
                mouse_pos.x = x;
                mouse_pos.y = y;
            }

            void update_mouse_wheel(const int32 delta) noexcept {
                mouse_wheel += delta;
            }

            void reset_mouse_wheel() noexcept {
                mouse_wheel = 0;
            }

            void update_window_size(const int32 width, const int32 height) noexcept {
                window_size.x = width;
                window_size.y = height;
            }

            void update_mouse_state(const int32 button, const bool state) noexcept {
                mouse_buttons[button] = state;
            }

            void update_key_state(const int32 button, const bool state) noexcept {
                // todo create a keymap
                keyboard[button] = state;
            }

            void update_mouse_focus(const bool state) noexcept {
                mouse_focus = state;
            }

            void update_key_focus(const bool state) noexcept {
                key_focus = state;
            }
        };

        class window {
#ifdef _WIN32
            HWND native_window = nullptr;
            wchar_t* title;

            static wchar_t* convert_str_to_wstr(char* str) {
#ifdef __MINGW32__
                uint64 str_len = lstrlenA(str);
                wchar_t* buffer = new wchar_t[str_len + 1];
                mbstowcs(buffer, str, str_len);
                buffer[str_len] = L'\0';
#else
                int str_len = MultiByteToWideChar(CP_UTF8, 0, str, -1, nullptr, 0);
                wchar_t* buffer = new wchar_t[str_len];
                MultiByteToWideChar(CP_UTF8, 0, str, -1, buffer, count);
#endif
                return buffer;
            }
#elif defined(__linux__)
            Display* display = nullptr;
            Window window_root = 0;
            Window native_window = 0;
            Colormap colormap = 0;
            XSetWindowAttributes attributes{};
#endif
            window_data data;
            bool is_open = false;

        public:
            // Destroys the window and frees up resources
            bool cleanup() noexcept;

            // Creates the window at pos with the Size: size
            bool create(const vec2i& pos, const vec2i& size) noexcept;

            // Sets the title-bar-text of the window
            bool set_title(const char* title) const noexcept;

            // Needs to be called in the same thread
            // where the create function was called.
            // And has only to be called once (before starting a game loop)
            bool start_system_event_loop() noexcept;

            // Needs to be called every game tick
            // or every time you want to update sth
            bool handle_system_events() noexcept;

            [[nodiscard]] bool open() const noexcept { return is_open; }

            void terminate() noexcept { is_open = false; }
        };

        #ifdef _WIN32
            inline bool window::cleanup() noexcept {
                PostMessage(native_window, WM_DESTROY, 0, 0);
                return true;
            }

            inline bool window::create(const vec2i& pos, const vec2i& size) noexcept {
                return true;
            }
        #elif defined(__linux__)
            inline bool window::cleanup() noexcept {
                XDestroyWindow(display, native_window);

                is_open = false;

                return true;
            }

            inline bool window::create(const vec2i& pos, const vec2i& size) noexcept {
                XInitThreads();

                display = XOpenDisplay(nullptr);
                window_root = DefaultRootWindow(display);
                attributes.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
                    ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask | StructureNotifyMask;

                native_window = XCreateWindow(display, window_root, pos.x, pos.y, size.x, size.y, 0, 0, InputOutput, nullptr, CWColormap | CWEventMask, &attributes);

                Atom wmDelete = XInternAtom(display, "WM_DELETE_WINDOW", true);
                XSetWMProtocols(display, native_window, &wmDelete, 1);

                XMapWindow(display, native_window);
                XStoreName(display, native_window, "github.com/sky64redstone");

                is_open = true;

                return true;
            }

            inline bool window::set_title(const char* title) const noexcept {
                XStoreName(display, native_window, title);
                return true;
            }

            inline bool window::start_system_event_loop() noexcept {
                return true;
            }

            inline bool window::handle_system_events() noexcept {
                XEvent event;

                while (XPending(display)) {
                    XNextEvent(display, &event);

                    switch (event.type) {
                    case Expose: {
                        XWindowAttributes attr;
                        XGetWindowAttributes(display, native_window, &attr);
                        data.update_window_size(attr.width, attr.height);
                        break;
                    }
                    case ConfigureNotify: {
                        data.update_window_size(event.xconfigure.width, event.xconfigure.height);
                        break;
                    }
                    case KeyPress:
                    case KeyRelease: {
                        const KeySym sym = XLookupKeysym(&event.xkey, 0);
                        data.update_key_state(static_cast<int32>(sym), event.type == KeyPress);
                        break;
                    }
                    case ButtonPress:
                    case ButtonRelease: {
                        switch (event.xbutton.button) {
                        case 1: { data.update_mouse_state(0, event.type == ButtonPress); break; }
                        case 2: { data.update_mouse_state(1, event.type == ButtonPress); break; }
                        case 3: { data.update_mouse_state(2, event.type == ButtonPress); break; }
                        case 4: { data.update_mouse_wheel(120); break; }
                        case 5: { data.update_mouse_wheel(-120); break; }
                        default: break;
                        }
                    }
                    case MotionNotify: {
                        data.update_mouse(event.xmotion.x, event.xmotion.y);
                        break;
                    }
                    case FocusIn:
                    case FocusOut: {
                        data.update_key_focus(event.type == FocusIn);
                        break;
                    }
                    case ClientMessage: {
                        this->terminate();
                    }
                    default: break;
                    }
                }

                return true;
            }
        #endif
    }

#endif //WINDOW_HPP
