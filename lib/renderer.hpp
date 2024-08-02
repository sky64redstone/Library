//
// Created by sky on 29.07.24.
//

//
// 0.1: lib::renderer
// 0.1: lib::renderer_opengl10
//

#ifndef RENDERER_HPP
    #define RENDERER_HPP

    #ifdef _WIN32
        #include <dwmapi.h>
        #include <GL/gl.h>

        #if !defined(__MINGW32__)
            #pragma comment(lib, "Dwmapi.lib")
        #endif

        namespace lib {
            using opengl_swap_interval = BOOL(WINAPI*)(int interval);
            using opengl_device_context = HDC;
        }
    #elif defined(__linux__)
        #include <GL/gl.h>
        #include <GL/glx.h>

        namespace lib {
            using opengl_swap_interval = int(*)(Display* display, GLXDrawable drawable, int interval);
            using opengl_device_context = GLXContext;
        }
    #endif

    #include "types.hpp"
    #include "window.hpp"
    #include "color.hpp"

    namespace lib {
        class renderer {
        public:
            virtual ~renderer() = default;

            // create the renderer in the same thread as you render the scene
            virtual bool create(window& wnd, bool vsync) noexcept = 0;
            virtual bool destroy() noexcept = 0;
            virtual bool swap_buffers() noexcept = 0;
            virtual void prepare_drawing() noexcept = 0;
            virtual void update_viewport(const vec2i& pos, const vec2i& size) noexcept = 0;
        };

        // OpenGL 1.0 renderer
        class renderer_opengl10 final : public renderer {
        private:
            #ifdef _WIN32
                HGLRC render_context{};
            #elif defined(__linux__)
                Display* display = nullptr;
                Window* native_window = nullptr;
                XVisualInfo* visual_info = nullptr;
            #endif

            opengl_device_context device_context{};
            opengl_swap_interval swap_interval = nullptr;
            bool vsync : 1 = false;

        public:
            ~renderer_opengl10() noexcept override;

            bool create(window& wnd, bool vsync) noexcept override;
            bool destroy() noexcept override;

            bool swap_buffers() noexcept override;
            void prepare_drawing() noexcept override;
            void update_viewport(const vec2i& pos, const vec2i& size) noexcept override;
            void set_swap_interval(opengl_swap_interval swap_interval) noexcept;

            void clear_buffer(const color4& color, bool depth) noexcept;
            void draw_layer_quad(const vec2f& offset, const vec2f& scale, const color4& color) noexcept;
        };

        template <typename renderer_>
        constexpr bool is_renderer = is_any_of_type<renderer_, renderer, renderer_opengl10>;

        template <typename renderer_>
        constexpr bool is_opengl_renderer = is_any_of_type<renderer_, renderer_opengl10>;

        template <typename renderer_>
        constexpr bool is_opengl10_renderer = is_same_type<renderer_, renderer_opengl10>;

        // Implementations

        inline void renderer_opengl10::prepare_drawing() noexcept {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }

        inline void renderer_opengl10::update_viewport(const vec2i &pos, const vec2i &size) noexcept {
            glViewport(pos.x, pos.y, size.x, size.y);
        }

        inline void renderer_opengl10::set_swap_interval(const opengl_swap_interval swap_interval) noexcept {
            this->swap_interval = swap_interval;
        }

        inline void renderer_opengl10::clear_buffer(const color4& color, const bool depth) noexcept {
            glClearColor(color.float_r(), color.float_g(), color.float_b(), color.float_a());
            glClear(GL_COLOR_BUFFER_BIT | (depth ? GL_DEPTH_BUFFER_BIT : 0));
        }

        inline void renderer_opengl10::draw_layer_quad(const vec2f& offset, const vec2f& scale, const color4& color) noexcept {
            glBegin(GL_QUADS);

            glColor4ub(color.r, color.g, color.b, color.a);

            glTexCoord2f(offset.x, scale.y + offset.y);
            glVertex3f(-1.f, -1.f, 0.f);

            glTexCoord2f(offset.x, offset.y);
            glVertex3f(-1.f, 1.f, 0.f);

            glTexCoord2f(scale.x + offset.x, offset.y);
            glVertex3f(1.f, 1.f, 0.f);

            glTexCoord2f(scale.x + offset.x, scale.y + offset.y);
            glVertex3f(1.f, -1.f, 0.f);

            glEnd();
        }

        #ifdef _WIN32
            inline renderer_opengl10::~renderer_opengl10() noexcept {
                destroy();
            }

            inline bool renderer_opengl10::create(window& wnd, const bool vsync) noexcept {
                if (!wnd.has_opengl())
                    return false;

                device_context = GetDC(wnd.native());
                PIXELFORMATDESCRIPTOR pfd = {
                    sizeof(PIXELFORMATDESCRIPTOR), 1,
                    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
                    PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    PFD_MAIN_PLANE, 0, 0, 0, 0
                };

                int pf = 0;
                if (!(pf = ChoosePixelFormat(device_context, &pfd)))
                    return false;
                SetPixelFormat(device_context, pf, &pfd);

                if (!(render_context = wglCreateContext(device_context)))
                    return false;
                wglMakeCurrent(device_context, render_context);

                swap_interval = (opengl_swap_interval)wglGetProcAddress("wglSwapIntervalEXT");
                if (swap_interval != nullptr && !vsync)
                    swap_interval(0);
                this->vsync = vsync;

                //glEnable(GL_TEXTURE_2D);
                glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

                return true;
            }

            inline bool renderer_opengl10::destroy() noexcept {
                BOOL result = wglDeleteContext(render_context);
                if (result == FALSE) return false;
                result = DeleteDC(device_context);
                return result != 0;
            }

            inline bool renderer_opengl10::swap_buffers() noexcept {
                BOOL result = SwapBuffers(device_context);
                if (vsync) {
                    if (result != TRUE) [[unlikely]]
                        return false;

                    return DwmFlush() == S_OK;
                }
                return result == TRUE;
            }
        #elif defined(__linux__)
            inline renderer_opengl10::~renderer_opengl10() noexcept {
                destroy();
            }

            inline bool renderer_opengl10::create(window& wnd, const bool vsync) noexcept {
                if (!wnd.has_opengl())
                    // for rendering with opengl, you need to create the window with the opengl flag
                    return false;

                display = wnd.native_display();
                native_window = &wnd.native();
                visual_info = wnd.native_visual_info();

                device_context = glXCreateContext(display, visual_info, nullptr, GL_TRUE);
                if (device_context == nullptr) return false;
                glXMakeCurrent(display, *native_window, device_context);

                if (swap_interval == nullptr && !vsync) {
                    // for disabling vsync, you need to specify the swap_interval function
                    return false;
                }

                if (swap_interval != nullptr && !vsync) {
                    swap_interval(display, *native_window, 0);
                }

                glEnable(GL_TEXTURE_2D);
                glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);

                return true;
            }

            inline bool renderer_opengl10::destroy() noexcept {
                if (device_context == nullptr)
                    return true;

                glXMakeCurrent(display, None, nullptr);
                glXDestroyContext(display, device_context);
                device_context = nullptr;

                return true;
            }

            inline bool renderer_opengl10::swap_buffers() noexcept {
                glXSwapBuffers(display, *native_window);
                return true;
            }

        #endif
    }

#endif //RENDERER_HPP
