#include "lib/iostream.hpp"
#include "lib/array.hpp"
#include "lib/assert.hpp"
#include "lib/atomic.hpp"
#include "lib/bit.hpp"
#include "lib/color.hpp"
#include "lib/iostream.hpp"
#include "lib/list.hpp"
#include "lib/mat.hpp"
#include "lib/math.hpp"
#include "lib/memory.hpp"
#include "lib/string.hpp"
#include "lib/time.hpp"
#include "lib/types.hpp"
#include "lib/vec.hpp"
#include "lib/vector.hpp"
#include "lib/window.hpp"
#include "lib/renderer.hpp"

#include <thread>

#define unused(x) (void)(x)

lib::window win{};
lib::renderer_opengl10 opengl{};

void update() noexcept {
    opengl.create(win, true);

    while (win.open()) {
        opengl.update_viewport({ 0, 0 }, win.window_size());

        opengl.clear_buffer({ 255, 255, 255 }, true);

        constexpr float Offset = 0.9;

        opengl.begin_triangles();

        opengl.draw_triangle(
            { 0, Offset, 1 }, { 255, 0, 0 },
            { Offset, -Offset, 1 }, { 0, 255, 0 },
            {-Offset, -Offset, 1 }, { 0, 0, 255 }
        );

        opengl.end_drawing();

        opengl.swap_buffers();
    }

    opengl.destroy();
    win.cleanup();
}

int main() noexcept {
    win.create({ 0, 0 }, { 500, 300 }, true);

    std::thread t(update);

    win.start_system_event_loop();

    t.join();

    return 0;
}