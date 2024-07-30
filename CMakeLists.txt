cmake_minimum_required(VERSION 3.28)
project(Library)

set(CMAKE_CXX_STANDARD 23)

link_libraries(X11 GL)

add_executable(Library main.cpp
        lib/types.hpp
        lib/vec.hpp
        lib/mat.hpp
        lib/math.hpp
        lib/memory.hpp
        lib/string.hpp
        lib/array.hpp
        lib/vector.hpp
        lib/atomic.hpp
        lib/bit.hpp
        lib/color.hpp
        lib/list.hpp
        lib/iostream.hpp
        lib/time.hpp
        lib/assert.hpp
        lib/handle.hpp
        lib/image.hpp
        lib/process.hpp
        lib/global_error.hpp
        lib/network.hpp
        lib/window.hpp
        lib/renderer.hpp
)
