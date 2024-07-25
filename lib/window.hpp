//
// Created by sky on 21.07.24.
//

//
// 0.1: support for x11 (e.g. linux)
// 0.2: support for win32 (windows)
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
        enum class mouse_button : int32 {
            left = 0,
            right = 1,
            middle = 2,
            x1 = 3,
            x2 = 4,
            count = 5
        };

        enum class keyboard_keys : int32 {

        };

        class window_data {
            vec2i mouse_pos{};
            vec2i window_size{};
            vec2i window_pos{};
            int32 mouse_wheel = 0;

            bitlist<256> keyboard{};
            bitlist<static_cast<uint64>(mouse_button::count)> mouse_buttons{};

            bool mouse_focus : 1 = false;
            bool key_focus   : 1 = false;

        public:
            [[nodiscard]] const vec2i& get_mouse() const noexcept {
                return mouse_pos;
            }

            [[nodiscard]] const vec2i& get_size() const noexcept {
                return window_size;
            }

            [[nodiscard]] const vec2i& get_pos() const noexcept {
                return window_pos;
            }

            [[nodiscard]] int32 get_mouse_wheel() const noexcept {
                return mouse_wheel;
            }

            [[nodiscard]] bool get_key_pressed(const int32 key_code) const noexcept {
                return keyboard.get(key_code);
            }

            [[nodiscard]] bool get_key_released(const int32 key_code) const noexcept {
                return !keyboard.get(key_code);
            }

            [[nodiscard]] bool get_mouse_button_pressed(const mouse_button button) const noexcept {
                return mouse_buttons.get(static_cast<uint32>(button));
            }

            [[nodiscard]] bool get_mouse_button_released(const mouse_button button) const noexcept {
                return !mouse_buttons.get(static_cast<uint32>(button));
            }

            [[nodiscard]] bool get_mouse_focus() const noexcept {
                return mouse_focus;
            }

            [[nodiscard]] bool get_key_focus() const noexcept {
                return key_focus;
            }

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

            void update_window_pos(const int32 x, const int32 y) noexcept {
                window_pos.x = x;
                window_pos.y = y;
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

                static LRESULT CALLBACK global_window_event(HWND window, UINT msg, WPARAM w, LPARAM l) noexcept {
                    // todo
                }

                LRESULT CALLBACK window_event(UINT msg, WPARAM w, LPARAM l) noexcept {
                    switch (msg) {
                        case WM_MOUSEMOVE: data.update_mouse(l & 0xFFFF, (l >> 16) & 0xFFFF); break;
                        case WM_MOVE: data.update_window_pos(l & 0xFFFF, (l >> 16) & 0xFFFF); break;
                        case WM_SIZE: data.update_window_size(l & 0xFFFF, (l >> 16) & 0xFFFF); break;
                        case WM_MOUSEWHEEL: data.update_mouse_wheel(GET_WHEEL_DELTA_WPARAM(w)); break;
                        case WM_MOUSELEAVE: data.update_mouse_focus(false); break;
                        case WM_SETFOCUS: data.update_key_focus(true); break;
                        case WM_KILLFOCUS: data.update_key_focus(false); break;
                        case WM_SYSKEYDOWN: [[fallthrough]]
                        case WM_KEYDOWN: data.update_key_state(w, true); break;
                        case WM_SYSKEYUP: [[fallthrough]]
                        case WM_KEYUP: data.update_key_state(w, false); break;
                        case WM_LBUTTONDOWN: data.update_mouse_state(0, true); break;
                        case WM_LBUTTONUP: data.update_mouse_state(0, false); break;
                        case WM_RBUTTONDOWN: data.update_mouse_state(1, true); break;
                        case WM_RBUTTONUP: data.update_mouse_state(1, false); break;
                        case WM_MBUTTONDOWN: data.update_mouse_state(2, true); break;
                        case WM_MBUTTONUP: data.update_mouse_state(2, false); break;
                        case WM_CLOSE: terminate(); return 0;
                        case WM_DESTROY: PostQuitMessage(0); DestroyWindow(native_window); return 0;
                    }
                    return DefWindowProc(native_window, msg, w, l);
                }
            #elif defined(__linux__)
                Display* display = nullptr;
                Window window_root = 0;
                Window native_window = 0;
                Colormap colormap = 0;
                XSetWindowAttributes attributes{};
            #endif
            window_data data;
            bool is_open : 1 = false;

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

            // mouse & keyboard

            [[nodiscard]] const vec2i& mouse_pos() const noexcept {
                return data.get_mouse();
            }

            [[nodiscard]] const vec2i& window_size() const noexcept {
                return data.get_size();
            }

            [[nodiscard]] const vec2i& window_pos() const noexcept {
                return data.get_pos();
            }

            [[nodiscard]] int32 mouse_wheel() const noexcept {
                return data.get_mouse_wheel();
            }

            [[nodiscard]] bool key_pressed(const int32 key_code) const noexcept {
                return data.get_key_pressed(key_code);
            }

            [[nodiscard]] bool key_released(const int32 key_code) const noexcept {
                return data.get_key_released(key_code);
            }

            [[nodiscard]] bool mouse_pressed(const mouse_button button) const noexcept {
                return data.get_mouse_button_pressed(button);
            }

            [[nodiscard]] bool mouse_released(const mouse_button button) const noexcept {
                return data.get_mouse_button_released(button);
            }

            [[nodiscard]] bool mouse_focus() const noexcept {
                return data.get_mouse_focus();
            }

            [[nodiscard]] bool key_focus() const noexcept {
                return data.get_key_focus();
            }
        };

        #ifdef _WIN32
            inline bool window::cleanup() noexcept {
                PostMessage(native_window, WM_DESTROY, 0, 0);
                return true;
            }

            inline bool window::create(const vec2i& pos, const vec2i& size) noexcept {
                WNDCLASS wclass{};
                wclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
                wclass.hCursor = LoadCursor(NULL, IDC_ARROW);
                wclass.style = CS_HREDRAW | CS_VREDRAW;
                wclass.hInstance = GetModuleHandle(nullptr);
                wclass.lpfnWndProc = global_window_event;
                wclass.cbClsExtra = 0;
                wclass.cbWndExtra = 0;
                wclass.lpszMenuName = nullptr;
                wclass.hbrBackground = nullptr;
                wclass.lpszClassName = TEXT("sky64redstone/window");

                ATOM win_atom = RegisterClass(&wclass);

                DWORD exstyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
                DWORD style = WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_THICKFRAME;

                // calculate client size
                RECT rect = { 0, 0, size.x, size.y };
                AdjustWindowRectEx(&rect, style, FALSE, exstyle);
                size.x = rect.right - rect.left;
                size.y = rect.bottom - rect.top;

                native_window = CreateWindowEx(
                    exstyle,
                    (LPCTSTR)((LPCTSTR)(0) | win_atom),
                    TEXT("github.com/sky64redstone"),
                    style,
                    pos.x, pos.y,
                    size.x, size.y,
                    NULL, NULL,
                    wclass.hInstance,
                    this
                );

                return true;
            }

            inline bool window::set_title(const char* title) const noexcept {
                #ifdef UNICODE
                    return SetWindowText(native_window, convert_str_to_wstr(title));
                #else
                    return SetWindowText(native_window, title);
                #endif
            }

            inline bool window::start_system_event_loop() noexcept {
                MSG msg{};
                while (GetMessage(&msg, nullptr, 0, 0) > 0) {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
                return true;
            }

            inline bool window::handle_system_events() noexcept {
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
                    case EnterNotify:
                    case LeaveNotify: {
                        data.update_mouse_focus(event.type == EnterNotify);
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
