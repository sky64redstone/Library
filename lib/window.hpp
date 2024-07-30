//
// Created by sky on 21.07.24.
//

//
// 0.1: support for x11 (e.g. linux)
// 0.2: support for win32 (windows)
// 0.3: support for opengl 1.0 for x11
//

//
// vulkan support:
// https://registry.khronos.org/vulkan/specs/1.0-wsi_extensions/html/vkspec.html#platformCreateSurface_xlib
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
        #include <X11/Xutil.h>

        #include <GL/gl.h>
        #include <GL/glx.h>
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
                static ATOM win_atom;
                HWND native_window = nullptr;
                TCHAR* title = nullptr;

                static wchar_t* convert_str_to_wstr(char* str) noexcept;

                static LRESULT CALLBACK global_window_event(HWND wnd, const UINT msg, const WPARAM w, const LPARAM l) noexcept;

                LRESULT CALLBACK window_event(const UINT msg, const WPARAM w, const LPARAM l) noexcept;
            #elif defined(__linux__)
                Display* display = nullptr;
                Window window_root = 0;
                Window native_window = 0;
                Colormap colormap = 0;
                XSetWindowAttributes attributes{};
                XVisualInfo* visual_info = nullptr;
            #endif
            window_data data;
            bool is_open : 1 = false;
            bool opengl : 1 = false;

        public:
            // Destroys the window and frees up resources
            bool cleanup() noexcept;

            // Creates the window at pos with the Size: size
            bool create(const vec2i& pos, const vec2i& size, bool opengl = false) noexcept;

            // Sets the title-bar-text of the window
            bool set_title(const char* title) const noexcept;

            // Needs to be called in the same thread
            // where the create function was called.
            // And has only to be called once (before starting a game loop)
            static bool start_system_event_loop() noexcept;

            // Needs to be called every game tick
            // or every time you want to update sth
            bool handle_system_events() noexcept;

            [[nodiscard]] bool open() const noexcept { return is_open; }

            void terminate() noexcept { is_open = false; }

            bool set_size(const vec2i& size) const noexcept;

            bool set_pos(const vec2i& pos) const noexcept;

            [[nodiscard]] bool has_opengl() const noexcept { return opengl; }

            #ifdef _WIN32
                [[nodiscard]] HWND& native() noexcept { reutrn native_window; }
            #elif defined(__linux__)
                [[nodiscard]] Window& native() noexcept { return native_window; }
                [[nodiscard]] Window& native_root() noexcept { return window_root; }
                [[nodiscard]] Display* native_display() const noexcept { return display; }
                [[nodiscard]] XVisualInfo* native_visual_info() const noexcept { return visual_info; }
            #endif

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
            inline wchar_t* window::convert_str_to_wstr(char* str) noexcept {
                #ifdef __MINGW32__
                    uint64 str_len = lstrlenA(str);
                    auto* buffer = new wchar_t[str_len + 1];
                    mbstowcs(buffer, str, str_len);
                    buffer[str_len] = L'\0';
                #else
                    int str_len = MultiByteToWideChar(CP_UTF8, 0, str, -1, nullptr, 0);
                    auto* buffer = new wchar_t[str_len];
                    MultiByteToWideChar(CP_UTF8, 0, str, -1, buffer, count);
                #endif
                return buffer;
            }

            inline LRESULT CALLBACK window::global_window_event(HWND wnd, const UINT msg, const WPARAM w, const LPARAM l) noexcept {
                window* wnd_ptr;

                if (msg == WM_NCCREATE) {
                    const auto* create = reinterpret_cast<CREATESTRUCT*>(l);

                    wnd_ptr = static_cast<window*>(create->lpCreateParams);

                    if (wnd_ptr) {
                        SetWindowLongPtr(wnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(wnd_ptr));

                        wnd_ptr->native_window = wnd;
                    }
                } else {
                    wnd_ptr = reinterpret_cast<window*>(GetWindowLongPtr(wnd, GWLP_USERDATA));
                }

                if (wnd_ptr) {
                    return wnd_ptr->window_event(msg, w, l);
                }

                return DefWindowProc(wnd, msg, w, l);
            }

            inline LRESULT CALLBACK window::window_event(const UINT msg, const WPARAM w, const LPARAM l) noexcept {
                switch (msg) {
                    case WM_MOUSEMOVE:      data.update_mouse(LOWORD(l), HIWORD(l)); return 0;
                    case WM_MOVE:           data.update_window_pos(LOWORD(l), HIWORD(l)); return 0;
                    case WM_SIZE:           data.update_window_size(LOWORD(l), HIWORD(l)); return 0;
                    case WM_MOUSEWHEEL:     data.update_mouse_wheel(GET_WHEEL_DELTA_WPARAM(w)); return 0;
                    case WM_MOUSELEAVE:     data.update_mouse_focus(false); return 0;
                    case WM_SETFOCUS:       data.update_key_focus(true); return 0;
                    case WM_KILLFOCUS:      data.update_key_focus(false); return 0;
                    case WM_SYSKEYDOWN:
                    case WM_KEYDOWN:        data.update_key_state(static_cast<int32>(w), true); return 0;
                    case WM_SYSKEYUP:
                    case WM_KEYUP:          data.update_key_state(static_cast<int32>(w), false); return 0;
                    case WM_LBUTTONDOWN:    data.update_mouse_state(0, true); return 0;
                    case WM_LBUTTONUP:      data.update_mouse_state(0, false); return 0;
                    case WM_RBUTTONDOWN:    data.update_mouse_state(1, true); return 0;
                    case WM_RBUTTONUP:      data.update_mouse_state(1, false); return 0;
                    case WM_MBUTTONDOWN:    data.update_mouse_state(2, true); return 0;
                    case WM_MBUTTONUP:      data.update_mouse_state(2, false); return 0;
                    case WM_CLOSE:          terminate(); return 0;
                    case WM_DESTROY:        PostQuitMessage(0); return 0;
                    default: break;
                }
                return DefWindowProc(native_window, msg, w, l);
            }

            inline bool window::cleanup() noexcept {
                PostMessage(native_window, WM_DESTROY, 0, 0);

                is_open = false;

                return true;
            }

            ATOM window::win_atom = 0;

            inline bool window::create(const vec2i& pos, const vec2i& size) noexcept {
                if (win_atom == 0) [[unlikely]] { // after the first time it's not reachable
                    WNDCLASS wclass{};
                    wclass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
                    wclass.hCursor = LoadCursor(nullptr, IDC_ARROW);
                    wclass.style = CS_HREDRAW | CS_VREDRAW; // redraw on size/move
                    wclass.hInstance = GetModuleHandle(nullptr);
                    wclass.lpfnWndProc = global_window_event;
                    wclass.cbClsExtra = 0;
                    wclass.cbWndExtra = 0;
                    wclass.lpszMenuName = nullptr;
                    wclass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
                    wclass.lpszClassName = TEXT("sky64redstone/window");

                    win_atom = RegisterClass(&wclass);
                }

                constexpr DWORD exstyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
                constexpr DWORD style = WS_TILEDWINDOW | WS_VISIBLE;

                // calculate client size
                RECT rect = { 0, 0, size.x, size.y };
                AdjustWindowRectEx(&rect, style, FALSE, exstyle);
                const int32 w = rect.right - rect.left;
                const int32 h = rect.bottom - rect.top;

                native_window = CreateWindowEx(
                    exstyle,
                    MAKEINTATOM(win_atom),
                    TEXT("github.com/sky64redstone"),
                    style,
                    pos.x, pos.y,
                    w, h,
                    nullptr, nullptr,
                    GetModuleHandle(nullptr),
                    this
                );

                is_open = true;
                this->opengl = opengl;

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

            inline bool window::set_size(const vec2i& size) const noexcept {
                constexpr UINT flags = SWP_NOMOVE | SWP_NOZORDER;
                BOOL result = SetWindowPos(native_window, nullptr, 0, 0, size.x, size.y, flags);
                return result != 0;
            }

            inline bool window::set_pos(const vec2i& pos) const noexcept {
                constexpr UINT flags = SWP_NOSIZE | SWP_NOZORDER;
                BOOL result = SetWindowPos(native_window, nullptr, pos.x, pos.y, 0, 0, flags);
                return result != 0;
            }

        #elif defined(__linux__)
            inline bool window::cleanup() noexcept {
                XDestroyWindow(display, native_window);

                is_open = false;

                return true;
            }

            inline bool window::create(const vec2i& pos, const vec2i& size, const bool opengl) noexcept {
                XInitThreads();

                display = XOpenDisplay(nullptr);
                window_root = DefaultRootWindow(display);

                if (opengl) {
                    GLint gl_attr[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
                    visual_info = glXChooseVisual(display, 0, gl_attr);
                    colormap = XCreateColormap(display, window_root, visual_info->visual, AllocNone);
                    attributes.colormap = colormap;
                }

                attributes.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
                    ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask | StructureNotifyMask;

                native_window = XCreateWindow(
                    display,
                    window_root,
                    pos.x, pos.y,
                    size.x, size.y,
                    0, // border width
                    opengl ? visual_info->depth : 0,
                    InputOutput,
                    opengl ? visual_info->visual : nullptr,
                    CWColormap | CWEventMask,
                    &attributes
                );

                Atom wmDelete = XInternAtom(display, "WM_DELETE_WINDOW", true);
                XSetWMProtocols(display, native_window, &wmDelete, 1);

                XMapWindow(display, native_window);
                XStoreName(display, native_window, "github.com/sky64redstone");

                is_open = true;
                this->opengl = opengl;

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

            inline bool window::set_size(const vec2i& size) const noexcept {
                const int result = XResizeWindow(display, native_window, size.x, size.y);
                return result != BadValue && result != BadWindow;
            }

            inline bool window::set_pos(const vec2i& pos) const noexcept {
                const int result = XMoveWindow(display, native_window, pos.x, pos.y);
                return result != BadWindow;
            }

        #endif
    }

#endif //WINDOW_HPP
