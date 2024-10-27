//
// Created by sky: 30.8.2024
//
// Contents:
//
// Always prefixed with: 'lib::'
// The namespace 'lib::detail::' is reserved
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
// - conditional_type<bool, T1, T2>
// - type_from_size<u32, bool>
// - iptr, uptr
// - f32, f64
// - min_[data type], max_[data type]
// - type_traits<T>
// - is_same_type<T1, T2>
// - is_any_of_type<T, Ts...>
// - is_int_type<T>
// - is_floating_type<T>
// - is_arithmetic_type<T>
// - is_void_type<T>
// - is_bool_type<T>
// - is_char_type<T>
// - is_integral_type<T>
// - is_signed_type<T>
// - is_unsigned_type<T>
// - is_const_type<T>
// - is_pointer_type<T>
// - is_lvalue_type<T>
// - is_rvalue_type<T>
// - remove_reference<T>
// - remove_const<T>
// - remove_volatile<T>
// - remove_const_volatile<T>
// - remove_pointer<T>
//

#ifndef TYPES_HPP
  #define TYPES_HPP

  // keep this at the top, or else msvc won't notice it :(
  #define NOMINMAX

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

      #define types_found

    #elif defined(macros_compiler_gcc) || defined(macros_compiler_clang)
      #if defined(__INT8_TYPE__) && defined(__UINT8_TYPE__)    \
        && defined(__INT16_TYPE__) && defined(__UINT16_TYPE__) \
        && defined(__INT32_TYPE__) && defined(__UINT32_TYPE__) \
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
    
    union u128 {
      struct {} empty;
      u8 bytes[16];
      u16 shorts[8];
      u32 integers[4];
      u64 longs[2];

      macros_constexpr u128() macros_noexcept : empty() {}
      macros_constexpr u128(const u128& other) : longs{ other.longs[0], other.longs[1] } {}
      macros_constexpr u128(const u64 a) macros_noexcept : longs{ a, 0 } {}
      macros_constexpr u128(const u64 a, const u64 b) macros_noexcept : longs{ a, b } {}
      macros_constexpr u128(const u32 a, const u32 b, const u32 c, const u32 d) macros_noexcept : integers{ a, b, c, d } {}
      
      macros_constexpr operator bool() const macros_noexcept { return longs[0] != 0 || longs[1] != 0; }
      macros_constexpr operator u8()  const macros_noexcept { return bytes[0]; }
      macros_constexpr operator u16() const macros_noexcept { return shorts[0]; }
      macros_constexpr operator u32() const macros_noexcept { return integers[0]; }
      macros_constexpr operator u64() const macros_noexcept { return longs[0]; }

      macros_constexpr u128 operator+(const u128& other) const macros_noexcept {
        u128 out = *this;
        out += other;
        return out;
      } // +

      macros_constexpr u128& operator+=(const u128& other) macros_noexcept {
        const u64 a = longs[0];
        longs[0] += other.longs[0];
        longs[1] += other.longs[1];
        longs[1] += longs[0] < a;
        return *this;
      } // +=

      macros_constexpr u128 operator-(const u128& other) const macros_noexcept {
        u128 out = *this;
        out -= other;
        return out;
      } // -

      macros_constexpr u128& operator-=(const u128& other) macros_noexcept {
        const u64 a = longs[0];
        longs[0] -= other.longs[0];
        longs[1] -= other.longs[1];
        longs[1] -= longs[0] > a;
        return *this;
      } // -=

      macros_constexpr u128 operator%(const u128& other) const macros_noexcept {
        u128 out = *this;
        out %= other;
        return out;
      } // %

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
      } // %=

      macros_constexpr u128 operator<<(const i32 count) const macros_noexcept {
        u128 out = *this;
        out <<= count;
        return out;
      } // <<

      macros_constexpr u128& operator<<=(const i32 count) macros_noexcept {
        longs[1] <<= count;
        longs[1] |= longs[0] >> (64 - count);
        longs[0] <<= count;
        return *this;
      } // <<=

      macros_constexpr u128 operator>>(const i32 count) const macros_noexcept {
        u128 out = *this;
        out >>= count;
        return out;
      } // >>

      macros_constexpr u128& operator>>=(const i32 count) macros_noexcept {
        longs[0] >>= count;
        longs[0] |= longs[1] << (64 - count);
        longs[1] >>= count;
        return *this;
      } // >>=

      macros_constexpr bool operator==(const u128& other) const macros_noexcept {
        return longs[0] == other.longs[0] && longs[1] == other.longs[1];
      } // ==

      macros_constexpr bool operator!=(const u128& other) const macros_noexcept {
        return longs[0] != other.longs[0] || longs[1] != other.longs[1];
      } // !=

      macros_constexpr bool operator<(const u128& other) const macros_noexcept {
        return (longs[0] < other.longs[0] && longs[1] == other.longs[1]) || longs[1] < other.longs[1];
      } // <

      macros_constexpr bool operator>(const u128& other) const macros_noexcept {
        return (longs[0] > other.longs[0] && longs[1] == other.longs[1]) || longs[1] > other.longs[1];
      } // >

      macros_constexpr bool operator<=(const u128& other) const macros_noexcept {
        return (longs[0] <= other.longs[0] && longs[1] == other.longs[1]) || longs[1] <= other.longs[1];
      } // <=

      macros_constexpr bool operator>=(const u128& other) const macros_noexcept {
        return (longs[0] >= other.longs[0] && longs[1] == other.longs[1]) || longs[1] >= other.longs[1];
      } // >=
    }; // union u128;

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
        #if defined(macros_os_windows)
          void*;
        #else
          int;
        #endif

    } // namespace native

    namespace detail {
      template <bool, typename T1, typename>
      struct conditional_type_struct {
        using type = T1;
      }; // struct conditional_type_struct
      
      template <typename T1, typename T2>
      struct conditional_type_struct<false, T1, T2> {
        using type = T2;
      }; // struct conditional_type_struct
      
      template <u32, bool unsigned_type>
      struct type_from_size_struct {
        static_assert(false, "Type size not found!");
      }; // struct type_from_size_struct

      template <bool unsigned_type>
      struct type_from_size_struct<1, unsigned_type> {
        using type = conditional_type_struct<unsigned_type, u8, i8>::type;
      }; // struct type_from_size_struct

      template <bool unsigned_type>
      struct type_from_size_struct<2, unsigned_type> {
        using type = conditional_type_struct<unsigned_type, u16, i16>::type;
      }; // struct type_from_size_struct

      template <bool unsigned_type>
      struct type_from_size_struct<4, unsigned_type> {
        using type = conditional_type_struct<unsigned_type, u32, i32>::type;
      }; // struct type_from_size_struct

      template <bool unsigned_type>
      struct type_from_size_struct<8, unsigned_type> {
        using type = conditional_type_struct<unsigned_type, u64, i64>::type;
      }; // struct type_from_size_struct
    } // namespace detail

    template <bool enable, typename T1, typename T2>
    using conditional_type = detail::conditional_type_struct<enable, T1, T2>::type;

    template <u32 size, bool unsigned_type>
    using type_from_size = detail::type_from_size_struct<size, unsigned_type>::type;

    using iptr = type_from_size<sizeof(void*), false>;
    using uptr = type_from_size<sizeof(void*), true>;

    using f32 = float;
    using f64 = double;

    macros_constexpr i8 min_i8 = static_cast<i8>(0x80);
    macros_constexpr i8 max_i8 = static_cast<i8>(0x7F);
    macros_constexpr u8 min_u8 = static_cast<u8>(0x00);
    macros_constexpr u8 max_u8 = static_cast<u8>(0xFF);
    
    macros_constexpr i16 min_i16 = static_cast<i16>(0x8000);
    macros_constexpr i16 max_i16 = static_cast<i16>(0x7FFF);
    macros_constexpr u16 min_u16 = static_cast<u16>(0x0000);
    macros_constexpr u16 max_u16 = static_cast<u16>(0xFFFF);
    
    macros_constexpr i32 min_i32 = static_cast<i32>(0x80000000);
    macros_constexpr i32 max_i32 = static_cast<i32>(0x7FFFFFFF);
    macros_constexpr u32 min_u32 = static_cast<u32>(0x00000000);
    macros_constexpr u32 max_u32 = static_cast<u32>(0xFFFFFFFF);
    
    macros_constexpr i64 min_i64 = static_cast<i64>(0x8000000000000000);
    macros_constexpr i64 max_i64 = static_cast<i64>(0x7FFFFFFFFFFFFFFF);
    macros_constexpr u64 min_u64 = static_cast<u64>(0x0000000000000000);
    macros_constexpr u64 max_u64 = static_cast<u64>(0xFFFFFFFFFFFFFFFF);
    
    macros_constexpr u128 min_u128 = u128(min_u64, min_u64);
    macros_constexpr u128 max_u128 = u128(max_u64, max_u64);

		constexpr f32 min_pos_f32 = static_cast<f32>( 1.175494351e-38F);
		constexpr f32 max_f32     = static_cast<f32>( 3.402823466e+38F);
		constexpr f32 min_f32     = static_cast<f32>(-3.402823466e+38F);

		constexpr f64 min_pos_f64 = static_cast<f64>( 2.2250738585072014e-308);
		constexpr f64 max_f64     = static_cast<f64>( 1.7976931348623158e+308);
		constexpr f64 min_f64     = static_cast<f64>(-1.7976931348623158e+308);

    namespace detail {
      template <typename T>
      struct type_traits {
        static_assert(false, "Unknown type!");
      }; // type_traits

      template <>
      struct type_traits<i8> {
        using type = i8;

        macros_constexpr static type min() macros_noexcept {
          return min_i8;
        } // min

        macros_constexpr static type max() macros_noexcept {
          return max_i8;
        } // max

        macros_constexpr static type min_pos() macros_noexcept {
          return 0;
        } // min_pos

        macros_constexpr static i32 byte_count() macros_noexcept {
          return sizeof(type);
        } // byte_count

        macros_constexpr static i32 bit_count() macros_noexcept {
          return sizeof(type) * 8;
        } // bit_count
      }; // type_traits<i8>

      template <>
      struct type_traits<u8> {
        using type = u8;

        macros_constexpr static type min() macros_noexcept {
          return min_u8;
        } // min

        macros_constexpr static type max() macros_noexcept {
          return max_u8;
        } // max

        macros_constexpr static type min_pos() macros_noexcept {
          return 0;
        } // min_pos

        macros_constexpr static i32 byte_count() macros_noexcept {
          return sizeof(type);
        } // byte_count

        macros_constexpr static i32 bit_count() macros_noexcept {
          return sizeof(type) * 8;
        } // bit_count
      }; // type_traits<u8>

      template <>
      struct type_traits<i16> {
        using type = i16;

        macros_constexpr static type min() macros_noexcept {
          return min_i16;
        } // min

        macros_constexpr static type max() macros_noexcept {
          return max_i16;
        } // max

        macros_constexpr static type min_pos() macros_noexcept {
          return 0;
        } // min_pos

        macros_constexpr static i32 byte_count() macros_noexcept {
          return sizeof(type);
        } // byte_count

        macros_constexpr static i32 bit_count() macros_noexcept {
          return sizeof(type) * 8;
        } // bit_count
      }; // type_traits<i16>

      template <>
      struct type_traits<u16> {
        using type = u16;

        macros_constexpr static type min() macros_noexcept {
          return min_u16;
        } // min

        macros_constexpr static type max() macros_noexcept {
          return max_u16;
        } // max

        macros_constexpr static type min_pos() macros_noexcept {
          return 0;
        } // min_pos

        macros_constexpr static i32 byte_count() macros_noexcept {
          return sizeof(type);
        } // byte_count

        macros_constexpr static i32 bit_count() macros_noexcept {
          return sizeof(type) * 8;
        } // bit_count
      }; // type_traits<u16>

      template <>
      struct type_traits<i32> {
        using type = i32;

        macros_constexpr static type min() macros_noexcept {
          return min_i32;
        } // min

        macros_constexpr static type max() macros_noexcept {
          return max_i32;
        } // max

        macros_constexpr static type min_pos() macros_noexcept {
          return 0;
        } // min_pos

        macros_constexpr static i32 byte_count() macros_noexcept {
          return sizeof(type);
        } // byte_count

        macros_constexpr static i32 bit_count() macros_noexcept {
          return sizeof(type) * 8;
        } // bit_count
      }; // type_traits<i32>

      template <>
      struct type_traits<u32> {
        using type = u32;

        macros_constexpr static type min() macros_noexcept {
          return min_u32;
        } // min

        macros_constexpr static type max() macros_noexcept {
          return max_u32;
        } // max

        macros_constexpr static type min_pos() macros_noexcept {
          return 0;
        } // min_pos

        macros_constexpr static i32 byte_count() macros_noexcept {
          return sizeof(type);
        } // byte_count

        macros_constexpr static i32 bit_count() macros_noexcept {
          return sizeof(type) * 8;
        } // bit_count
      }; // type_traits<u32>

      template <>
      struct type_traits<i64> {
        using type = i64;

        macros_constexpr static type min() macros_noexcept {
          return min_i64;
        } // min

        macros_constexpr static type max() macros_noexcept {
          return max_i64;
        } // max

        macros_constexpr static type min_pos() macros_noexcept {
          return 0;
        } // min_pos

        macros_constexpr static i32 byte_count() macros_noexcept {
          return sizeof(type);
        } // byte_count

        macros_constexpr static i32 bit_count() macros_noexcept {
          return sizeof(type) * 8;
        } // bit_count
      }; // type_traits<i64>

      template <>
      struct type_traits<u64> {
        using type = u64;

        macros_constexpr static type min() macros_noexcept {
          return min_u64;
        } // min

        macros_constexpr static type max() macros_noexcept {
          return max_u64;
        } // max

        macros_constexpr static type min_pos() macros_noexcept {
          return 0;
        } // min_pos

        macros_constexpr static i32 byte_count() macros_noexcept {
          return sizeof(type);
        } // byte_count

        macros_constexpr static i32 bit_count() macros_noexcept {
          return sizeof(type) * 8;
        } // bit_count
      }; // type_traits<u64>

      template <>
      struct type_traits<u128> {
        using type = u128;

        macros_constexpr static type min() macros_noexcept {
          return min_u128;
        } // min

        macros_constexpr static type max() macros_noexcept {
          return max_u128;
        } // max

        macros_constexpr static type min_pos() macros_noexcept {
          return min_u128;
        } // min_pos

        macros_constexpr static i32 byte_count() macros_noexcept {
          return sizeof(type);
        } // byte_count

        macros_constexpr static i32 bit_count() macros_noexcept {
          return sizeof(type) * 8;
        } // bit_count
      }; // type_traits<u128>

      template <>
      struct type_traits<f32> {
        using type = f32;

        macros_constexpr static type min() macros_noexcept {
          return min_f32;
        } // min

        macros_constexpr static type max() macros_noexcept {
          return max_f32;
        } // max

        macros_constexpr static type min_pos() macros_noexcept {
          return min_pos_f32;
        } // min_pos

        macros_constexpr static i32 byte_count() macros_noexcept {
          return sizeof(type);
        } // byte_count

        macros_constexpr static i32 bit_count() macros_noexcept {
          return sizeof(type) * 8;
        } // bit_count
      }; // type_traits<f32>

      template <>
      struct type_traits<f64> {
        using type = f64;

        macros_constexpr static type min() macros_noexcept {
          return min_f64;
        } // min

        macros_constexpr static type max() macros_noexcept {
          return max_f64;
        } // max

        macros_constexpr static type min_pos() macros_noexcept {
          return min_pos_f64;
        } // min_pos

        macros_constexpr static i32 byte_count() macros_noexcept {
          return sizeof(type);
        } // byte_count

        macros_constexpr static i32 bit_count() macros_noexcept {
          return sizeof(type) * 8;
        } // bit_count
      }; // type_traits<f64>


    } // detail

    using detail::type_traits;

    macros_constexpr iptr min_iptr = detail::type_traits<iptr>::min();
    macros_constexpr iptr max_iptr = detail::type_traits<iptr>::max();
    macros_constexpr uptr min_uptr = detail::type_traits<uptr>::min();
    macros_constexpr uptr max_uptr = detail::type_traits<uptr>::max();

    template <typename, typename>
    macros_constexpr bool is_same_type = false;
    template <typename T>
    macros_constexpr bool is_same_type<T, T> = true;

    template <typename T, typename... Ts>
    macros_constexpr bool is_any_of_type = (is_same_type<T, Ts> || ...);

    template <typename T>
    macros_constexpr bool is_int_type = is_any_of_type<T, i8, u8, i16, u16, i32, u32, i64, u64, u128>;

    template <typename T>
    macros_constexpr bool is_floating_type = is_any_of_type<T, f32, f64>;

    template <typename T>
    macros_constexpr bool is_arithmetic_type = (is_int_type<T> || is_floating_type<T>);

    template <typename T>
    macros_constexpr bool is_void_type = is_same_type<T, void>;

    template <typename T>
    macros_constexpr bool is_bool_type = is_same_type<T, bool>;

    template <typename T>
    macros_constexpr bool is_char_type = is_any_of_type<T, char, wchar_t>;

    template <typename T>
    macros_constexpr bool is_integral_type = is_bool_type<T> || is_char_type<T> || is_int_type<T>;

    template <typename T>
    macros_constexpr bool is_signed_type = static_cast<T>(-1) < static_cast<T>(0);

    template <typename T>
    macros_constexpr bool is_unsigned_type = !is_signed_type<T>;

    template <typename T>
    macros_constexpr bool is_const_type = false;
    template <typename T>
    macros_constexpr bool is_const_type<const T> = true;

    template <typename T>
    macros_constexpr bool is_pointer_type = false;
    template <typename T>
    macros_constexpr bool is_pointer_type<T*> = true;
    template <typename T>
    macros_constexpr bool is_pointer_type<T* const> = true;
    template <typename T>
    macros_constexpr bool is_pointer_type<T* volatile> = true;
    template <typename T>
    macros_constexpr bool is_pointer_type<T* const volatile> = true;

    template <typename T>
    macros_constexpr bool is_lvalue_type = false;
    template <typename T>
    macros_constexpr bool is_lvalue_type<T&> = true;

    template <typename T>
    macros_constexpr bool is_rvalue_type = false;
    template <typename T>
    macros_constexpr bool is_rvalue_type<T&&> = true;

    namespace detail {
      template <typename T>
      struct remove_reference {
        using type = T;
      };

      template <typename T>
      struct remove_reference<T&> {
        using type = T;
      };

      template <typename T>
      struct remove_reference<T&&> {
        using type = T;
      };

      template <typename T>
      struct remove_const {
        using type = T;
      };

      template <typename T>
      struct remove_const<const T> {
        using type = T;
      };

      template <typename T>
      struct remove_volatile {
        using type = T;
      };

      template <typename T>
      struct remove_volatile<volatile T> {
        using type = T;
      };

      #if __has_builtin(__remove_cv)
        template <typename T>
        struct remove_const_volatile {
          using type = __remove_cv(T);
        };
      #else
        template <typename T>
        struct remove_const_volatile {
          using type = T;
        };

        template <typename T>
        struct remove_const_volatile<const T> {
          using type = T;
        };

        template <typename T>
        struct remove_const_volatile<volatile T> {
          using type = T;
        };

        template <typename T>
        struct remove_const_volatile<const volatile T> {
          using type = T;
        };
      #endif

      template <typename T>
      struct remove_pointer {
        using type = T;
      };

      template <typename T>
      struct remove_pointer<T*> {
        using type = T;
      };

      template <typename T>
      struct remove_pointer<T* const> {
        using type = T;
      };

      template <typename T>
      struct remove_pointer<T* volatile> {
        using type = T;
      };

      template <typename T>
      struct remove_pointer<T* const volatile> {
        using type = T;
      };
    }

    template <typename T>
    using remove_reference = detail::remove_reference<T>::type;
    template <typename T>
    using remove_const = detail::remove_const<T>::type;
    template <typename T>
    using remove_volatile = detail::remove_volatile<T>::type;
    template <typename T>
    using remove_const_volatile = detail::remove_const_volatile<T>::type;
    template <typename T>
    using remove_pointer = detail::remove_pointer<T>::type;

  } // namespace lib

#endif // TYPES_HPP
