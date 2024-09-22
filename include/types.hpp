//
// Created by sky: 30.8.2024
//
// Contents:
//
// Always prefixed with: 'lib::'
//
// Data types:
// - i8, u8
// - i16, u16
// - i32, u32
// - i64, u64
// - u128 (* and / operators not supported)
// - native::window_handle
// - native::file_handle
// - native::socket_handle
//

#ifndef TYPES_HPP
  #define TYPES_HPP

  #include "macros.hpp"

  namespace lib {
    #if defined(macros_compiler_msvc)
      using i8  = __int8;
      using u8  = unsigned __int8;
      using i16 = __int16;
      using u16 = unsigned __int16;
      using i32 = __int32;
      using u32 = unsigned __int32;
      using i64 = __int64;
      using u64 = unsigned __int64;
    #elif defined(macros_compiler_gcc) || defined(macros_compiler_clang)
      #if defined(__INT8_TYPE__) && defined(__UINT8_TYPE__)    \
        && defined(__INT16_TYPE__) && defined(__UINT16_TYPE__) \
        && defined(__INT32_TYPE__) && defiend(__UINT32_TYPE__) \
        && defined(__INT64_TYPE__) && defined(__UINT64_TYPE__)

        using i8  = __INT8_TYPE__;
        using u8  = __UINT8_TYPE__;
        using i16 = __INT16_TYPE__;
        using u16 = __UINT16_TYPE__;
        using i32 = __INT32_TYPE__;
        using u32 = __UINT32_TYPE__;
        using i64 = __INT64_TYPE__;
        using u64 = __UINT64_TYPE__;

        #define types_found

      #endif // hasn't predefined types
    #endif // gcc or clang

    // fallback to the os definitions
    #if !defined(types_found)
      #if defined(macros_os_windows)
        #include <WinDef.h>
          
        using i8  = INT8;
        using u8  = UINT8;
        using i16 = INT16;
        using u16 = UINT16;
        using i32 = INT32;
        using u32 = UINT32;
        using i64 = INT64;
        using u64 = UINT64;

      #elif defined(macros_os_linux) || defined(macros_os_macos) || defined(macros_os_android)
        #include <sys/types.h>

        using i8  = int8_t;
        using u8  = uint8_t;
        using i16 = int16_t;
        using u16 = uint16_t;
        using i32 = int32_t;
        using u32 = uint32_t;
        using i64 = int64_t;
        using u64 = uint64_t;
        
      #endif // macros_os_posix
    #else // !def(types_found)
      #undef types_found
    #endif // def(types_found)
    
    #if defined(__SIZEOF_INT128__)
      using u128 = __uint128;
    #else // fallback to selfcoded-128-bit-int
      union u128 {
        struct {} empty;
        u8 bytes[16];
        u16 shorts[8];
        u32 integers[4];
        u64 longs[2];

        macros_constexpr u128() macros_noexcept : empty() {}
        macros_constexpr u128(const u128& other) : longs{ other.longs[0], other.longs[1] } {}
        macros_constexpr u128(const u64 a, const u64 b = 0) macros_noexcept : longs{ a, b } {}
        macros_constexpr u128(const u32 a, const u32 b = 0, const u32 c = 0, const u32 d = 0) macros_noexcept : integers{ a, b, c, d } {}
        
        macros_constexpr operator bool() const macros_noexcept { return longs[0] != 0 || longs[1] != 0; }
        macros_constexpr operator u8()  const macros_noexcept { return bytes[0]; }
        macros_constexpr operator u16() const macros_noexcept { return shorts[0]; }
        macros_constexpr operator u32() const macros_noexcept { return integers[0]; }
        macros_constexpr operator u64() const macros_noexcept { return longs[0]; }

        macros_constexpr u128 operator+(const u128& other) const macros_noexcept {
          u128 out = *this;
          out += other;
          return out;
        }

        macros_constexpr u128& operator+=(const u128& other) macros_noexcept {
          const u64 a = longs[0];
          longs[0] += other.longs[0];
          longs[1] += other.longs[1];
          longs[1] += longs[0] < a;
          return *this;
        }

        macros_constexpr u128 operator-(const u128& other) const macros_noexcept {
          u128 out = *this;
          out -= other;
          return out;
        }

        macros_constexpr u128& operator-=(const u128& other) macros_noexcept {
          const u64 a = longs[0];
          longs[0] -= other.longs[0];
          longs[1] -= other.longs[1];
          longs[1] -= longs[0] > a;
          return *this;
        }

        macros_constexpr u128 operator%(const u128& other) const macros_noexcept {
          u128 out = *this;
          out %= other;
          return out;
        }

        macros_constexpr u128& operator%=(const u128& other) macros_noexcept {
          if (!other)
            return *this;

          u128 x = other;
          const u128 y = *this >> 1;

          while (x <= y) {
            x <<= 1;
          }

          while (*this >= other) {
            if (*this >= x)
              *this -= x;

            x >>= 1;
          }

          return *this;
        }

        macros_constexpr u128 operator<<(const i32 count) const macros_noexcept {
          u128 out = *this;
          out <<= count;
          return out;
        }

        macros_constexpr u128& operator<<=(const i32 count) macros_noexcept {
          longs[1] <<= count;
          longs[1] |= longs[0] >> (64 - count);
          longs[0] <<= count;
          return *this;
        }

        macros_constexpr u128 operator>>(const i32 count) const macros_noexcept {
          u128 out = *this;
          out >>= count;
          return out;
        }

        macros_constexpr u128& operator>>=(const i32 count) macros_noexcept {
          longs[0] >>= count;
          longs[0] |= longs[1] << (64 - count);
          longs[1] >>= count;
          return *this;
        }

        macros_constexpr bool operator==(const u128& other) const macros_noexcept {
          return longs[0] == other.longs[0] && longs[1] == other.longs[1];
        }

        macros_constexpr bool operator!=(const u128& other) const macros_noexcept {
          return longs[0] != other.longs[0] || longs[1] != other.longs[1];
        }

        macros_constexpr bool operator<(const u128& other) const macros_noexcept {
          return (longs[0] < other.longs[0] && longs[1] == other.longs[1]) || longs[1] < other.longs[1];
        }

        macros_constexpr bool operator>(const u128& other) const macros_noexcept {
          return (longs[0] > other.longs[0] && longs[1] == other.longs[1]) || longs[1] > other.longs[1];
        }

        macros_constexpr bool operator<=(const u128& other) const macros_noexcept {
          return (longs[0] <= other.longs[0] && longs[1] == other.longs[1]) || longs[1] <= other.longs[1];
        }

        macros_constexpr bool operator>=(const u128& other) const macros_noexcept {
          return (longs[0] >= other.longs[0] && longs[1] == other.longs[1]) || longs[1] >= other.longs[1];
        }
      } // union u128;
    #endif // selfcoded-128-bit-int

    namespace native {
      
      #if defined(macros_os_windows) && defined(STRICT)
        struct HWND__; // predefine the HWND struct
      #endif

      // Defines a handle from the os to a window
      // Win32:   HWND
      // Linux:   unsigned long
      // Macos:   void*
      // Android: void*
      using window_handle = 
        #if defined(macros_os_windows)
          #if defined(STRICT)
            HWND__*;
          #else
            void*; //(defined as: HANDLE->PVOID->void*)
          #endif
        #elif defined(macros_os_linux)
          unsigned long;
        #elif defined(macros_os_macos)
          void*;
        #endif

      // Defines a handle from the os to a file
      // Win32:   HANDLE
      // Linux:   int
      // Macos:   int
      // Android: int
      using file_handle = 
        #if defined(macros_os_windows)
          void*;
        #else
          int;
        #endif

      
      // Defines a handle from the os to a socket
      // Win32:   SOCKET
      // Linux:   int
      // Macos:   int
      // Android: int
      using socket_handle = 

    } // namespace native

  } // namespace lib

#endif // TYPES_HPP
