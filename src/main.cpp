#include "macros.hpp"
#include "types.hpp"

// evil, but easy for testing :)
using namespace lib;

#include <iostream>
#define println(x) std::cout << x << std::endl

macros_constexpr void test_macros() macros_noexcept;
macros_constexpr void test_types() macros_noexcept;

#if defined(macros_os_windows)

  #include <windows.h>

  int WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    std::cout << "Hello World from WinMain!" << std::endl;
    test_macros();
    test_types();
    return 0;
  }

#elif defined(macros_os_linux)

  int main() {
    std::cout << "Hello World from linux!" << std::endl;
    test_macros();
    test_types();
    return 0;
  }

#endif

macros_constexpr void test_macros() macros_noexcept {
  println("Testing macros...");

  println("OS:       " macros_os);
  println("Compiler: " macros_compiler);
  println("Random:   " << macros_random(0, 100) << "\n");

  println("Successfully tested macros.hpp");
}

macros_constexpr void test_types() macros_noexcept {
  println("Testing types...");
  
  i8 a = 0; u8 b = 0;
  i16 c = 0; u16 d = 0;
  i32 e = 0; u32 f = 0;
  i64 g = 0; u64 h = 0;
  u128 i = 0;
  iptr j = 0; uptr k = 0;
  f32 l = 0.0f; f64 m = 0.0;
  h = a + b + c + d + e + f + g + h;
  i = u128(j + k + l + m, 0);
  
  native::window_handle n = 0;
  native::file_handle o = 0;
  native::socket_handle p = 0;

  static_assert(typeid(conditional_type<false, u8, i32>) == typeid(i32));
  static_assert(typeid(conditional_type<true, i32, i16>) == typeid(i32));

  static_assert(typeid(type_from_size<4, false>) == typeid(i32));
  static_assert(typeid(type_from_size<4, true>) == typeid(u32));

  println("min/max i8: " << (i32)min_i8 << "..." << (i32)max_i8);
  println("min/max u8: " << (i32)min_u8 << "..." << (i32)max_u8);
  println("min/max i16: " << min_i16 << "..." << max_i16);
  println("min/max u16: " << min_u16 << "..." << max_u16);
  println("min/max i32: " << min_i32 << "..." << max_i32);
  println("min/max u32: " << min_u32 << "..." << max_u32);
  println("min/max i64: " << min_i64 << "..." << max_i64);
  println("min/max u64: " << min_u64 << "..." << max_u64);

  println("Successfully tested types.hpp");
}