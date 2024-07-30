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
    while (win.open()) {
        win.handle_system_events();
    }

    opengl.destroy();
    win.cleanup();
}

int main() {
    win.create({ 100, 100 }, { 250, 250 }, true);
    opengl.create(win, true);

    std::thread thread{update};

    lib::window::start_system_event_loop();

    thread.join();

    return 0;
}
