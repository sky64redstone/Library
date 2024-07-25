#include "lib/iostream.hpp"
#include "lib/array.hpp"
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

#define unused(x) (void)(x)

int main() {
    lib::window win{};
    win.create({ 100, 100 }, { 250, 250 });

    unused(win.set_title("test"));

    win.start_system_event_loop();

    while (win.open()) {
        win.handle_system_events();
    }

    return 0;
}
