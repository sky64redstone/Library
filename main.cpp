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

void update() {
    if (opengl.create(win, true) == false) return;
    opengl.update_viewport({ 0, 0 }, win.window_size());

    while (win.open()) {
        win.handle_system_events();

        glClearColor(0.9, 0.7, 0.0, 1.0);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        constexpr float Offset = 0.9;

        glBegin(GL_TRIANGLES);

        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(0, Offset);

        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(Offset, -Offset);

        glColor3f(0.0, 0.0, 1.0);
        glVertex2f(-Offset, -Offset);

        glEnd();

        glXSwapBuffers(win.native_display(), win.native());
    }

    opengl.destroy();
    win.cleanup();
}

int main() {
    if (win.create({ 100, 100 }, { 250, 250 }, true) == false)
        return -1;

    std::thread thread{update};

    lib::window::start_system_event_loop();

    thread.join();

    return 0;
}
