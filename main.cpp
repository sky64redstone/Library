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

#define unused(x) (void)(x)

int main() {
    constexpr lib::mat2i test{};
    auto temp = test.inverse();

    constexpr lib::string str = "readonly";
    lib::uint64 str_pos = str.find("only");
    lib::uint64 ch_pos = str.find('o');

    unused(lib::cout << "hi");

    return (temp.m00 = 0);
}
