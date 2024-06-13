# 0 "/home/sky/projects/Library/main.cpp"
# 1 "/home/sky/projects/Library/cmake-build-debug//"
# 0 "<eingebaut>"
# 0 "<Kommandozeile>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<Kommandozeile>" 2
# 1 "/home/sky/projects/Library/main.cpp"
# 1 "/home/sky/projects/Library/lib/iostream.hpp" 1



# 1 "/home/sky/projects/Library/lib/types.hpp" 1
# 50 "/home/sky/projects/Library/lib/types.hpp"
    namespace lib {
# 62 "/home/sky/projects/Library/lib/types.hpp"
                using byte = signed char;





                using ubyte = unsigned char;





                using int16 = short int;





                using uint16 = short unsigned int;





                using int32 = int;





                using uint32 = unsigned int;





                using int64 = long int;





                using uint64 = long unsigned int;





  union alignas(16) uint128 {
   struct {} empty;
   ubyte as_bytes[16];
   uint16 as_uint16[8];
   uint32 as_uint32[4];
   uint64 as_uint64[2];

   constexpr uint128() noexcept : empty() {}
   constexpr uint128(const uint64 v1, const uint64 v2 = 0) noexcept : as_uint64{ v1, v2 } {}
   constexpr uint128(const uint32 v1, const uint32 v2, const uint32 v3, const uint32 v4) noexcept : as_uint32{ v1, v2, v3, v4 } {}

   constexpr operator bool() const noexcept { return as_uint64[0] != 0 || as_uint64[1] != 0; }
   constexpr explicit operator ubyte () const noexcept { return as_bytes [0]; }
   constexpr explicit operator uint16() const noexcept { return as_uint16[0]; }
   constexpr explicit operator uint32() const noexcept { return as_uint32[0]; }
   constexpr explicit operator uint64() const noexcept { return as_uint64[0]; }

   constexpr uint128 operator+(const uint128& other) const noexcept {
    uint128 out(*this);
    out += other;
    return out;
   }

   constexpr uint128& operator+=(const uint128 & other) noexcept {
    const auto o = as_uint64[0];
    as_uint64[0] += other.as_uint64[0];
    as_uint64[1] += other.as_uint64[1];
    as_uint64[1] += (as_uint64[0] < o);
    return *this;
   }

   constexpr uint128 operator-(const uint128& other) const noexcept {
    uint128 out(*this);
    out -= other;
    return out;
   }

   constexpr uint128& operator-=(const uint128& other) noexcept {
    const auto o = as_uint64[0];
    as_uint64[0] -= other.as_uint64[0];
    as_uint64[1] -= other.as_uint64[1];
    as_uint64[1] -= (as_uint64[0] > o);
    return *this;
   }

   constexpr uint128 operator%(const uint128& other) const noexcept {
    uint128 out(*this);
    out %= other;
    return out;
   }

   constexpr uint128& operator%=(const uint128& other) noexcept {
    if (!other)
     return *this;

    uint128 x(other);
    const uint128 y(*this >> 1);

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

   constexpr uint128 operator<<(const lib::ubyte value) const noexcept {
    uint128 out(*this);
    out <<= value;
    return out;
   }

   constexpr uint128& operator<<=(const lib::ubyte value) noexcept {
    as_uint64[1] <<= value;
    as_uint64[1] |= as_uint64[0] >> (64 - value);
    as_uint64[0] <<= value;
    return *this;
   }

   constexpr uint128 operator>>(const lib::ubyte value) const noexcept {
    uint128 out(*this);
    out >>= value;
    return out;
   }

   constexpr uint128& operator>>=(const lib::ubyte value) noexcept {
    as_uint64[0] >>= value;
    as_uint64[0] |= as_uint64[1] << (64 - value);
    as_uint64[1] >>= value;
    return *this;
   }

   constexpr uint128 operator<<(const int value) const noexcept {
    return *this << static_cast<lib::ubyte>(value);
   }

   constexpr uint128& operator<<=(const int value) noexcept {
    return *this <<= static_cast<lib::ubyte>(value);
   }

   constexpr uint128 operator>>(const int value) const noexcept {
    return *this >> static_cast<lib::ubyte>(value);
   }

   constexpr uint128& operator>>=(const int value) noexcept {
    return *this >>= static_cast<lib::ubyte>(value);
   }

   constexpr bool operator==(const uint128& other) const noexcept {
    return as_uint64[0] == other.as_uint64[0] && as_uint64[1] == other.as_uint64[1];
   }

   constexpr bool operator!=(const uint128& other) const noexcept {
    return as_uint64[0] != other.as_uint64[0] || as_uint64[1] != other.as_uint64[1];
   }

   constexpr bool operator<(const uint128& other) const noexcept {
    return (as_uint64[0] < other.as_uint64[0] && as_uint64[1] == other.as_uint64[1]) || as_uint64[1] < other.as_uint64[1];
   }

   constexpr bool operator<=(const uint128& other) const noexcept {
    return (as_uint64[0] <= other.as_uint64[0] && as_uint64[1] == other.as_uint64[1]) || as_uint64[1] < other.as_uint64[1];
   }

   constexpr bool operator>(const uint128& other) const noexcept {
    return (as_uint64[0] > other.as_uint64[0] && as_uint64[1] == other.as_uint64[1]) || as_uint64[1] > other.as_uint64[1];
   }

   constexpr bool operator>=(const uint128& other) const noexcept {
    return (as_uint64[0] >= other.as_uint64[0] && as_uint64[1] == other.as_uint64[1]) || as_uint64[1] > other.as_uint64[1];
   }

   [[nodiscard]] constexpr lib::uint64 hash() const noexcept {
    return as_uint64[0] ^ as_uint64[1];
   }
  };
  static_assert(sizeof(uint128) == 16);
  static_assert(alignof(uint128) == 16);

        template <bool, typename t1, typename>
        struct conditional_type_struct {
            using type = t1;
        };

        template <typename t1, typename t2>
        struct conditional_type_struct<false, t1, t2> {
            using type = t2;
        };

        template <bool enable, typename t1, typename t2>
        using conditional_type = typename conditional_type_struct<enable, t1, t2>::type;

        template <uint64 type_size, bool unsigned_type>
        struct type_from_size_struct {};

        template <bool unsigned_type>
        struct type_from_size_struct<1, unsigned_type> {
            using type = conditional_type<unsigned_type, ubyte, byte>;
        };

        template <bool unsigned_type>
        struct type_from_size_struct<2, unsigned_type> {
            using type = conditional_type<unsigned_type, uint16, int16>;
        };

        template <bool unsigned_type>
        struct type_from_size_struct<4, unsigned_type> {
            using type = conditional_type<unsigned_type, uint32, int32>;
        };

        template <bool unsigned_type>
        struct type_from_size_struct<8, unsigned_type> {
            using type = conditional_type<unsigned_type, uint64, int64>;
        };

     template <uint64 type_size, bool unsigned_type>
     using type_from_size = typename type_from_size_struct<type_size, unsigned_type>::type;

        using intptr = type_from_size<sizeof(void*), false>;
        using uintptr = type_from_size<sizeof(void*), true>;

        constexpr byte min_byte = static_cast<byte> (0x80);
  constexpr byte max_byte = static_cast<byte> (0x7F);
  constexpr ubyte min_ubyte = static_cast<ubyte> (0x00);
  constexpr ubyte max_ubyte = static_cast<ubyte> (0xFF);
  constexpr int16 min_int16 = static_cast<int16> (0x8000);
  constexpr int16 max_int16 = static_cast<int16> (0x7FFF);
  constexpr uint16 min_uint16 = static_cast<uint16>(0x0000);
  constexpr uint16 max_uint16 = static_cast<uint16>(0xFFFF);
  constexpr int32 min_int32 = static_cast<int32> (0x80000000);
  constexpr int32 max_int32 = static_cast<int32> (0x7FFFFFFF);
  constexpr uint32 min_uint32 = static_cast<uint32>(0x00000000);
  constexpr uint32 max_uint32 = static_cast<uint32>(0xFFFFFFFF);
  constexpr int64 min_int64 = static_cast<int64> (0x8000000000000000);
  constexpr int64 max_int64 = static_cast<int64> (0x7FFFFFFFFFFFFFFF);
  constexpr uint64 min_uint64 = static_cast<uint64>(0x0000000000000000);
  constexpr uint64 max_uint64 = static_cast<uint64>(0xFFFFFFFFFFFFFFFF);

  constexpr float min_pos_float = static_cast<float> (1.175494351e-38F);
  constexpr float max_float = static_cast<float> (3.402823466e+38F);
  constexpr float min_float = static_cast<float> (-3.402823466e+38F);

  constexpr double min_pos_double = static_cast<double>(2.2250738585072014e-308);
  constexpr double max_double = static_cast<double>(1.7976931348623158e+308);
  constexpr double min_double = static_cast<double>(-1.7976931348623158e+308);

  template <typename T>
  struct type_traits {
   using type = T;
  };

  template <>
  struct type_traits<byte> {
   using type = byte;

   static constexpr byte min() noexcept {
    return min_byte;
   }

   static constexpr byte min_pos() noexcept {
    return 0;
   }

   static constexpr byte max() noexcept {
    return max_byte;
   }

   static constexpr uint32 byte_size() noexcept {
    return sizeof(byte);
   }

   static constexpr uint32 bit_size() noexcept {
    return (sizeof(byte) + 7) << 3;
   }
  };

  template <>
  struct type_traits<ubyte> {
   using type = ubyte;

   static constexpr ubyte min() noexcept {
    return min_ubyte;
   }

   static constexpr ubyte min_pos() noexcept {
    return 0;
   }

   static constexpr ubyte max() noexcept {
    return max_ubyte;
   }

   static constexpr uint32 byte_size() noexcept {
    return sizeof(ubyte);
   }

   static constexpr uint32 bit_size() noexcept {
    return (sizeof(ubyte) + 7) << 3;
   }
  };

  template <>
  struct type_traits<int16> {
   using type = int16;

   static constexpr int16 min() noexcept {
    return min_int16;
   }

   static constexpr int16 min_pos() noexcept {
    return 0;
   }

   static constexpr int16 max() noexcept {
    return max_int16;
   }

   static constexpr uint32 byte_size() noexcept {
    return sizeof(int16);
   }

   static constexpr uint32 bit_size() noexcept {
    return (sizeof(int16) + 7) << 3;
   }
  };

  template <>
  struct type_traits<uint16> {
   using type = uint16;

   static constexpr uint16 min() noexcept {
    return min_uint16;
   }

   static constexpr uint16 min_pos() noexcept {
    return 0;
   }

   static constexpr uint16 max() noexcept {
    return max_uint16;
   }

   static constexpr uint32 byte_size() noexcept {
    return sizeof(uint16);
   }

   static constexpr uint32 bit_size() noexcept {
    return (sizeof(uint16) + 7) << 3;
   }
  };

  template <>
  struct type_traits<int32> {
   using type = int32;

   static constexpr int32 min() noexcept {
    return min_int32;
   }

   static constexpr int32 min_pos() noexcept {
    return 0;
   }

   static constexpr int32 max() noexcept {
    return max_int32;
   }

   static constexpr uint32 byte_size() noexcept {
    return sizeof(int32);
   }

   static constexpr uint32 bit_size() noexcept {
    return (sizeof(int32) + 7) << 3;
   }
  };

  template <>
  struct type_traits<uint32> {
   using type = uint32;

   static constexpr uint32 min() noexcept {
    return min_uint32;
   }

   static constexpr uint32 min_pos() noexcept {
    return 0;
   }

   static constexpr uint32 max() noexcept {
    return max_uint32;
   }

   static constexpr uint32 byte_size() noexcept {
    return sizeof(uint32);
   }

   static constexpr uint32 bit_size() noexcept {
    return (sizeof(uint32) + 7) << 3;
   }
  };

  template <>
  struct type_traits<int64> {
   using type = int64;

   static constexpr int64 min() noexcept {
    return min_int64;
   }

   static constexpr int64 min_pos() noexcept {
    return 0;
   }

   static constexpr int64 max() noexcept {
    return max_int64;
   }

   static constexpr uint32 byte_size() noexcept {
    return sizeof(int64);
   }

   static constexpr uint32 bit_size() noexcept {
    return (sizeof(int64) + 7) << 3;
   }
  };

  template <>
  struct type_traits<uint64> {
   using type = uint64;

   static constexpr uint64 min() noexcept {
    return min_uint64;
   }

   static constexpr uint64 min_pos() noexcept {
    return 0;
   }

   static constexpr uint64 max() noexcept {
    return max_uint64;
   }

   static constexpr uint32 byte_size() noexcept {
    return sizeof(uint64);
   }

   static constexpr uint32 bit_size() noexcept {
    return (sizeof(uint64) + 7) << 3;
   }
  };

  template <>
  struct type_traits<float> {
   using type = float;

   static constexpr float min() noexcept {
    return min_float;
   }

   static constexpr float min_pos() noexcept {
    return min_pos_float;
   }

   static constexpr float max() noexcept {
    return max_float;
   }

   static constexpr uint32 byte_size() noexcept {
    return sizeof(float);
   }

   static constexpr uint32 bit_size() noexcept {
    return (sizeof(float) + 7) << 3;
   }
  };

  template <>
  struct type_traits<double> {
   using type = double;

   static constexpr double min() noexcept {
    return min_double;
   }

   static constexpr double min_pos() noexcept {
    return min_pos_double;
   }

   static constexpr double max() noexcept {
    return max_double;
   }

   static constexpr uint32 byte_size() noexcept {
    return sizeof(double);
   }

   static constexpr uint32 bit_size() noexcept {
    return (sizeof(double) + 7) << 3;
   }
  };

  template <>
  struct type_traits<long double> {
   using type = long double;

   static constexpr long double min() noexcept {
    return min_double;
   }

   static constexpr long double min_pos() noexcept {
    return min_pos_double;
   }

   static constexpr long double max() noexcept {
    return max_double;
   }

   static constexpr uint32 byte_size() noexcept {
    return sizeof(long double);
   }

   static constexpr uint32 bit_size() noexcept {
    return (sizeof(long double) + 7) << 3;
   }
  };

  template <typename, typename>
  inline constexpr bool is_same_type = false;
  template <typename T>
  inline constexpr bool is_same_type<T, T> = true;

  template <typename T, typename... TYPES>
  inline constexpr bool is_any_of_type = (is_same_type<T, TYPES> || ...);

  template <typename T>
  inline constexpr bool is_int_type = is_any_of_type<T, byte, ubyte, int16, uint16, int32, uint32, int64, uint64>;

  template <typename T>
  inline constexpr bool is_floating_type = is_any_of_type<T, float, double, long double>;

  template <typename T>
  inline constexpr bool is_arithmetic_type = (is_int_type<T> || is_floating_type<T>);

  template <typename T>
  inline constexpr bool is_void_type = is_same_type<T, void>;

  template <typename T>
  inline constexpr bool is_bool_type = is_same_type<T, bool>;

  template <typename T>
  inline constexpr bool is_char_type = is_any_of_type<T, char, wchar_t>;

  template <typename T>
  inline constexpr bool integral_type = is_bool_type<T> || is_char_type<T> || is_int_type<T>;

  template <uint64 size>
  using make_unsigned_with_size = type_from_size<size, true>;

  template <typename T>
  using make_unsigned = make_unsigned_with_size<sizeof(T)>;

  template <uint64 size>
  using make_signed_with_size = type_from_size<size, false>;

  template <typename T>
  using make_signed = make_signed_with_size<sizeof(T)>;

  template <typename T>
  struct remove_reference_struct {
   using type = T;
  };

  template <typename T>
  struct remove_reference_struct<T&> {
   using type = T;
  };

  template <typename T>
  struct remove_reference_struct<T&&> {
   using type = T;
  };

     template <typename T>
     using remove_reference = typename remove_reference_struct<T>::type;

  template <typename T>
  struct remove_const_struct {
   using type = T;
  };

  template <typename T>
  struct remove_const_struct<const T> {
   using type = T;
  };

     template <typename T>
     using remove_const = typename remove_const_struct<T>::type;

  template <typename T>
  struct remove_volatile_struct {
   using type = T;
  };

  template <typename T>
  struct remove_volatile_struct<volatile T> {
   using type = T;
  };

     template <typename T>
     using remove_volatile = remove_volatile_struct<T>;

  template <typename T>
  struct remove_const_volatile_struct {
   using type = T;
  };

  template <typename T>
  struct remove_const_volatile_struct<const T> {
   using type = T;
  };

  template <typename T>
  struct remove_const_volatile_struct<volatile T> {
   using type = T;
  };

  template <typename T>
  struct remove_const_volatile_struct<const volatile T> {
   using type = T;
  };

     template <typename T>
     using remove_const_volatile = typename remove_const_volatile_struct<T>::type;

  template <typename T>
  struct signed_type_struct {
   static constexpr bool is_signed = static_cast<T>(-1) < static_cast<T>(0);
   static constexpr bool is_unsigned = !is_signed;
  };

     template <typename T>
     constexpr inline bool is_signed = signed_type_struct<T>::is_signed;

     template <typename T>
  constexpr inline bool is_unsigned = signed_type_struct<T>::is_unsigned;







  template <typename T>
  constexpr inline bool is_const = false;

  template <typename T>
  constexpr inline bool is_const<const T> = true;

  template <typename T>
  constexpr inline bool is_object = lib::is_const<const T> && !lib::is_void_type<T>;
# 747 "/home/sky/projects/Library/lib/types.hpp"
  template <typename T>
  class cycle_value {
  private:
   T current;
   T min, max;
   T step;

  public:
   constexpr cycle_value() noexcept {
    current = 0;
    step = 1;


    if constexpr (lib::is_signed<T>) {
     min = 0;
     max = 1 << ((sizeof(T) + 7) >> 3);
    } else {
     constexpr uint64 bound = 1 << (((sizeof(T) + 7) >> 3) - 1);
     min = -bound;
     max = bound;
    }
   }

   constexpr cycle_value(T min, T max, T curr, T step = 1) noexcept : current(curr), min(min), max(max), step(step) {}

   constexpr T& get() noexcept {
    return current;
   }

   constexpr const T& get() const noexcept {
    return current;
   }

   constexpr T get_min() const noexcept {
    return min;
   }

   constexpr T get_max() const noexcept {
    return max;
   }

   constexpr T get_step() const noexcept {
    return step;
   }

   constexpr void set_step(T new_step) noexcept {
    step = new_step;
   }

   constexpr void set_min(T new_min) noexcept {
    min = new_min;
   }

   constexpr void set_max(T new_max) noexcept {
    max = new_max;
   }

   constexpr void cycle() noexcept {
    if constexpr (lib::is_unsigned<T>) {
     if (current == max) {
      current = min;
     } else {
      current += step;
      if (current == max) {
       current -= max - min;
      }
     }
    } else {
     if (step >= 0) {
      if (current == max) {
       current = min;
       current += step - 1;
      } else {
       current += step;
       if (current >= max) {
        current -= max - min;
       }
      }
     } else {
      if (current == min) {
       current = max;
       current += step + 1;
      } else {
       current += step;
       if (current <= min) {
        current += max - min;
       }
      }
     }
    }
   }
  };

  template <typename T, T VALUE>
  struct constant {
   static constexpr T value = VALUE;

   using type = T;

   constexpr explicit operator type() const noexcept {
    return value;
   }

   [[nodiscard]] constexpr T operator()() const noexcept {
    return value;
   }
  };

  using true_type = constant<bool, true>;
  using false_type = constant<bool, false>;

  template <typename>
  inline constexpr bool is_lvalue_reference = false;

  template <typename T>
     inline constexpr bool is_lvalue_reference<T&> = true;

     template <typename>
  inline constexpr bool is_rvalue_reference = false;

     template <typename T>
  inline constexpr bool is_rvalue_reference<T&&> = true;

  template <typename T>
  [[nodiscard]] inline constexpr T&& forward(lib::remove_reference<T>& value) noexcept {
   return static_cast<T&&>(value);
  }

  template <typename T>
  [[nodiscard]] inline constexpr T&& forward(lib::remove_reference<T>&& value) noexcept {
   static_assert(!is_lvalue_reference<T>, "not allowed!");
   return static_cast<T&&>(value);
  }

  template <bool enable, typename T>
  struct enable_if_type_struct {};

  template <typename T>
  struct enable_if_type_struct<true, T> {
   using type = T;
  };

     template <bool enable, typename T>
     using enable_if_type = typename enable_if_type_struct<enable, T>::type;

  template <typename T>
  struct optional {
  protected:
   T _value;
   bool _has_value;

  public:
   constexpr optional() noexcept : _value(), _has_value(false) {}
   constexpr explicit optional(T val) noexcept : _value(val), _has_value(true) {}
   template <typename... types>
   constexpr explicit optional(types... params) noexcept : _value(params...), _has_value(true) {}

   [[nodiscard]] constexpr bool empty() const noexcept { return !_has_value; }
   [[nodiscard]] constexpr bool has_value() const noexcept { return _has_value; }

   constexpr const T& value() const noexcept { return _value; }
   constexpr T& value() noexcept { return _value; }

   constexpr const T& value_or(const T& other) const noexcept { return _has_value ? _value : other; }
   constexpr T& value_or(T& other) noexcept { return _has_value ? _value : other; }

   constexpr const optional<T>& or_else(const optional<T>& other) const noexcept { return _has_value ? *this : other; }
   constexpr optional<T>& or_else(optional<T>& other) noexcept { return _has_value ? *this : other; }

   template <typename FUNC_T>
   constexpr auto transform(FUNC_T&& func) const noexcept { return func(_value); }
  };

    }
# 5 "/home/sky/projects/Library/lib/iostream.hpp" 2
# 1 "/home/sky/projects/Library/lib/string.hpp" 1




# 1 "/home/sky/projects/Library/lib/memory.hpp" 1




# 1 "/home/sky/projects/Library/lib/math.hpp" 1
# 46 "/home/sky/projects/Library/lib/math.hpp"
 namespace lib {

        static constexpr auto PI = 3.1415926535897932384626433832795028841971;
        static constexpr auto E = 2.7182818284590452353602874713526624977572;
        static constexpr auto C_LIGHT = 299'792'458;

        static constexpr auto PI_DIV_180 = PI / 180.0;
        static constexpr auto INV_PI_DIV_180 = 1.0 / PI_DIV_180;

        inline constexpr auto min(const auto first, const auto second) noexcept {
            return first > second ? second : first;
        }

        inline constexpr auto max(const auto first, const auto second) noexcept {
            return first < second ? second : first;
        }

        template <typename T_OUT, typename T_IN>
        inline constexpr T_OUT union_cast(T_IN in) {
            union {
                T_IN i;
                T_OUT o;
            };
            o = 0;
            i = in;

            return o;
        }

        inline constexpr float fast_inverse(float x) noexcept {
            union {
                float f;
                uint32 i;
            } v{ .f = 0 };

            float sx = (x < 0) ? -1.0f : 1.0f;
            x = sx * x;

            v.i = static_cast<uint32>(0x7EF127EA - lib::union_cast<uint32>(x));
            float w = x * v.f;


            v.f = v.f * (2 - w);



            return v.f * sx;
        }

        inline constexpr float fast_inverse_square_root(const float number) noexcept {
            constexpr float x = 1.5F;

            const float x2 = number * 0.5F;
            float y = number;
            long i = union_cast<long>(y);
            i = 0x5F3759DF - (i >> 1);
            y = union_cast<float>(i);
            y = y * (x - (x2 * y * y));

            return y;
        }

        inline constexpr float fast_square_root(float n) noexcept {
            return 1 / lib::fast_inverse_square_root(n);
        }

        inline constexpr float floor(float number) noexcept {
            union {
                float f;
                uint32 i;
            } val { .f = number };

            uint32 exponent = (val.i >> 23) & 0xff;
            uint32 fractional_bits = 150 - exponent;

            if (fractional_bits > 23)
                return 0.0f;
            if (fractional_bits > 0)
                val.i &= ~((1U << fractional_bits) - 1);

            return val.f;
        }

        inline constexpr int32 floori(const float number) noexcept {
            return static_cast<int32>(number - 0.5f);
        }

        inline constexpr float ceil(const float number) noexcept {
            float floor_num = lib::floor(number);

            if (floor_num < number)
                ++floor_num;

            return floor_num;
        }

        inline constexpr int32 ceili(const float number) noexcept {
            return static_cast<int32>(number + 0.5f);
        }

        template <typename T>
        inline constexpr T abs(T num) noexcept {
            return num < 0 ? -num : num;
        }

        template <typename T> requires (is_floating_type<T>)
        inline constexpr bool is_subnormal(T x) noexcept {
            constexpr const T min_pos = is_same_type<T, float> ? min_pos_float : min_pos_double;
            return lib::abs(x) < min_pos;
        }

        template <typename FLOAT_T> requires is_floating_type<FLOAT_T>
        [[nodiscard]] constexpr inline bool is_nan(FLOAT_T value) noexcept {
            return value != value;
        }

        template <typename FLOAT_T> requires is_floating_type<FLOAT_T>
        [[nodiscard]] constexpr inline bool is_inf(FLOAT_T value) noexcept {



                    return __builtin_isinf_sign(value);
# 177 "/home/sky/projects/Library/lib/math.hpp"
        }

        constexpr inline double powi(double base, uint64 exponent) noexcept {
            double out = base;
            for (uint64 i = 0; i < (exponent - 1); i++) {
                out *= base;
            }
            return out;
        }

        constexpr inline auto deg(auto x) noexcept {
            return x * PI_DIV_180;
        }

        constexpr inline auto rad(auto x) noexcept {
            return x * INV_PI_DIV_180;
        }
 }
# 6 "/home/sky/projects/Library/lib/memory.hpp" 2

 namespace lib {
  template <typename T>
  constexpr inline T* memcpy(const T* const src, T* const dest, const uint64 count, const uint64 offset = 0) noexcept {
   if (src == nullptr || dest == nullptr)
    return nullptr;



   constexpr bool elemental_type = (sizeof(T) == 2) || (sizeof(T) == 4) || (sizeof(T) == 8);


   if constexpr (elemental_type) {

    using type = lib::make_unsigned<T>;

    const type* const tsrc = reinterpret_cast<const type* const>(src);
    type* const tdest = reinterpret_cast<type* const>(dest);
    const uint64 tcount = (count * sizeof(T)) / sizeof(type);
    const uint64 toffset = (offset * sizeof(T)) / sizeof(type);

    for (uint64 i = toffset; i < tcount; ++i) {
     tdest[i] = tsrc[i];
    }

    return dest;
   }

   const auto* const bsrc = reinterpret_cast<const ubyte* const>(src);
   auto* const bdest = reinterpret_cast<ubyte* const>(dest);
   const uint64 bcount = (count * sizeof(T)) / sizeof(ubyte);
   const uint64 boffset = (offset * sizeof(T)) / sizeof(ubyte);

   for (uint64 i = boffset; i < bcount; ++i) {
    bdest[i] = bsrc[i];
   }

   return dest;
  }

  template <typename T>
  constexpr inline T* memmove(T* const src, T* const dest, const uint64 count, const uint64 offset = 0) noexcept {
   if (src == nullptr || dest == nullptr)
    return nullptr;



   constexpr bool elemental_type = (sizeof(T) == 2) || (sizeof(T) == 4) || (sizeof(T) == 8);


   if constexpr (elemental_type) {

    using type = lib::make_unsigned<T>;

    type* const tsrc = reinterpret_cast<type* const>(src);
    type* const tdest = reinterpret_cast<type* const>(dest);
    const uint64 tcount = (count * sizeof(T)) / sizeof(type);
    const uint64 toffset = (offset * sizeof(T)) / sizeof(type);

    for (uint64 i = toffset; i < tcount; ++i) {
     tdest[i] = tsrc[i];
     tsrc[i] = 0;
    }

    return dest;
   }

   auto* const bsrc = reinterpret_cast<ubyte* const>(src);
   auto* const bdest = reinterpret_cast<ubyte* const>(dest);
   const uint64 bcount = (count * sizeof(T)) / sizeof(ubyte);
   const uint64 boffset = (offset * sizeof(T)) / sizeof(ubyte);

   for (uint64 i = boffset; i < bcount; ++i) {
    bdest[i] = bsrc[i];
    bsrc[i] = 0;
   }

   return dest;
  }

  template <typename T>
  constexpr inline T* memset(T* const ptr, const T& value, const uint64 count, const uint64 offset = 0) noexcept {
   if (ptr == nullptr)
    return nullptr;



   constexpr bool elemental_type = (sizeof(T) == 2) || (sizeof(T) == 4) || (sizeof(T) == 8);


   if constexpr (elemental_type) {

    using type = lib::make_unsigned<T>;

    type* const tdest = reinterpret_cast<type* const>(ptr);
    const uint64 tcount = (count * sizeof(T)) / sizeof(type);
    const uint64 toffset = (offset * sizeof(T)) / sizeof(type);

    for (uint64 i = toffset; i < tcount; ++i) {
     tdest[i] = 0;
    }

    return ptr;
   }

   auto* const bdest = reinterpret_cast<ubyte* const>(ptr);
   const uint64 bcount = (count * sizeof(T)) / sizeof(ubyte);
   const uint64 boffset = (offset * sizeof(T)) / sizeof(ubyte);

   for (uint64 i = boffset; i < bcount; ++i) {
    bdest[i] = 0;
   }

   return ptr;
  }

  template <typename T>
  constexpr inline T* memset_point(T* ptr, const T& value, const uint64 x, const uint64 y, const uint64 size_w) noexcept {
   if (ptr == nullptr) [[unlikely]]
    return nullptr;

   ptr = static_cast<T*>(ptr + (x + (y * size_w)) * sizeof(T));

   ptr[0] = value;

   return ptr;
  }



  template <typename T>
  constexpr inline void memset_line(T* ptr, const T& value, int64 x0, int64 y0, const int64 x1, const int64 y1, const uint64 size_w) noexcept {
   if (ptr == nullptr)
    return;

   bool yLonger = false;
   int64 shortLen = y1 - y0;
   int64 longLen = x1 - x0;

   if (abs(shortLen) > abs(longLen)) {
    const int64 swap = shortLen;
    shortLen = longLen;
    longLen = swap;
    yLonger = true;
   }

   int64 decInc;

   if (longLen == 0LL)
    decInc = 0LL;
   else
    decInc = (shortLen << 16) / longLen;

   if (yLonger) {
    if (longLen > 0) {
     longLen += y0;
     for (int64 j = 0x8000 + (x0 << 16); y0 <= longLen; ++y0) {
      lib::memset_point<T>(ptr, value, j >> 16, y0, size_w);
      j += decInc;
     }
     return;
    }
    longLen += y0;
    for (int64 j = 0x8000 + (x0 << 16); y0 >= longLen; --y0) {
     lib::memset_point<T>(ptr, value, j >> 16, y0, size_w);
     j -= decInc;
    }
    return;
   }

   if (longLen > 0) {
    longLen += x0;
    for (int64 j = 0x8000 + (y0 << 16); x0 <= longLen; ++x0) {
     (void) lib::memset_point<T>(ptr, value, x0, j >> 16, size_w);
     j += decInc;
    }
    return;
   }

   longLen += x0;

   for (int64 j = 0x8000 + (y0 << 16); x0 >= longLen; --x0) {
    lib::memset_point<T>(ptr, value, x0, j >> 16, size_w);
    j -= decInc;
   }
  }


  template <typename T>
  constexpr inline void memset_line_antialised(T* ptr, const T& value, double x0, double y0, double x1, double y1, const uint64 size_w) noexcept {
   if (ptr == nullptr)
    return;
# 206 "/home/sky/projects/Library/lib/memory.hpp"
   const bool steep = (y1 - y0 > 0 ? y1 - y0 : -y1 - y0) > (x1 - x0 > 0 ? x1 - x0 : -x1 - x0);

   if (steep) {
    { auto temp = x0; x0 = y0; y0 = temp; };
    { auto temp = x1; x1 = y1; y1 = temp; };
   }
   if (x0 > x1) {
    { auto temp = x0; x0 = x1; x1 = temp; };
    { auto temp = y0; y0 = y1; y1 = temp; };
   }

   auto dx = x1 - x0;
   auto dy = y1 - y0;
   double gradient = 0.0;

   if (dx == 0.0) {
    gradient = 1.0;
   } else {
    gradient = dy / dx;
   }

   auto xend = static_cast<uint64>(x0 + 0.5);
   auto yend = y0 + gradient * (xend - x0);
   auto xgap = (1 - (x0 + 0.5 - static_cast<uint64>(x0 + 0.5)));
   const auto xpxl1 = xend;
   const auto ypxl1 = static_cast<uint64>(yend);

   if (steep) {
    lib::memset_point<T>(ptr, value * ((1 - (yend - static_cast<uint64>(yend))) * xgap), ypxl1, xpxl1, size_w);
    lib::memset_point<T>(ptr, value * ((yend - static_cast<uint64>(yend)) * xgap), ypxl1 + 1, xpxl1, size_w);
   } else {
    lib::memset_point<T>(ptr, value * ((1 - (yend - static_cast<uint64>(yend))) * xgap), xpxl1, ypxl1, size_w);
    lib::memset_point<T>(ptr, value * ((yend - static_cast<uint64>(yend)) * xgap), xpxl1, ypxl1 + 1, size_w);
   }

   auto intery = yend + gradient;

   xend = static_cast<uint64>(x1 + 0.5);
   yend = y1 + gradient * (xend - x1);
   xgap = (x1 + 0.5 - static_cast<uint64>(x1 + 0.5));
   const auto xpxl2 = xend;
   const auto ypxl2 = static_cast<uint64>(yend);

   if (steep) {
    lib::memset_point<T>(ptr, value * ((1 - (yend - static_cast<uint64>(yend))) * xgap), ypxl2, xpxl2, size_w);
    lib::memset_point<T>(ptr, value * ((yend - static_cast<uint64>(yend)) * xgap), ypxl2 + 1, xpxl2, size_w);

    const auto xstartloop = xpxl1 + 1;
    const auto xendloop = xpxl2 - 1;

    const uint64 increment = xstartloop < xendloop ? 1 : -1;
    for (auto x = xpxl1 + 1; x != xpxl2 - 1; x += increment) {
     lib::memset_point<T>(ptr, value * (1 - (intery - static_cast<uint64>(intery))), static_cast<uint64>(intery), x, size_w);
     lib::memset_point<T>(ptr, value * (intery - static_cast<uint64>(intery)), static_cast<uint64>(intery) + 1, x, size_w);

     intery += gradient;
    }

   } else {
    lib::memset_point<T>(ptr, value * ((1 - (yend - static_cast<uint64>(yend))) * xgap), xpxl1, ypxl1, size_w);
    lib::memset_point<T>(ptr, value * ((yend - static_cast<uint64>(yend)) * xgap), xpxl1, ypxl1 + 1, size_w);

    const auto xstartloop = xpxl1 + 1;
    const auto xendloop = xpxl2 - 1;

    const uint64 increment = xstartloop < xendloop ? 1 : -1;
    for (auto x = xpxl1 + 1; x != xpxl2 - 1; x += increment) {
     lib::memset_point<T>(ptr, value * (1 - (intery - static_cast<uint64>(intery))), x, static_cast<uint64>(intery), size_w);
     lib::memset_point<T>(ptr, value * (intery - static_cast<uint64>(intery)), x, static_cast<uint64>(intery) + 1, size_w);

     intery += gradient;
    }
   }







  }

  template <typename T>
  constexpr inline void memset_rect(T* ptr, const T& value, uint64 x, const uint64 y, const uint64 w, const uint64 h, const uint64 size_w) noexcept {
   if (ptr == nullptr)
    return;

   const uint64 yh = h + y;

   const uint64 wl1d = (size_w - w) * sizeof(T);

   ptr = static_cast<T*>(ptr + y * size_w * sizeof(T));

   for (uint64 dy = y; dy < yh; ++dy) {
    T* xptr = static_cast<T*>(ptr + x);

    for (uint64 dx = 0; dx < w; ++dx) {
     xptr[dx] = value;
    }

    ptr = static_cast<T*>(ptr + wl1d);
   }
  }

  template <typename T>
  constexpr inline int32 memcmp(const T* const first, const T* const second, const uint64 count, const uint64 offset = 0) noexcept {
   if (first == nullptr || second == nullptr) [[unlikely]]
    return static_cast<intptr>(first - second);

   constexpr const uint64 size = sizeof(T);
   const uint64 size_count = size * count;
   const uint64 size_offset = size * offset;

   const auto* const first8 = reinterpret_cast<const ubyte* const>(first);
   const auto* const second8 = reinterpret_cast<const ubyte* const>(second);

   for (uint64 i = size_offset; i < size_count; ++i) {
    if (first8[i] != second8[i]) {
     return first8[i] > second8[i] ? 1 : -1;
    }
   }

   return 0;
  }

  template <typename T>
  constexpr inline void memswap(T* const first, T* const second) noexcept {
   T temp{};
   lib::memcpy<T>(first, &temp, 1);
   lib::memcpy<T>(second, first, 1);
   lib::memcpy<T>(&temp, second, 1);
  }

  template <typename T>
  constexpr inline void memswap(T& first, T& second) noexcept {
   T temp = first;
   first = second;
   second = temp;
  }

  class nocopy {
  protected:
   constexpr nocopy() noexcept = default;
   constexpr ~nocopy() noexcept = default;

  public:
   constexpr nocopy([[maybe_unused]] const nocopy&) noexcept = delete;
   constexpr nocopy& operator=([[maybe_unused]] const nocopy&) noexcept = delete;
  };

  class nomove {
  protected:
   constexpr nomove() noexcept = default;
   constexpr ~nomove() noexcept = default;

  public:
   constexpr nomove([[maybe_unused]] const nomove&&) noexcept = delete;
   constexpr nomove& operator=([[maybe_unused]] const nomove&&) noexcept = delete;
  };

  template <typename T>
  [[nodiscard]] constexpr inline lib::remove_reference<T>&& move(T&& value) {
   return static_cast<lib::remove_reference<T>&&>(value);
  }

  template <typename T>
  class unique_ptr : public nocopy {
  private:
   T* ptr;

  public:
   constexpr unique_ptr() noexcept {
    ptr = nullptr;
   }

   constexpr unique_ptr(unique_ptr&& other) noexcept {




    ptr = other.ptr;

    other.ptr = nullptr;
   }

   constexpr unique_ptr& operator=(unique_ptr&& other) noexcept {
    destroy();

    ptr = other.ptr;

    other.ptr = nullptr;

    return *this;
   }

   constexpr ~unique_ptr() noexcept {
    destroy();
   }

   template <typename... PARAMS>
   [[nodiscard]] static constexpr unique_ptr<T> make(PARAMS... params) noexcept {
    unique_ptr out{};

    out.ptr = new T(params...);

    return out;
   }

   constexpr void destroy() noexcept {


    delete ptr;
   }

   [[nodiscard]] constexpr T* detach() noexcept {
    T* temp = ptr;

    ptr = nullptr;

    return ptr;
   }

   [[nodiscard]] constexpr T& operator*() noexcept {
    return *ptr;
   }

   [[nodiscard]] constexpr const T& operator*() const noexcept {
    return *ptr;
   }

   [[nodiscard]] constexpr T* operator->() noexcept {
    return ptr;
   }

   [[nodiscard]] constexpr explicit operator bool() const noexcept {
    return static_cast<bool>(ptr);
   }

   constexpr void copy(T* const dest) const noexcept {
    lib::memcpy(ptr, dest, 1);
   }

   constexpr void copy(unique_ptr<T>& other) const noexcept {
    other.destroy();

    T* out = new T{};

    lib::memcpy(ptr, out, 1);

    other.ptr = out;
   }

   [[nodiscard]] constexpr T* copy() const noexcept {
    T* out = new T{};

    lib::memcpy(ptr, out, 1);

    return out;
   }

   constexpr void swap(T* other) const noexcept {
    T temp{};

    lib::memcpy(ptr, &temp, 1);

    lib::memcpy(other, ptr, 1);

    lib::memcpy(&temp, other, 1);
   }

   constexpr void swap(unique_ptr<T>& other) const noexcept {
    T temp{};

    lib::memcpy(ptr, &temp, 1);

    lib::memcpy(other.ptr, ptr, 1);

    lib::memcpy(&temp, other.ptr, 1);
   }
  };
 }
# 6 "/home/sky/projects/Library/lib/string.hpp" 2
# 21 "/home/sky/projects/Library/lib/string.hpp"
 namespace lib {
  template <typename T>
  class char_traits {
  public:
   static constexpr T* copy(T* const dest, const T* src, const uint64 count) noexcept {
    if consteval {
     for (uint64 i = 0; i != count; ++i) {
      dest[i] = src[i];
     }

     return dest;
    }

    lib::memcpy<T>(src, dest, count);

    return dest;
   }

   static constexpr T* move(const T* dest, const T* src, const uint64 count) noexcept {
    if consteval {
     bool loop_forward = true;

     for (const T* source = src; source != src + count; ++source) {
      if (dest == source) {
       loop_forward = false;
       break;
      }
     }

     if (loop_forward) {
      for (uint64 i = 0; i != count; ++i) {
       dest[i] = src[i];
      }
     } else {
      for (uint64 i = count; i != 0; --i) {
       uint64 i_1 = i - 1;
       dest[i_1] = src[i_1];
      }
     }

     return dest;
    }

    lib::memmove(dest, src, count);

    return dest;
   }

   [[nodiscard]] static constexpr int compare(const T* first, const T* second, uint64 count) noexcept {
    for (; 0 < count; --count, ++first, ++second) {
     if (*first != *second) {
      return *first < *second ? -1 : 1;
     }
    }

    return 0;
   }


   [[nodiscard]] static constexpr uint64 length(const T* src) noexcept {
    uint64 count = 0;

    while (*src != static_cast<T>(0)) {
     ++count;
     ++src;
    }

    return count;
   }

   [[nodiscard]] static constexpr const T* find(const T* src, uint64 count, const T& to_find) noexcept {
    for (; 0 < count; --count, ++src) {
     if (*src == to_find) {
      return src;
     }
    }

    return nullptr;
   }

   static constexpr T* assign(T* const src, uint64 count, const T ch) noexcept {
    for (T* next = src; count > 0; --count, ++next) {
     *next = ch;
    }

    return src;
   }

   template <uint64 Size>
   [[nodiscard]] static constexpr T* end(T(&array)[Size]) noexcept {
    return array + Size;
   }
  };

  template <typename T, uint64 SIZE>
  class basic_const_string {
  public:
   using char_type = T;

   template <typename T_, uint64 SIZE_>
   struct basic_const_heap_string {
    static constexpr auto flag_bits = 1;
    static constexpr auto size_bits = 8 - flag_bits;

    ubyte from_stack : flag_bits;
    ubyte reserved : size_bits;

    T_* data;

    uint64 size;

    constexpr void init() noexcept {
     this->from_stack = false;
     this->data = new T_[SIZE_];
     this->size = SIZE_;
    }

    constexpr void destroy() const noexcept {
     delete[] reinterpret_cast<byte*>(data);
    }
   };

   template <typename T_, uint64 SIZE_>
   struct basic_const_stack_string {
    static constexpr auto flag_bits = 1;
    static constexpr auto size_bits = 8 - flag_bits;
    static constexpr auto buffer_size = (sizeof(basic_const_heap_string<T_, SIZE>) - 1) / sizeof(T_);
    static constexpr auto max_size = 1ULL << size_bits;

    ubyte from_stack : flag_bits;
    ubyte size : size_bits;

    T_ data[buffer_size];

    constexpr void init() noexcept {
     this->from_stack = true;
     this->size = static_cast<ubyte>(SIZE_);
    }
   };

  private:
   union {
    basic_const_heap_string <T, SIZE> heap_data;
    basic_const_stack_string<T, SIZE> stack_data;
   };

  public:
   constexpr basic_const_string() noexcept {
    init();
   }

   explicit constexpr basic_const_string(decltype(nullptr)) = delete;

   constexpr basic_const_string(const T* const data) {
    init(data);
   }

   constexpr basic_const_string(const basic_const_string<T, SIZE>& other) noexcept {
    if (other.stack_data.from_stack) {
     stack_data = other.stack_data;
    }
    else {
     heap_data = other.heap_data;
    }
   }

   constexpr basic_const_string(basic_const_string<T, SIZE>&& other) noexcept {
    if (other.stack_data.from_stack) {
     stack_data = other.stack_data;
    } else {
     heap_data = other.heap_data;
    }

    other.init();
   }

   constexpr basic_const_string<T, SIZE>& operator=(decltype(nullptr)) = delete;

   constexpr basic_const_string<T, SIZE>& operator=(const T* const) = delete;

   constexpr basic_const_string<T, SIZE>& operator=(const basic_const_string<T, SIZE>& other) = delete;

   constexpr basic_const_string<T, SIZE>& operator=(basic_const_string<T, SIZE>&& other) = delete;

   constexpr ~basic_const_string() {
    if (!stack_data.from_stack)
     heap_data.destroy();
   }

   [[nodiscard]] constexpr const T& at(uint64 position) const noexcept {
    if (stack_data.from_stack) {
     return stack_data.data[position];
    } else {
     return heap_data.data[position];
    }
   }

   [[nodiscard]] constexpr const T& operator[](uint64 position) const noexcept {

     if (position >= SIZE) {
      return '\0';
     }

    if (stack_data.from_stack) {
     return stack_data.data[position];
    } else {
     return heap_data.data[position];
    }
   }

   [[nodiscard]] constexpr const T* begin() const noexcept {
    if (stack_data.from_stack) {
     return stack_data.data;
    } else {
     return heap_data.data;
    }
   }

   [[nodiscard]] constexpr const T* end() const noexcept {
    if (stack_data.from_stack) {
     return &stack_data.data[SIZE];
    } else {
     return &heap_data.data[SIZE];
    }
   }

   [[nodiscard]] constexpr const T* data() const noexcept {
    return stack_data.from_stack ? stack_data.data : heap_data.data;
   }

   [[nodiscard]] constexpr const T* c_str() const noexcept {
    return stack_data.from_stack ? stack_data.data : heap_data.data;
   }

   [[nodiscard]] constexpr bool empty() const noexcept {
    return (stack_data.from_stack ? stack_data.size : heap_data.size) == 0;
   }

   [[nodiscard]] constexpr uint64 size() const noexcept {
    return stack_data.from_stack ? stack_data.size : heap_data.size;
   }

  private:
   constexpr void init() noexcept {
    if (SIZE < basic_const_stack_string<T, SIZE>::buffer_size) {
     stack_data = basic_const_stack_string<T, SIZE>{};
     stack_data.init();
     char_traits<T>::assign(stack_data.data, SIZE, static_cast<T>(0));
    } else {
     heap_data = basic_const_heap_string<T, SIZE>{};
     heap_data.init();
     char_traits<T>::assign(heap_data.data, SIZE, static_cast<T>(0));
    }
   }

   constexpr void init(const T* const data) {
    if (SIZE < basic_const_stack_string<T, SIZE>::buffer_size) {
     stack_data= basic_const_stack_string<T, SIZE>{};
     stack_data.init();
     auto count = char_traits<T>::length(data);
     char_traits<T>::copy(stack_data.data, data, (count < SIZE ? count : SIZE));
     if (count < SIZE) {
      char_traits<T>::assign(static_cast<T*>(stack_data.data + (count * sizeof(T))), SIZE - count, '\0');
     }
    } else {
     heap_data = basic_const_heap_string<T, SIZE>{};
     heap_data.init();
     char_traits<T>::copy(heap_data.data, data, SIZE);
    }
   }
  };

#pragma region const_string_usings
   template <uint64 SIZE> using const_string = basic_const_string<char, SIZE>; template <uint64 SIZE> using const_stack_string = basic_const_string<char, 0>::basic_const_stack_string<char, SIZE>; template <uint64 SIZE> using const_heap_string = basic_const_string<char, 0>::basic_const_heap_string<char, SIZE>;

   template <uint64 SIZE> using const_wstring = basic_const_string<wchar_t, SIZE>; template <uint64 SIZE> using const_stack_wstring = basic_const_string<wchar_t, 0>::basic_const_stack_string<wchar_t, SIZE>; template <uint64 SIZE> using const_heap_wstring = basic_const_string<wchar_t, 0>::basic_const_heap_string<wchar_t, SIZE>;
# 307 "/home/sky/projects/Library/lib/string.hpp"
    template <uint64 SIZE> using const_tstring = basic_const_string<char, SIZE>; template <uint64 SIZE> using const_stack_tstring = basic_const_string<char, 0>::basic_const_stack_string<char, SIZE>; template <uint64 SIZE> using const_heap_tstring = basic_const_string<char, 0>::basic_const_heap_string<char, SIZE>;

#pragma endregion const_string_usings

  template <typename T>
  class basic_string {
  public:
   using char_type = T;

   template <typename T_>
   struct basic_heap_string {
    static constexpr auto flag_bits = 1;
    static constexpr auto reserved_bits = 8 - flag_bits;

    ubyte from_stack : flag_bits;
    ubyte reserved : reserved_bits;

    T_* data;

    uint64 size;

    constexpr void init(uint64 size) noexcept {
     this->from_stack = false;
     this->data = new T_[size];
     this->size = size;
    }

    constexpr void destroy() const noexcept {
     if (data)
      delete[] reinterpret_cast<byte*>(data);
    }
   };

   template <typename T_>
   struct basic_stack_string {
    static constexpr auto flag_bits = 1;
    static constexpr auto size_bits = 8 - flag_bits;
    static constexpr auto buffer_size = (sizeof(basic_heap_string<T_>) - 1) / sizeof(T_);
    static constexpr auto max_size = 1ULL << size_bits;

    ubyte from_stack : flag_bits;
    ubyte size : size_bits;

    T_ data[buffer_size];

    constexpr void init(uint64 size) noexcept {
     this->from_stack = true;
     this->size = static_cast<ubyte>(size);
    }
   };

  private:
   union {
    basic_heap_string <T> heap_data;
    basic_stack_string<T> stack_data;
   };

  public:
   constexpr basic_string() noexcept {
    init(1);
   }

   explicit constexpr basic_string(decltype(nullptr)) = delete;

   constexpr basic_string(const T* const data) {
    init(data, lib::char_traits<T>::length(data) + 1);
   }

   constexpr explicit basic_string(const uint64 size) {
    init(size);
   }

   constexpr basic_string(const T* const data, const uint64 size) {
    init(data, size);
   }

   constexpr basic_string(const T* const first, const T* const last) {

    init(first, static_cast<uint64>(last - first));
   }

   constexpr basic_string(basic_string<T>& other) noexcept {
    if (other.stack_data.from_stack) {
     stack_data = other.stack_data;
    } else {
     heap_data = other.heap_data;
    }
   }

   constexpr basic_string(basic_string<T>&& other) noexcept {
    if (other.stack_data.from_stack) {
     stack_data = other.stack_data;
    } else {
     heap_data = other.heap_data;
    }

    other.init(1);
   }

   constexpr basic_string<T>& operator=(decltype(nullptr)) = delete;

   constexpr basic_string<T>& operator=(const T* const data) {
    init(data, lib::char_traits<T>::length(data) + 1);
    return *this;
   }

   constexpr basic_string<T>& operator=(const basic_string<T>& other) noexcept {
    if (other.stack_data.from_stack) {
     stack_data = other.stack_data;
    } else {
     heap_data = other.heap_data;
    }
    return *this;
   }

   constexpr basic_string<T>& operator=(basic_string<T>&& other) noexcept {
    if (other.stack_data.from_stack) {
     stack_data = other.stack_data;
    }
    else {
     heap_data = other.heap_data;
    }

    other.init(1);
    other.set(0, static_cast<T>(0));

    return *this;
   }

   constexpr ~basic_string() {
    if (!stack_data.from_stack)
     heap_data.destroy();
   }

   constexpr void assign(decltype(nullptr)) = delete;

   constexpr void assign(const T* const data) {
    if (!heap_data.from_stack)
     heap_data.destroy();

    init(data, lib::char_traits<T>::length(data));
   }

   constexpr void assign(const basic_string<T>& other) noexcept {
    if (other.stack_data.from_stack) {
     stack_data = other.stack_data;
    } else {
     heap_data = other.heap_data;
    }
   }

   constexpr void assign(basic_string<T>&& other) noexcept {
    if (other.stack_data.from_stack) {
     stack_data = other.stack_data;
    } else {
     heap_data = other.heap_data;
    }

    other.init(0);
   }

   [[nodiscard]] constexpr const T& at(uint64 position) const noexcept {
    if (stack_data.from_stack) {
     return stack_data.data[position];
    } else {
     return heap_data.data[position];
    }
   }

   [[nodiscard]] constexpr T& at(uint64 position) noexcept {
    if (stack_data.from_stack) {
     return stack_data.data[position];
    } else {
     return heap_data.data[position];
    }
   }

   constexpr T set(uint64 position, T value) noexcept {
    T& ref = at(position);
    T old = ref;

    ref = value;

    return old;
   }

   constexpr void erase(uint64 first, uint64 last = 0xFFFFFFFFFFFFFFFE) noexcept {
    if (first > size()) [[unlikely]]
     return;

    ++last;

    if (last >= size()) {
     const T null = '\0';
     lib::memset(const_cast<T* const>(data()), null, size() - first, first);
     return;
    }

    lib::memmove<T>(const_cast<T* const>(data() + last), const_cast<T* const>(data() + first), last - first);
   }

   constexpr void erase(T ch) noexcept {
    uint64 offset = 0;

    for (uint64 i = 0; i < size(); ++i) {
     T at_i = at(i);
     if (at_i == ch) {
      ++offset;
     } else if (offset) {
      set(i - offset, at_i);
     }
    }

    if (offset) {
     lib::memset<T>(data(), static_cast<T>(0), offset, size() - offset);
    }
   }

   constexpr void insert(T ch, uint64 position) noexcept {
    uint64 prev_size = size();
    set_size(prev_size + 1);

    if (position >= prev_size) {
     set(prev_size, ch);
     return;
    }

    T* src = data() + position;
    lib::memmove<T>(src, src + 1, prev_size - position);

    set(position, ch);
   }

   [[nodiscard]] constexpr const T& operator[](uint64 position) const noexcept {
    if (stack_data.from_stack) {
     return stack_data.data[position];
    } else {
     return heap_data.data[position];
    }
   }

   [[nodiscard]] constexpr T& operator[](uint64 position) noexcept {
    if (stack_data.from_stack) {
     return stack_data.data[position];
    } else {
     return heap_data.data[position];
    }
   }

   constexpr void upper() noexcept {
    const T diff = static_cast<T>('a' - 'A');

    for (uint64 i = 0; i < size(); ++i) {
     if (i >= 'a' && i <= 'z')
      this->at(i) -= diff;
    }
   }

   constexpr void lower() noexcept {
    const T diff = static_cast<T>('a' - 'A');

    for (uint64 i = 0; i < size(); ++i) {
     if (i >= 'A' && i <= 'Z')
      this->at(i) += diff;
    }
   }

   constexpr void switch_upper_lower() noexcept {
    const T diff = static_cast<T>('a' - 'A');

    for (uint64 i = 0; i < size(); ++i) {
     if (i >= 'A' && i <= 'Z')
      this->at(i) += diff;
     else if (i >= 'a' && i <= 'z')
      this->at(i) -= diff;
    }
   }

   [[nodiscard]] constexpr uint64 find(T ch) const noexcept {
    for (uint64 i = 0; i < size(); ++i) {
     if (this->at(i) == ch)
      return i;
    }

    return max_size();
   }

   [[nodiscard]] constexpr uint64 find(const basic_string<T>& str) const noexcept {
    if (this->size() < str.size())
     return str.find(*this);

    uint64 x = 0;

    for (uint64 i = 0; i < size() - 1; ++i) {
     for (uint64 j = 0;; x = j + i) {

      if (at(x) != str.at(j))
       break;

      ++j;

      if (j == str.size())
       return i;

      if (x < size())
       return max_size();
     }
    }

    return max_size();
   }

   [[nodiscard]] constexpr uint64 reverse_find(T ch) const noexcept {
    for (uint64 i = size() - 1;; --i) {
     if (this->at(i) == ch)
      return i;

     if (i == 0)
      return max_size();
    }
   }

   [[nodiscard]] constexpr uint64 reverse_find(const basic_string<T>& str) const noexcept {
    if (this->size() < str.size())
     return str.reverse_find(str);

    uint64 x = 0;

    for (uint64 i = size() - 1;; --i) {
     for (uint64 j = str.size();; x = i + j) {

      if (at(x) != str.at(j))
       break;

      --j;

      if (j == 0)
       return i;

      if (x < size())
       return max_size();
     }

     if (i == 0)
      return max_size();
    }
   }

   constexpr void append(T ch) noexcept {
    uint64 s = size();

    if (from_stack() && s < basic_stack_string<T>::buffer_size) {
     stack_data.size = s + 1;
    } else {
     set_size(s + 1);
    }

    at(s) = ch;
   }

   constexpr void append(const T* str, const uint64 str_size) noexcept {
    const uint64 s = size();
    uint64 new_size = s + str_size;

    if (from_stack() && new_size <= basic_stack_string<T>::buffer_size) {
     stack_data.size = new_size;
    } else {
     set_size(new_size);
    }

    for (uint64 i = 0, j = s; i < str_size; ++i, ++j) {
     at(j) = str[i];
    }
   }

   constexpr void append(const basic_string<T>& str) noexcept {
    uint64 s = size();
    uint64 new_size = s + str.size();

    if (from_stack() && new_size <= basic_stack_string<T>::buffer_size) {
     stack_data.size = new_size;
    } else {
     set_size(new_size);
    }

    for (uint64 i = 0, j = s; i < str.size(); ++i, ++j) {
     at(j) = str.at(i);
    }
   }

   constexpr void append(const basic_string<T>&& str) noexcept {
    uint64 s = size();
    uint64 new_size = s + str.size();

    if (from_stack() && new_size <= basic_stack_string<T>::buffer_size) {
     stack_data.size = new_size;
    }
    else {
     set_size(new_size);
    }

    for (uint64 i = 0, j = s; i < str.size(); ++i, ++j) {
     at(j) = str.at(i);
    }
   }

   constexpr void append(const T* str) noexcept {
    uint64 str_size = lib::char_traits<T>::length(str);
    uint64 s = size();
    uint64 new_size = s + str_size;

    if (from_stack() && new_size <= basic_stack_string<T>::buffer_size) {
     stack_data.size = new_size;
    } else {
     set_size(new_size);
    }

    for (uint64 i = 0, j = s; i < str_size; ++i, ++j) {
     at(j) = str[i];
    }
   }

   constexpr void append(uint64 count, T ch) noexcept {
    uint64 s = size();
    uint64 new_size = s + count;

    if (from_stack() && new_size <= basic_stack_string<T>::buffer_size) {
     stack_data.size = new_size;
    } else {
     set_size(new_size);
    }

    for (uint64 i = s; i < new_size; ++i) {
     at(i) = ch;
    }
   }


   constexpr bool set_size(uint64 new_size, const bool copy_old_data = true) noexcept {
    if (new_size <= size()) {
     ++new_size;

     const T null = static_cast<T>(0);
     lib::memset(data(), null, size() - new_size, new_size);

     return stack_data.from_stack;
    }

    if (stack_data.from_stack && new_size <= basic_stack_string<T>::buffer_size) {

     ++new_size;


     const T null = static_cast<T>(0);
     lib::memset(data(), null, basic_stack_string<T>::buffer_size - new_size, new_size);

     return true;
    }

    T* old_data = nullptr;
    uint64 old_size = size();

    if (copy_old_data) [[likely]] {
     old_data = new T[size()];
     lib::memcpy(data(), old_data, size());
    }


    if (!stack_data.from_stack) {
     heap_data.destroy();
    }

    heap_data.init(new_size);

    if (copy_old_data) [[likely]] {
     lib::memcpy(old_data, heap_data.data, old_size);

     delete[] old_data;
    }

    return false;
   }

   constexpr void shrink_to_fit() noexcept {


    if (!stack_data.from_stack) {
     if (const uint64 new_size = lib::char_traits<T>::length(data()) + 1; new_size < size()) {
      T* old_data = new T[new_size];
      lib::memcpy(data(), old_data, new_size);

      heap_data.destroy();

      this->init(old_data, new_size);

      delete[] old_data;
     }
    }
   }

   [[nodiscard]] constexpr const T* begin() const noexcept {
    if (stack_data.from_stack) {
     return stack_data.data;
    } else {
     return heap_data.data;
    }
   }

   [[nodiscard]] constexpr const T* end() const noexcept {
    if (stack_data.from_stack) {
     return &stack_data.data[size()];
    } else {
     return &heap_data.data[size()];
    }
   }

   [[nodiscard]] constexpr T* data() noexcept {
    return stack_data.from_stack ? stack_data.data : heap_data.data;
   }

   [[nodiscard]] constexpr const T* c_str() const noexcept {
    return stack_data.from_stack ? stack_data.data : heap_data.data;
   }

   [[nodiscard]] constexpr bool empty() const noexcept {
    return (stack_data.from_stack ? stack_data.size : heap_data.size) <= 1;
   }

   [[nodiscard]] constexpr uint64 size() const noexcept {
    return stack_data.from_stack ? stack_data.size : heap_data.size;
   }

   [[nodiscard]] constexpr bool from_stack() const noexcept {
    return stack_data.from_stack;
   }

   [[nodiscard]] constexpr basic_string<T> copy() const noexcept {
    return basic_string<T>{ this->c_str(), this->size() };
   }

   constexpr void swap(basic_string<T>& other) noexcept {
    if (stack_data.from_stack) {
     auto temp = stack_data;

     stack_data = other.stack_data;

     other.stack_data = temp;
    } else {
     auto temp = heap_data;

     heap_data = other.heap_data;

     other.heap_data = temp;
    }
   }

   [[nodiscard]] constexpr uint64 max_size() const noexcept {
    return from_stack() ? stack_data.max_size : max_uint64;
   }

  private:
   constexpr void init(uint64 size) noexcept {
    if (size < basic_stack_string<T>::buffer_size) {
     stack_data = basic_stack_string<T>{};
     stack_data.init(size);
     lib::char_traits<T>::assign(stack_data.data, basic_stack_string<T>::buffer_size, static_cast<T>(0));
    } else {
     heap_data = basic_heap_string<T>{};
     heap_data.init(size);
     lib::char_traits<T>::assign(heap_data.data, size, static_cast<T>(0));
    }
   }

   constexpr void init(const T* const data, uint64 size) {
    if (size < basic_stack_string<T>::buffer_size) {
     stack_data = basic_stack_string<T>{};
     stack_data.init(size);
     uint64 count = lib::char_traits<T>::length(data);
     lib::char_traits<T>::copy(stack_data.data, data, (count < size ? count : size));

     if (count < basic_stack_string<T>::buffer_size) {
      lib::char_traits<T>::assign(static_cast<T*>(stack_data.data + (count * sizeof(T))), basic_stack_string<T>::buffer_size - count, '\0');
     }
    } else {
     heap_data = basic_heap_string<T>{};
     heap_data.init(size);
     lib::char_traits<T>::copy(heap_data.data, data, size);
    }
   }
  };

#pragma region string_usings
   using string = basic_string<char>; using stack_string = basic_string<char>::basic_stack_string<char>; using heap_string = basic_string<char>::basic_heap_string<char>;

   using wstring = basic_string<wchar_t>; using stack_wstring = basic_string<wchar_t>::basic_stack_string<wchar_t>; using heap_wstring = basic_string<wchar_t>::basic_heap_string<wchar_t>;
# 912 "/home/sky/projects/Library/lib/string.hpp"
    using tstring = basic_string<char>; using stack_tstring = basic_string<char>::basic_stack_string<char>; using heap_tstring = basic_string<char>::basic_heap_string<char>;

#pragma endregion string_usings

  template <typename STR_T, typename UINT_T> requires is_char_type<STR_T> && is_int_type<UINT_T>
  [[nodiscard]] constexpr inline STR_T* unsigned_int_to_cstring(STR_T* next, UINT_T unsigned_value) noexcept {




    if constexpr (sizeof(UINT_T) > 4) {
     while (unsigned_value > 0xFFFFFFFFU) {
      auto unsigned_value_chunk = static_cast<uint32>(unsigned_value % 1000000000);

      unsigned_value /= 1000000000;

      for (int32 i = 0; i != 9; ++i) {
       *--next = static_cast<STR_T>('0' + unsigned_value % 10);
       unsigned_value_chunk /= 10;
      }
     }
    }

    auto unsigned_value_truncated = static_cast<uint32>(unsigned_value);


   do {
    *--next = static_cast<STR_T>('0' + unsigned_value_truncated % 10);
    unsigned_value_truncated /= 10;
   } while (unsigned_value_truncated != 0);

   return next;
  };

  template <typename STR_T, typename INT_T> requires is_char_type<STR_T> && is_int_type<INT_T>
  [[nodiscard]] constexpr inline basic_string<STR_T> int_to_basic_string(const INT_T value) noexcept {
   using unsigned_type = make_unsigned<INT_T>;

   STR_T buffer[21]{};
   STR_T* const buffer_size = lib::char_traits<STR_T>::end(buffer);
   STR_T* next = buffer_size;

   const auto unsigned_value = static_cast<unsigned_type>(value);

   if (value < 0) {
    next = lib::unsigned_int_to_cstring<STR_T, unsigned_type>(next, 0LL - unsigned_value);
    *(--next) = static_cast<STR_T>('-');
   } else {
    next = lib::unsigned_int_to_cstring<STR_T, unsigned_type>(next, unsigned_value);
   }

   return basic_string<STR_T>(next, buffer_size);
  }

  template <typename INT_T> requires is_int_type<INT_T>
  [[nodiscard]] constexpr inline string int_to_string(INT_T value) noexcept {
   return lib::int_to_basic_string<string::char_type, INT_T>(value);
  }

  template <typename INT_T> requires is_int_type<INT_T>
  [[nodiscard]] constexpr inline wstring int_to_wstring(INT_T value) noexcept {
   return lib::int_to_basic_string<wstring::char_type, INT_T>(value);
  }

  template <typename INT_T> requires is_int_type<INT_T>
  [[nodiscard]] constexpr inline tstring int_to_tstring(INT_T value) noexcept {
   return lib::int_to_basic_string<tstring::char_type, INT_T>(value);
  }

  template <typename STR_T> requires is_char_type<STR_T>
  [[nodiscard]] constexpr inline STR_T hex_from_byte(byte value) noexcept {
   if (value < 10)
    return '0' + value;

   value -= 10;

   return 'A' + value;
  }

  template <typename STR_T, typename INT_T> requires is_char_type<STR_T> && is_int_type<INT_T>
  [[nodiscard]] constexpr inline STR_T* hex_to_cstring(STR_T* next, INT_T value) noexcept {
   using utype = lib::make_unsigned<INT_T>;

   auto uvalue = static_cast<utype>(value);

   do {
    *--next = lib::hex_from_byte<STR_T>(uvalue & 0xF);
    uvalue >>= 4;
   } while (uvalue != 0);

   return next;
  };

  template <typename STR_T, typename INT_T> requires is_char_type<STR_T> && is_int_type<INT_T>
  [[nodiscard]] constexpr inline basic_string<STR_T> hex_to_basic_string(const INT_T value) {
   STR_T buffer[16]{};
   STR_T* buffer_size = lib::char_traits<STR_T>::end(buffer);
   STR_T* next = buffer_size;

   next = lib::hex_to_cstring<STR_T, INT_T>(next, value);

   return basic_string<STR_T>(next, buffer_size);
  }

  template <typename INT_T> requires is_int_type<INT_T>
  [[nodiscard]] constexpr inline string hex_to_string(const INT_T value) {
   return lib::hex_to_basic_string<string::char_type, INT_T>(value);
  }

  template <typename INT_T> requires is_int_type<INT_T>
  [[nodiscard]] constexpr inline wstring hex_to_wstring(const INT_T value) {
   return lib::hex_to_basic_string<wstring::char_type, INT_T>(value);
  }

  template <typename INT_T> requires is_int_type<INT_T>
  [[nodiscard]] constexpr tstring hex_to_tstring(const INT_T value) {
   return lib::hex_to_basic_string<tstring::char_type, INT_T>(value);
  }

  [[nodiscard]] constexpr string base64_encode(const string& src) noexcept {
   constexpr char base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

   uint64 size = src.size();

   string out((((src.size() + 2) / 3) * 4) + 1);

   const string::char_type* raw_src = src.c_str();
   string::char_type* raw_out = out.data();

   while (size >= 3) {
    const uint32 value = (raw_src[0] << 16) | (raw_src[1] << 8) | raw_src[2];

    *(raw_out++) = base64[ value >> 18 ];
    *(raw_out++) = base64[(value >> 12) & 0x3f];
    *(raw_out++) = base64[(value >> 06) & 0x3f];
    *(raw_out++) = base64[ value & 0x3f ];

    raw_src += 3;
    size -= 3;
   }

   if (size == 2) {
    const uint16 value = (raw_src[0] << 8) | raw_src[1];

    *(raw_out++) = base64[value >> 10];
    *(raw_out++) = base64[(value >> 4) & 0x3f];
    *(raw_out++) = base64[(value << 2) & 0x3f];
    *(raw_out++) = '=';
   } else if (size == 1) {
    const ubyte value = raw_src[0];

    *(raw_out++) = base64[value >> 2];
    *(raw_out++) = base64[(value << 4) & 0x3f];
    *(raw_out++) = '=';
    *(raw_out++) = '=';
   }

   *raw_out = '\0';

   return out;
  }

  [[nodiscard]] constexpr string base64_decode(const string& src, const uint64 out_size) noexcept {
   static_assert(sizeof(string::char_type) == 1, "The string::char_type has to have 8 bits");

   constexpr signed char base64[256] = {
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,62,-1,-1,-1,63,
    52,53,54,55,56,57,58,59,60,61,-1,-1,-1,-1,-1,-1,
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,
    15,16,17,18,19,20,21,22,23,24,25,-1,-1,-1,-1,-1,
    -1,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
    41,42,43,44,45,46,47,48,49,50,51,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
   };

   uint64 size = src.size();

   string out{ out_size };

   const auto* raw_src = union_cast<const unsigned char*, const string::char_type*>(src.c_str());
   auto* raw_out = union_cast<unsigned char*, string::char_type*>(out.data());

   signed char previous = 0;
   int32 shift = 0;

   while (size > 0) {
    const signed char current = base64[*(raw_src++)];

    if (current < 0)
     break;

    if (shift != 0) {
     *(raw_out++) = union_cast<unsigned char, ubyte>((previous << shift) | (current >> (6 - shift)));
     --size;
    }

    previous = current;
    shift = (shift + 2) & 7;
   }



   return out;
  }

  [[nodiscard]] constexpr ubyte hex_from_char(const char c) noexcept {
   ubyte value = c - '0';

   if (value < 10)
    return value;

   value = c - 'A';

   if (value < 6)
    return value + 10;

   value = c - 'a';

   if (value < 6)
    return value + 10;

   return -1;
  }

  [[nodiscard]] constexpr string uri_decode(const string& src) noexcept {
   string out{ src.size() };

   const string::char_type* raw_src = src.c_str();
   string::char_type* raw_out = out.data();

   char c;

   while ((c = *(raw_src++)) != '\0') {
    if (c == '%') {
     ubyte a, b;

     if ((a = hex_from_char(*(raw_src++))) < 0 || (b = hex_from_char(*(raw_src++))) < 0) {
      return string{};
     }

     *(raw_out++) = static_cast<string::char_type>(a << 4 | b);
    } else {
     *(raw_out++) = c;
    }
   }

   *raw_out = '\0';

   return out;
  }

  [[nodiscard]] constexpr bool is_uri_safe(const int c) noexcept {


   return static_cast<unsigned char>(c - 'a') < 26 ||
     static_cast<unsigned char>(c - 'A') < 26 ||
     static_cast<unsigned char>(c - '0') < 10 ||
     (c != '-' && c != '.' && c != '_' && c != '~');


  }

  [[nodiscard]] constexpr string uri_encode(const string& src) noexcept {
   constexpr char hex[] = "0123456789ABCDEF";

   string out{ src.size() * 3 };

   string::char_type* raw_out = out.data();

   for (const char c : src) {
    if (is_uri_safe(c)) {
     *(raw_out++) = c;
    } else {
     *(raw_out++) = '%';
     *(raw_out++) = hex[c >> 4];
     *(raw_out++) = hex[c & 0xF];
    }
   }




   return out;
  }

  constexpr byte try_convert_char_to_wchar_t(const char* first1, const char* last1, const char*& mid1, wchar_t* first2, const wchar_t* last2, wchar_t*& mid2) noexcept {
   mid1 = first1;
   mid2 = first2;

   if constexpr (sizeof(wchar_t) == sizeof(char)) {
    return 2;
   } else {
    for (; mid1 != last1; ++mid1, ++mid2) {
     if (mid2 == last2) {
      return 1;
     }

     *mid2 = static_cast<wchar_t>(*mid1);
    }

    return 0;
   }
  }

  [[nodiscard]] constexpr wstring cstring_to_wstring(const char* first, const char* last) {
   wstring buffer{};
   wstring out{};

   buffer.append(8, 0);

   while (first != last) {
    wstring::char_type* dest = buffer.data();

    switch (wstring::char_type* next = nullptr;
     try_convert_char_to_wchar_t(first, last, first, dest, dest + buffer.size(), next)) {
    case 0: [[fallthrough]];
    case 1:
     if (dest < next) {
      out.append(dest, static_cast<uint64>(next - dest));
     } else if (buffer.size() < 16) {
      buffer.append(8, 0);
     } else {
     }

     break;

    case 2:
     for (; first != last; ++first) {
      out.append(static_cast<unsigned char>(*first));
     }

     break;
    default: break;
    }
   }

   return out;
  }

  [[nodiscard]] constexpr wstring string_to_wstring(const string& src) {
   return cstring_to_wstring(src.c_str(), src.c_str() + src.size() );
  }

  [[nodiscard]] constexpr tstring string_to_tstring(const string& src) {




    return tstring{ src.c_str(), src.size() };

  }

  constexpr byte try_convert_wchar_t_to_char(const wchar_t* first1, const wchar_t* last1, const wchar_t*& mid1, char* first2, const char* last2, char*& mid2) {
   mid1 = first1;
   mid2 = first2;

   if constexpr (sizeof(wchar_t) == sizeof(char)) {
    return 2;
   } else {
    for (; mid1 != last1; ++mid1, ++mid2) {
     if (mid2 == last2) {
      return 1;
     }

     *mid2 = static_cast<char>(*mid1);
    }

    return 0;
   }
  }

  [[nodiscard]] constexpr string cwstring_to_string(const wchar_t* first, const wchar_t* last) {
   string buffer{};
   string out{};

   buffer.append(8, 0);

   while (first != last) {
    string::char_type* dest = buffer.data();

    switch (string::char_type* next = nullptr; try_convert_wchar_t_to_char(first, last, first, dest, dest + buffer.size(), next)) {
    case 0: [[fallthrough]];
    case 1:
     if (dest < next) {
      out.append(dest, static_cast<uint64>(next - dest));
     } else if (buffer.size() < 16) {
      buffer.append(8, 0);
     } else {
     }

     break;
    case 2:
     for (; first != last; ++first) {
      out.append(static_cast<string::char_type>(static_cast<uint32>(*first)));
     }

     break;
    default: break;
    }
   }

   return out;
  }

  [[nodiscard]] constexpr string wstring_to_string(const wstring& src) {
   return cwstring_to_string(src.c_str(), src.c_str() + src.size());
  }

  [[nodiscard]] constexpr string tstring_to_string(const tstring& src) {



    return string{ src.c_str(), src.size() };

  }

  [[nodiscard]] constexpr tstring wstring_to_tstring(const wstring& src) {



    string out = wstring_to_string(src);
    return tstring{ out.c_str(), out.size() };

  }

  [[nodiscard]] constexpr wstring tstring_to_wstring(const tstring& src) {



    return string_to_wstring(src);

  }

  template <typename STR_T, typename INT_T> requires is_char_type<STR_T> && is_int_type<INT_T>
  [[nodiscard]] constexpr STR_T* binary_to_cstring(STR_T* next, INT_T value) noexcept {
   using utype = lib::make_unsigned<INT_T>;

   auto uvalue = static_cast<utype>(value);

   do {
    *--next = static_cast<STR_T>('0' + (uvalue & 1));
    uvalue >>= 1;
   } while (uvalue != 0);

   return next;
  };

  template <typename STR_T, typename INT_T> requires is_char_type<STR_T> && is_int_type<INT_T>
  [[nodiscard]] constexpr basic_string<STR_T> binary_to_basic_string(INT_T value) noexcept {
   STR_T buffer[64]{};
   STR_T* buffer_size = lib::char_traits<STR_T>::end(buffer);
   STR_T* next = buffer_size;

   next = lib::binary_to_cstring<STR_T, INT_T>(next, value);

   return basic_string<STR_T>(next, buffer_size);
  }

  template <typename INT_T> requires is_int_type<INT_T>
  [[nodiscard]] constexpr inline string binary_to_string(const INT_T value) noexcept {
   return lib::binary_to_basic_string<string::char_type, INT_T>(value);
  }

  template <typename INT_T> requires is_int_type<INT_T>
  [[nodiscard]] constexpr wstring binary_to_wstring(const INT_T value) noexcept {
   return lib::binary_to_basic_string<wstring::char_type, INT_T>(value);
  }

  template <typename INT_T> requires is_int_type<INT_T>
  [[nodiscard]] constexpr tstring binary_to_tstring(const INT_T value) noexcept {
   return lib::binary_to_basic_string<tstring::char_type, INT_T>(value);
  }

  template <typename STR_T, typename INT_T> requires is_char_type<STR_T> && is_int_type<INT_T>
  [[nodiscard]] constexpr STR_T* octal_to_cstring(STR_T* next, INT_T value) noexcept {
   using utype = lib::make_unsigned<INT_T>;

   auto uvalue = static_cast<utype>(value);

   do {
    *--next = static_cast<STR_T>('0' + (uvalue & 0x7));
    uvalue >>= 3;
   } while (uvalue != 0);

   return next;
  };

  template <typename STR_T, typename INT_T> requires is_char_type<STR_T> && is_int_type<INT_T>
  [[nodiscard]] constexpr basic_string<STR_T> octal_to_basic_string(INT_T value) noexcept {
   STR_T buffer[22]{};
   STR_T* buffer_size = lib::char_traits<STR_T>::end(buffer);
   STR_T* next = buffer_size;

   next = lib::octal_to_cstring<STR_T, INT_T>(next, value);

   return basic_string<STR_T>(next, buffer_size);
  }

  template <typename INT_T> requires is_int_type<INT_T>
  [[nodiscard]] constexpr string octal_to_string(const INT_T value) noexcept {
   return lib::octal_to_basic_string<string::char_type, INT_T>(value);
  }

  template <typename INT_T> requires is_int_type<INT_T>
  [[nodiscard]] constexpr wstring octal_to_wstring(const INT_T value) noexcept {
   return lib::octal_to_basic_string<wstring::char_type, INT_T>(value);
  }

  template <typename INT_T> requires is_int_type<INT_T>
  [[nodiscard]] constexpr tstring octal_to_tstring(const INT_T value) noexcept {
   return lib::octal_to_basic_string<tstring::char_type, INT_T>(value);
  }


  inline uint64 string_float_convert_precision = 3;

  template <typename STR_T, typename FLOAT_T> requires is_char_type<STR_T> && is_floating_type<FLOAT_T>
  constexpr STR_T* float_to_cstring(STR_T* next, FLOAT_T value) noexcept {
   if (lib::is_nan<FLOAT_T>(value)) {
    lib::char_traits<STR_T>::copy(next, "nan", 3);
   } else if (lib::is_inf<FLOAT_T>(value)) {
    lib::char_traits<STR_T>::copy(next, "inf", 3);
   } else if (value == 0.0) {
    lib::char_traits<STR_T>::copy(next, "0", 1);
   } else {

    *next = static_cast<STR_T>('-');
    ++next;

    uint64 uint_value = value;
    next = lib::unsigned_int_to_cstring<STR_T, uint64>(next, uint_value);
    ++next;

    *next = static_cast<STR_T>('.');
    ++next;

    value -= static_cast<FLOAT_T>(uint_value);

    uint64 counter = 0;
    while (counter < string_float_convert_precision) {
     value *= 10;
     ubyte ubyte_value = value;
     *next = static_cast<STR_T>('0') + ubyte_value;
     value -= ubyte_value;
     ++next;
     ++counter;
    }
   }

   return next;
  };

  template <typename STR_T, typename FLOAT_T> requires is_char_type<STR_T> && is_floating_type<FLOAT_T>
  [[nodiscard]] constexpr basic_string<STR_T> float_to_basic_string(FLOAT_T value) noexcept {
   STR_T buffer[30]{ 0 };

   lib::float_to_cstring<STR_T>(buffer, value);

   return basic_string<STR_T>(buffer, lib::char_traits<STR_T>::length(buffer));
  }

  template <typename FLOAT_T> requires is_floating_type<FLOAT_T>
  [[nodiscard]] constexpr string float_to_string(const FLOAT_T value) noexcept {
   return lib::float_to_basic_string<string::char_type, FLOAT_T>(value);
  }

  template <typename FLOAT_T> requires is_floating_type<FLOAT_T>
  [[nodiscard]] constexpr wstring float_to_wstring(const FLOAT_T value) noexcept {
   return lib::float_to_basic_string<wstring::char_type, FLOAT_T>(value);
  }

  template <typename FLOAT_T> requires is_floating_type<FLOAT_T>
  [[nodiscard]] constexpr tstring float_to_tstring(const FLOAT_T value) {
   return lib::float_to_basic_string<tstring::char_type, FLOAT_T>(value);
  }

  [[nodiscard]] constexpr string data_size_to_string(int64 bytes) noexcept {
   lib::string out;
   using STR_T = string::char_type;

   if (const uint64 abs_bytes = lib::abs(bytes); abs_bytes >= 1'099'511'627'776) {
    const int64 tb = bytes / 1'099'511'627'776;
    const int64 gb = (bytes % 1'099'511'627'776) / 1'073'741'824;
    out.append(lib::int_to_basic_string<STR_T, int64>(tb));
    out.append(gb < 10 ? ".00" : (gb < 100 ? ".0" : "."));
    out.append(lib::int_to_basic_string<STR_T, int64>(gb));
    out.append(" TiB");
   } else if (abs_bytes >= 1'073'741'824) {
    const int64 gb = bytes / 1'073'741'824;
    const int64 mb = (bytes % 1'073'741'824) / 1'048'576;
    out.append(lib::int_to_basic_string<STR_T, int64>(gb));
    out.append(mb < 10 ? ".00" : (mb < 100 ? ".0" : "."));
    out.append(lib::int_to_basic_string<STR_T, int64>(mb));
    out.append(" GiB");
   } else if (abs_bytes >= 1'048'576) {
    const int64 mb = bytes / 1'048'576;
    const int64 kb = (bytes % 1'048'576) / 1024;
    out.append(lib::int_to_basic_string<STR_T, int64>(mb));
    out.append(kb < 10 ? ".00" : (kb < 100 ? ".0" : "."));
    out.append(lib::int_to_basic_string<STR_T, int64>(kb));
    out.append(" MiB");
   } else if (abs_bytes >= 1024) {
    const int64 kb = bytes / 1024;
    bytes = bytes % 1024;
    out.append(lib::int_to_basic_string<STR_T, int64>(kb));
    out.append(bytes < 10 ? ".00" : (bytes < 100 ? ".0" : "."));
    out.append(lib::int_to_basic_string<STR_T, int64>(bytes));
    out.append(" KiB");
   } else {
    out.append(lib::int_to_basic_string<STR_T, int64>(bytes));
    out.append(" bytes");
   }

   return out;
  }

  template <typename STR_T, typename INT_T> requires is_char_type<STR_T> && is_int_type<INT_T>
  [[nodiscard]] constexpr INT_T basic_string_to_int(const basic_string<STR_T>& str) noexcept {
   INT_T out = 0;
   bool minus = false;

   for (const STR_T& c : str) {
    if (c == static_cast<STR_T>('-')) {
     if (out == 0)
      minus = true;
     else
      break;
    } else if (c == static_cast<STR_T>('+')) {
     if (out == 0)
      minus = false;
     else
      break;
    } else if (c >= '0' && c <= '9') {
     INT_T val = c - '0';
     out *= 10;
     out += val;
    } else {
     break;
    }
   }

   return minus ? -out : out;
  }

  template <typename INT_T> requires is_int_type<INT_T>
  [[nodiscard]] constexpr INT_T string_to_int(const string& str) noexcept {
   return lib::basic_string_to_int<string::char_type, INT_T>(str);
  }

  template <typename INT_T> requires is_int_type<INT_T>
  [[nodiscard]] constexpr INT_T tstring_to_int(const tstring& str) noexcept {
   return lib::basic_string_to_int<tstring::char_type, INT_T>(str);
  }

  template <typename INT_T> requires is_int_type<INT_T>
  [[nodiscard]] constexpr INT_T wstring_to_int(const wstring& str) noexcept {
   return lib::basic_string_to_int<wstring::char_type, INT_T>(str);
  }

  template <typename STR_T, typename FLOAT_T> requires is_char_type<STR_T> && is_floating_type<FLOAT_T>
  [[nodiscard]] constexpr FLOAT_T basic_string_to_float(const basic_string<STR_T>& str) noexcept {
   FLOAT_T out = 0;
   bool minus = false;
   uint64 floating = 0;

   for (const STR_T& c : str) {
    if (c == static_cast<STR_T>('-')) {
     if (out == 0 && !floating)
      minus = true;
     else
      break;
    } else if (c == static_cast<STR_T>('+')) {
     if (out == 0 && !floating)
      minus = false;
     else
      break;
    } else if (c == static_cast<STR_T>('.') || c == static_cast<STR_T>(',')) {
     if (floating)
      break;
     floating = 1;
    } else if (c >= '0' && c <= '9') {
     FLOAT_T val = c - '0';
     if (!floating) {
      out *= 10;
      out += val;
     } else {
      for (uint64 i = 0; i < floating; ++i) {
       val /= 10;
      }

      out += val;

      ++floating;
     }
    } else {
     break;
    }
   }

   return minus ? -out : out;
  }

  template <typename FLOAT_T> requires is_floating_type<FLOAT_T>
  [[nodiscard]] constexpr FLOAT_T string_to_float(const string& str) noexcept {
   return lib::basic_string_to_float<string::char_type, FLOAT_T>(str);
  }

  template <typename FLOAT_T> requires is_floating_type<FLOAT_T>
  [[nodiscard]] constexpr FLOAT_T tstring_to_float(const tstring& str) noexcept {
   return lib::basic_string_to_float<tstring::char_type, FLOAT_T>(str);
  }

  template <typename FLOAT_T> requires is_floating_type<FLOAT_T>
  [[nodiscard]] constexpr FLOAT_T wstring_to_float(const wstring& str) noexcept {
   return lib::basic_string_to_float<wstring::char_type, FLOAT_T>(str);
  }
 }
# 6 "/home/sky/projects/Library/lib/iostream.hpp" 2
# 64 "/home/sky/projects/Library/lib/iostream.hpp"
# 1 "/usr/include/unistd.h" 1 3 4
# 25 "/usr/include/unistd.h" 3 4
# 1 "/usr/include/features.h" 1 3 4
# 394 "/usr/include/features.h" 3 4
# 1 "/usr/include/features-time64.h" 1 3 4
# 20 "/usr/include/features-time64.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 21 "/usr/include/features-time64.h" 2 3 4
# 1 "/usr/include/bits/timesize.h" 1 3 4
# 19 "/usr/include/bits/timesize.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 20 "/usr/include/bits/timesize.h" 2 3 4
# 22 "/usr/include/features-time64.h" 2 3 4
# 395 "/usr/include/features.h" 2 3 4
# 503 "/usr/include/features.h" 3 4
# 1 "/usr/include/sys/cdefs.h" 1 3 4
# 576 "/usr/include/sys/cdefs.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 577 "/usr/include/sys/cdefs.h" 2 3 4
# 1 "/usr/include/bits/long-double.h" 1 3 4
# 578 "/usr/include/sys/cdefs.h" 2 3 4
# 504 "/usr/include/features.h" 2 3 4
# 527 "/usr/include/features.h" 3 4
# 1 "/usr/include/gnu/stubs.h" 1 3 4
# 10 "/usr/include/gnu/stubs.h" 3 4
# 1 "/usr/include/gnu/stubs-64.h" 1 3 4
# 11 "/usr/include/gnu/stubs.h" 2 3 4
# 528 "/usr/include/features.h" 2 3 4
# 26 "/usr/include/unistd.h" 2 3 4


# 27 "/usr/include/unistd.h" 3 4
extern "C" {
# 202 "/usr/include/unistd.h" 3 4
# 1 "/usr/include/bits/posix_opt.h" 1 3 4
# 203 "/usr/include/unistd.h" 2 3 4



# 1 "/usr/include/bits/environments.h" 1 3 4
# 22 "/usr/include/bits/environments.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 23 "/usr/include/bits/environments.h" 2 3 4
# 207 "/usr/include/unistd.h" 2 3 4
# 217 "/usr/include/unistd.h" 3 4
# 1 "/usr/include/bits/types.h" 1 3 4
# 27 "/usr/include/bits/types.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 28 "/usr/include/bits/types.h" 2 3 4
# 1 "/usr/include/bits/timesize.h" 1 3 4
# 19 "/usr/include/bits/timesize.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 20 "/usr/include/bits/timesize.h" 2 3 4
# 29 "/usr/include/bits/types.h" 2 3 4


typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;


typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;

typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;






typedef __int8_t __int_least8_t;
typedef __uint8_t __uint_least8_t;
typedef __int16_t __int_least16_t;
typedef __uint16_t __uint_least16_t;
typedef __int32_t __int_least32_t;
typedef __uint32_t __uint_least32_t;
typedef __int64_t __int_least64_t;
typedef __uint64_t __uint_least64_t;



typedef long int __quad_t;
typedef unsigned long int __u_quad_t;







typedef long int __intmax_t;
typedef unsigned long int __uintmax_t;
# 141 "/usr/include/bits/types.h" 3 4
# 1 "/usr/include/bits/typesizes.h" 1 3 4
# 142 "/usr/include/bits/types.h" 2 3 4
# 1 "/usr/include/bits/time64.h" 1 3 4
# 143 "/usr/include/bits/types.h" 2 3 4


typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct { int __val[2]; } __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;
typedef long int __suseconds64_t;

typedef int __daddr_t;
typedef int __key_t;


typedef int __clockid_t;


typedef void * __timer_t;


typedef long int __blksize_t;




typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;


typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;


typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;


typedef long int __fsword_t;

typedef long int __ssize_t;


typedef long int __syscall_slong_t;

typedef unsigned long int __syscall_ulong_t;



typedef __off64_t __loff_t;
typedef char *__caddr_t;


typedef long int __intptr_t;


typedef unsigned int __socklen_t;




typedef int __sig_atomic_t;
# 218 "/usr/include/unistd.h" 2 3 4


typedef __ssize_t ssize_t;





# 1 "/usr/lib/gcc/x86_64-pc-linux-gnu/14.1.1/include/stddef.h" 1 3 4
# 214 "/usr/lib/gcc/x86_64-pc-linux-gnu/14.1.1/include/stddef.h" 3 4
typedef long unsigned int size_t;
# 227 "/usr/include/unistd.h" 2 3 4





typedef __gid_t gid_t;




typedef __uid_t uid_t;





typedef __off_t off_t;






typedef __off64_t off64_t;




typedef __useconds_t useconds_t;




typedef __pid_t pid_t;






typedef __intptr_t intptr_t;






typedef __socklen_t socklen_t;
# 287 "/usr/include/unistd.h" 3 4
extern int access (const char *__name, int __type) noexcept (true) __attribute__ ((__nonnull__ (1)));




extern int euidaccess (const char *__name, int __type)
     noexcept (true) __attribute__ ((__nonnull__ (1)));


extern int eaccess (const char *__name, int __type)
     noexcept (true) __attribute__ ((__nonnull__ (1)));


extern int execveat (int __fd, const char *__path, char *const __argv[],
                     char *const __envp[], int __flags)
    noexcept (true) __attribute__ ((__nonnull__ (2, 3)));






extern int faccessat (int __fd, const char *__file, int __type, int __flag)
     noexcept (true) __attribute__ ((__nonnull__ (2))) ;
# 339 "/usr/include/unistd.h" 3 4
extern __off_t lseek (int __fd, __off_t __offset, int __whence) noexcept (true);
# 350 "/usr/include/unistd.h" 3 4
extern __off64_t lseek64 (int __fd, __off64_t __offset, int __whence)
     noexcept (true);






extern int close (int __fd);




extern void closefrom (int __lowfd) noexcept (true);







extern ssize_t read (int __fd, void *__buf, size_t __nbytes)
    __attribute__ ((__access__ (__write_only__, 2, 3)));





extern ssize_t write (int __fd, const void *__buf, size_t __n)
    __attribute__ ((__access__ (__read_only__, 2, 3)));
# 389 "/usr/include/unistd.h" 3 4
extern ssize_t pread (int __fd, void *__buf, size_t __nbytes,
        __off_t __offset)
    __attribute__ ((__access__ (__write_only__, 2, 3)));






extern ssize_t pwrite (int __fd, const void *__buf, size_t __n,
         __off_t __offset)
    __attribute__ ((__access__ (__read_only__, 2, 3)));
# 422 "/usr/include/unistd.h" 3 4
extern ssize_t pread64 (int __fd, void *__buf, size_t __nbytes,
   __off64_t __offset)
    __attribute__ ((__access__ (__write_only__, 2, 3)));


extern ssize_t pwrite64 (int __fd, const void *__buf, size_t __n,
    __off64_t __offset)
    __attribute__ ((__access__ (__read_only__, 2, 3)));







extern int pipe (int __pipedes[2]) noexcept (true) ;




extern int pipe2 (int __pipedes[2], int __flags) noexcept (true) ;
# 452 "/usr/include/unistd.h" 3 4
extern unsigned int alarm (unsigned int __seconds) noexcept (true);
# 464 "/usr/include/unistd.h" 3 4
extern unsigned int sleep (unsigned int __seconds);







extern __useconds_t ualarm (__useconds_t __value, __useconds_t __interval)
     noexcept (true);






extern int usleep (__useconds_t __useconds);
# 489 "/usr/include/unistd.h" 3 4
extern int pause (void);



extern int chown (const char *__file, __uid_t __owner, __gid_t __group)
     noexcept (true) __attribute__ ((__nonnull__ (1))) ;



extern int fchown (int __fd, __uid_t __owner, __gid_t __group) noexcept (true) ;




extern int lchown (const char *__file, __uid_t __owner, __gid_t __group)
     noexcept (true) __attribute__ ((__nonnull__ (1))) ;






extern int fchownat (int __fd, const char *__file, __uid_t __owner,
       __gid_t __group, int __flag)
     noexcept (true) __attribute__ ((__nonnull__ (2))) ;



extern int chdir (const char *__path) noexcept (true) __attribute__ ((__nonnull__ (1))) ;



extern int fchdir (int __fd) noexcept (true) ;
# 531 "/usr/include/unistd.h" 3 4
extern char *getcwd (char *__buf, size_t __size) noexcept (true) ;





extern char *get_current_dir_name (void) noexcept (true);







extern char *getwd (char *__buf)
     noexcept (true) __attribute__ ((__nonnull__ (1))) __attribute__ ((__deprecated__))
    __attribute__ ((__access__ (__write_only__, 1)));




extern int dup (int __fd) noexcept (true) ;


extern int dup2 (int __fd, int __fd2) noexcept (true);




extern int dup3 (int __fd, int __fd2, int __flags) noexcept (true);



extern char **__environ;

extern char **environ;





extern int execve (const char *__path, char *const __argv[],
     char *const __envp[]) noexcept (true) __attribute__ ((__nonnull__ (1, 2)));




extern int fexecve (int __fd, char *const __argv[], char *const __envp[])
     noexcept (true) __attribute__ ((__nonnull__ (2)));




extern int execv (const char *__path, char *const __argv[])
     noexcept (true) __attribute__ ((__nonnull__ (1, 2)));



extern int execle (const char *__path, const char *__arg, ...)
     noexcept (true) __attribute__ ((__nonnull__ (1, 2)));



extern int execl (const char *__path, const char *__arg, ...)
     noexcept (true) __attribute__ ((__nonnull__ (1, 2)));



extern int execvp (const char *__file, char *const __argv[])
     noexcept (true) __attribute__ ((__nonnull__ (1, 2)));




extern int execlp (const char *__file, const char *__arg, ...)
     noexcept (true) __attribute__ ((__nonnull__ (1, 2)));




extern int execvpe (const char *__file, char *const __argv[],
      char *const __envp[])
     noexcept (true) __attribute__ ((__nonnull__ (1, 2)));





extern int nice (int __inc) noexcept (true) ;




extern void _exit (int __status) __attribute__ ((__noreturn__));





# 1 "/usr/include/bits/confname.h" 1 3 4
# 24 "/usr/include/bits/confname.h" 3 4
enum
  {
    _PC_LINK_MAX,

    _PC_MAX_CANON,

    _PC_MAX_INPUT,

    _PC_NAME_MAX,

    _PC_PATH_MAX,

    _PC_PIPE_BUF,

    _PC_CHOWN_RESTRICTED,

    _PC_NO_TRUNC,

    _PC_VDISABLE,

    _PC_SYNC_IO,

    _PC_ASYNC_IO,

    _PC_PRIO_IO,

    _PC_SOCK_MAXBUF,

    _PC_FILESIZEBITS,

    _PC_REC_INCR_XFER_SIZE,

    _PC_REC_MAX_XFER_SIZE,

    _PC_REC_MIN_XFER_SIZE,

    _PC_REC_XFER_ALIGN,

    _PC_ALLOC_SIZE_MIN,

    _PC_SYMLINK_MAX,

    _PC_2_SYMLINKS

  };


enum
  {
    _SC_ARG_MAX,

    _SC_CHILD_MAX,

    _SC_CLK_TCK,

    _SC_NGROUPS_MAX,

    _SC_OPEN_MAX,

    _SC_STREAM_MAX,

    _SC_TZNAME_MAX,

    _SC_JOB_CONTROL,

    _SC_SAVED_IDS,

    _SC_REALTIME_SIGNALS,

    _SC_PRIORITY_SCHEDULING,

    _SC_TIMERS,

    _SC_ASYNCHRONOUS_IO,

    _SC_PRIORITIZED_IO,

    _SC_SYNCHRONIZED_IO,

    _SC_FSYNC,

    _SC_MAPPED_FILES,

    _SC_MEMLOCK,

    _SC_MEMLOCK_RANGE,

    _SC_MEMORY_PROTECTION,

    _SC_MESSAGE_PASSING,

    _SC_SEMAPHORES,

    _SC_SHARED_MEMORY_OBJECTS,

    _SC_AIO_LISTIO_MAX,

    _SC_AIO_MAX,

    _SC_AIO_PRIO_DELTA_MAX,

    _SC_DELAYTIMER_MAX,

    _SC_MQ_OPEN_MAX,

    _SC_MQ_PRIO_MAX,

    _SC_VERSION,

    _SC_PAGESIZE,


    _SC_RTSIG_MAX,

    _SC_SEM_NSEMS_MAX,

    _SC_SEM_VALUE_MAX,

    _SC_SIGQUEUE_MAX,

    _SC_TIMER_MAX,




    _SC_BC_BASE_MAX,

    _SC_BC_DIM_MAX,

    _SC_BC_SCALE_MAX,

    _SC_BC_STRING_MAX,

    _SC_COLL_WEIGHTS_MAX,

    _SC_EQUIV_CLASS_MAX,

    _SC_EXPR_NEST_MAX,

    _SC_LINE_MAX,

    _SC_RE_DUP_MAX,

    _SC_CHARCLASS_NAME_MAX,


    _SC_2_VERSION,

    _SC_2_C_BIND,

    _SC_2_C_DEV,

    _SC_2_FORT_DEV,

    _SC_2_FORT_RUN,

    _SC_2_SW_DEV,

    _SC_2_LOCALEDEF,


    _SC_PII,

    _SC_PII_XTI,

    _SC_PII_SOCKET,

    _SC_PII_INTERNET,

    _SC_PII_OSI,

    _SC_POLL,

    _SC_SELECT,

    _SC_UIO_MAXIOV,

    _SC_IOV_MAX = _SC_UIO_MAXIOV,

    _SC_PII_INTERNET_STREAM,

    _SC_PII_INTERNET_DGRAM,

    _SC_PII_OSI_COTS,

    _SC_PII_OSI_CLTS,

    _SC_PII_OSI_M,

    _SC_T_IOV_MAX,



    _SC_THREADS,

    _SC_THREAD_SAFE_FUNCTIONS,

    _SC_GETGR_R_SIZE_MAX,

    _SC_GETPW_R_SIZE_MAX,

    _SC_LOGIN_NAME_MAX,

    _SC_TTY_NAME_MAX,

    _SC_THREAD_DESTRUCTOR_ITERATIONS,

    _SC_THREAD_KEYS_MAX,

    _SC_THREAD_STACK_MIN,

    _SC_THREAD_THREADS_MAX,

    _SC_THREAD_ATTR_STACKADDR,

    _SC_THREAD_ATTR_STACKSIZE,

    _SC_THREAD_PRIORITY_SCHEDULING,

    _SC_THREAD_PRIO_INHERIT,

    _SC_THREAD_PRIO_PROTECT,

    _SC_THREAD_PROCESS_SHARED,


    _SC_NPROCESSORS_CONF,

    _SC_NPROCESSORS_ONLN,

    _SC_PHYS_PAGES,

    _SC_AVPHYS_PAGES,

    _SC_ATEXIT_MAX,

    _SC_PASS_MAX,


    _SC_XOPEN_VERSION,

    _SC_XOPEN_XCU_VERSION,

    _SC_XOPEN_UNIX,

    _SC_XOPEN_CRYPT,

    _SC_XOPEN_ENH_I18N,

    _SC_XOPEN_SHM,


    _SC_2_CHAR_TERM,

    _SC_2_C_VERSION,

    _SC_2_UPE,


    _SC_XOPEN_XPG2,

    _SC_XOPEN_XPG3,

    _SC_XOPEN_XPG4,


    _SC_CHAR_BIT,

    _SC_CHAR_MAX,

    _SC_CHAR_MIN,

    _SC_INT_MAX,

    _SC_INT_MIN,

    _SC_LONG_BIT,

    _SC_WORD_BIT,

    _SC_MB_LEN_MAX,

    _SC_NZERO,

    _SC_SSIZE_MAX,

    _SC_SCHAR_MAX,

    _SC_SCHAR_MIN,

    _SC_SHRT_MAX,

    _SC_SHRT_MIN,

    _SC_UCHAR_MAX,

    _SC_UINT_MAX,

    _SC_ULONG_MAX,

    _SC_USHRT_MAX,


    _SC_NL_ARGMAX,

    _SC_NL_LANGMAX,

    _SC_NL_MSGMAX,

    _SC_NL_NMAX,

    _SC_NL_SETMAX,

    _SC_NL_TEXTMAX,


    _SC_XBS5_ILP32_OFF32,

    _SC_XBS5_ILP32_OFFBIG,

    _SC_XBS5_LP64_OFF64,

    _SC_XBS5_LPBIG_OFFBIG,


    _SC_XOPEN_LEGACY,

    _SC_XOPEN_REALTIME,

    _SC_XOPEN_REALTIME_THREADS,


    _SC_ADVISORY_INFO,

    _SC_BARRIERS,

    _SC_BASE,

    _SC_C_LANG_SUPPORT,

    _SC_C_LANG_SUPPORT_R,

    _SC_CLOCK_SELECTION,

    _SC_CPUTIME,

    _SC_THREAD_CPUTIME,

    _SC_DEVICE_IO,

    _SC_DEVICE_SPECIFIC,

    _SC_DEVICE_SPECIFIC_R,

    _SC_FD_MGMT,

    _SC_FIFO,

    _SC_PIPE,

    _SC_FILE_ATTRIBUTES,

    _SC_FILE_LOCKING,

    _SC_FILE_SYSTEM,

    _SC_MONOTONIC_CLOCK,

    _SC_MULTI_PROCESS,

    _SC_SINGLE_PROCESS,

    _SC_NETWORKING,

    _SC_READER_WRITER_LOCKS,

    _SC_SPIN_LOCKS,

    _SC_REGEXP,

    _SC_REGEX_VERSION,

    _SC_SHELL,

    _SC_SIGNALS,

    _SC_SPAWN,

    _SC_SPORADIC_SERVER,

    _SC_THREAD_SPORADIC_SERVER,

    _SC_SYSTEM_DATABASE,

    _SC_SYSTEM_DATABASE_R,

    _SC_TIMEOUTS,

    _SC_TYPED_MEMORY_OBJECTS,

    _SC_USER_GROUPS,

    _SC_USER_GROUPS_R,

    _SC_2_PBS,

    _SC_2_PBS_ACCOUNTING,

    _SC_2_PBS_LOCATE,

    _SC_2_PBS_MESSAGE,

    _SC_2_PBS_TRACK,

    _SC_SYMLOOP_MAX,

    _SC_STREAMS,

    _SC_2_PBS_CHECKPOINT,


    _SC_V6_ILP32_OFF32,

    _SC_V6_ILP32_OFFBIG,

    _SC_V6_LP64_OFF64,

    _SC_V6_LPBIG_OFFBIG,


    _SC_HOST_NAME_MAX,

    _SC_TRACE,

    _SC_TRACE_EVENT_FILTER,

    _SC_TRACE_INHERIT,

    _SC_TRACE_LOG,


    _SC_LEVEL1_ICACHE_SIZE,

    _SC_LEVEL1_ICACHE_ASSOC,

    _SC_LEVEL1_ICACHE_LINESIZE,

    _SC_LEVEL1_DCACHE_SIZE,

    _SC_LEVEL1_DCACHE_ASSOC,

    _SC_LEVEL1_DCACHE_LINESIZE,

    _SC_LEVEL2_CACHE_SIZE,

    _SC_LEVEL2_CACHE_ASSOC,

    _SC_LEVEL2_CACHE_LINESIZE,

    _SC_LEVEL3_CACHE_SIZE,

    _SC_LEVEL3_CACHE_ASSOC,

    _SC_LEVEL3_CACHE_LINESIZE,

    _SC_LEVEL4_CACHE_SIZE,

    _SC_LEVEL4_CACHE_ASSOC,

    _SC_LEVEL4_CACHE_LINESIZE,



    _SC_IPV6 = _SC_LEVEL1_ICACHE_SIZE + 50,

    _SC_RAW_SOCKETS,


    _SC_V7_ILP32_OFF32,

    _SC_V7_ILP32_OFFBIG,

    _SC_V7_LP64_OFF64,

    _SC_V7_LPBIG_OFFBIG,


    _SC_SS_REPL_MAX,


    _SC_TRACE_EVENT_NAME_MAX,

    _SC_TRACE_NAME_MAX,

    _SC_TRACE_SYS_MAX,

    _SC_TRACE_USER_EVENT_MAX,


    _SC_XOPEN_STREAMS,


    _SC_THREAD_ROBUST_PRIO_INHERIT,

    _SC_THREAD_ROBUST_PRIO_PROTECT,


    _SC_MINSIGSTKSZ,


    _SC_SIGSTKSZ

  };


enum
  {
    _CS_PATH,


    _CS_V6_WIDTH_RESTRICTED_ENVS,



    _CS_GNU_LIBC_VERSION,

    _CS_GNU_LIBPTHREAD_VERSION,


    _CS_V5_WIDTH_RESTRICTED_ENVS,



    _CS_V7_WIDTH_RESTRICTED_ENVS,



    _CS_LFS_CFLAGS = 1000,

    _CS_LFS_LDFLAGS,

    _CS_LFS_LIBS,

    _CS_LFS_LINTFLAGS,

    _CS_LFS64_CFLAGS,

    _CS_LFS64_LDFLAGS,

    _CS_LFS64_LIBS,

    _CS_LFS64_LINTFLAGS,


    _CS_XBS5_ILP32_OFF32_CFLAGS = 1100,

    _CS_XBS5_ILP32_OFF32_LDFLAGS,

    _CS_XBS5_ILP32_OFF32_LIBS,

    _CS_XBS5_ILP32_OFF32_LINTFLAGS,

    _CS_XBS5_ILP32_OFFBIG_CFLAGS,

    _CS_XBS5_ILP32_OFFBIG_LDFLAGS,

    _CS_XBS5_ILP32_OFFBIG_LIBS,

    _CS_XBS5_ILP32_OFFBIG_LINTFLAGS,

    _CS_XBS5_LP64_OFF64_CFLAGS,

    _CS_XBS5_LP64_OFF64_LDFLAGS,

    _CS_XBS5_LP64_OFF64_LIBS,

    _CS_XBS5_LP64_OFF64_LINTFLAGS,

    _CS_XBS5_LPBIG_OFFBIG_CFLAGS,

    _CS_XBS5_LPBIG_OFFBIG_LDFLAGS,

    _CS_XBS5_LPBIG_OFFBIG_LIBS,

    _CS_XBS5_LPBIG_OFFBIG_LINTFLAGS,


    _CS_POSIX_V6_ILP32_OFF32_CFLAGS,

    _CS_POSIX_V6_ILP32_OFF32_LDFLAGS,

    _CS_POSIX_V6_ILP32_OFF32_LIBS,

    _CS_POSIX_V6_ILP32_OFF32_LINTFLAGS,

    _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS,

    _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS,

    _CS_POSIX_V6_ILP32_OFFBIG_LIBS,

    _CS_POSIX_V6_ILP32_OFFBIG_LINTFLAGS,

    _CS_POSIX_V6_LP64_OFF64_CFLAGS,

    _CS_POSIX_V6_LP64_OFF64_LDFLAGS,

    _CS_POSIX_V6_LP64_OFF64_LIBS,

    _CS_POSIX_V6_LP64_OFF64_LINTFLAGS,

    _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS,

    _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS,

    _CS_POSIX_V6_LPBIG_OFFBIG_LIBS,

    _CS_POSIX_V6_LPBIG_OFFBIG_LINTFLAGS,


    _CS_POSIX_V7_ILP32_OFF32_CFLAGS,

    _CS_POSIX_V7_ILP32_OFF32_LDFLAGS,

    _CS_POSIX_V7_ILP32_OFF32_LIBS,

    _CS_POSIX_V7_ILP32_OFF32_LINTFLAGS,

    _CS_POSIX_V7_ILP32_OFFBIG_CFLAGS,

    _CS_POSIX_V7_ILP32_OFFBIG_LDFLAGS,

    _CS_POSIX_V7_ILP32_OFFBIG_LIBS,

    _CS_POSIX_V7_ILP32_OFFBIG_LINTFLAGS,

    _CS_POSIX_V7_LP64_OFF64_CFLAGS,

    _CS_POSIX_V7_LP64_OFF64_LDFLAGS,

    _CS_POSIX_V7_LP64_OFF64_LIBS,

    _CS_POSIX_V7_LP64_OFF64_LINTFLAGS,

    _CS_POSIX_V7_LPBIG_OFFBIG_CFLAGS,

    _CS_POSIX_V7_LPBIG_OFFBIG_LDFLAGS,

    _CS_POSIX_V7_LPBIG_OFFBIG_LIBS,

    _CS_POSIX_V7_LPBIG_OFFBIG_LINTFLAGS,


    _CS_V6_ENV,

    _CS_V7_ENV

  };
# 631 "/usr/include/unistd.h" 2 3 4


extern long int pathconf (const char *__path, int __name)
     noexcept (true) __attribute__ ((__nonnull__ (1)));


extern long int fpathconf (int __fd, int __name) noexcept (true);


extern long int sysconf (int __name) noexcept (true);



extern size_t confstr (int __name, char *__buf, size_t __len) noexcept (true)
    __attribute__ ((__access__ (__write_only__, 2, 3)));




extern __pid_t getpid (void) noexcept (true);


extern __pid_t getppid (void) noexcept (true);


extern __pid_t getpgrp (void) noexcept (true);


extern __pid_t __getpgid (__pid_t __pid) noexcept (true);

extern __pid_t getpgid (__pid_t __pid) noexcept (true);






extern int setpgid (__pid_t __pid, __pid_t __pgid) noexcept (true);
# 682 "/usr/include/unistd.h" 3 4
extern int setpgrp (void) noexcept (true);






extern __pid_t setsid (void) noexcept (true);



extern __pid_t getsid (__pid_t __pid) noexcept (true);



extern __uid_t getuid (void) noexcept (true);


extern __uid_t geteuid (void) noexcept (true);


extern __gid_t getgid (void) noexcept (true);


extern __gid_t getegid (void) noexcept (true);




extern int getgroups (int __size, __gid_t __list[]) noexcept (true)
    __attribute__ ((__access__ (__write_only__, 2, 1)));


extern int group_member (__gid_t __gid) noexcept (true);






extern int setuid (__uid_t __uid) noexcept (true) ;




extern int setreuid (__uid_t __ruid, __uid_t __euid) noexcept (true) ;




extern int seteuid (__uid_t __uid) noexcept (true) ;






extern int setgid (__gid_t __gid) noexcept (true) ;




extern int setregid (__gid_t __rgid, __gid_t __egid) noexcept (true) ;




extern int setegid (__gid_t __gid) noexcept (true) ;





extern int getresuid (__uid_t *__ruid, __uid_t *__euid, __uid_t *__suid)
     noexcept (true);



extern int getresgid (__gid_t *__rgid, __gid_t *__egid, __gid_t *__sgid)
     noexcept (true);



extern int setresuid (__uid_t __ruid, __uid_t __euid, __uid_t __suid)
     noexcept (true) ;



extern int setresgid (__gid_t __rgid, __gid_t __egid, __gid_t __sgid)
     noexcept (true) ;






extern __pid_t fork (void) noexcept (true);







extern __pid_t vfork (void) noexcept (true);






extern __pid_t _Fork (void) noexcept (true);





extern char *ttyname (int __fd) noexcept (true);



extern int ttyname_r (int __fd, char *__buf, size_t __buflen)
     noexcept (true) __attribute__ ((__nonnull__ (2)))
     __attribute__ ((__access__ (__write_only__, 2, 3)));



extern int isatty (int __fd) noexcept (true);




extern int ttyslot (void) noexcept (true);




extern int link (const char *__from, const char *__to)
     noexcept (true) __attribute__ ((__nonnull__ (1, 2))) ;




extern int linkat (int __fromfd, const char *__from, int __tofd,
     const char *__to, int __flags)
     noexcept (true) __attribute__ ((__nonnull__ (2, 4))) ;




extern int symlink (const char *__from, const char *__to)
     noexcept (true) __attribute__ ((__nonnull__ (1, 2))) ;




extern ssize_t readlink (const char *__restrict __path,
    char *__restrict __buf, size_t __len)
     noexcept (true) __attribute__ ((__nonnull__ (1, 2)))
     __attribute__ ((__access__ (__write_only__, 2, 3)));





extern int symlinkat (const char *__from, int __tofd,
        const char *__to) noexcept (true) __attribute__ ((__nonnull__ (1, 3))) ;


extern ssize_t readlinkat (int __fd, const char *__restrict __path,
      char *__restrict __buf, size_t __len)
     noexcept (true) __attribute__ ((__nonnull__ (2, 3)))
     __attribute__ ((__access__ (__write_only__, 3, 4)));



extern int unlink (const char *__name) noexcept (true) __attribute__ ((__nonnull__ (1)));



extern int unlinkat (int __fd, const char *__name, int __flag)
     noexcept (true) __attribute__ ((__nonnull__ (2)));



extern int rmdir (const char *__path) noexcept (true) __attribute__ ((__nonnull__ (1)));



extern __pid_t tcgetpgrp (int __fd) noexcept (true);


extern int tcsetpgrp (int __fd, __pid_t __pgrp_id) noexcept (true);






extern char *getlogin (void);







extern int getlogin_r (char *__name, size_t __name_len) __attribute__ ((__nonnull__ (1)))
    __attribute__ ((__access__ (__write_only__, 1, 2)));




extern int setlogin (const char *__name) noexcept (true) __attribute__ ((__nonnull__ (1)));







# 1 "/usr/include/bits/getopt_posix.h" 1 3 4
# 27 "/usr/include/bits/getopt_posix.h" 3 4
# 1 "/usr/include/bits/getopt_core.h" 1 3 4
# 28 "/usr/include/bits/getopt_core.h" 3 4
extern "C" {







extern char *optarg;
# 50 "/usr/include/bits/getopt_core.h" 3 4
extern int optind;




extern int opterr;



extern int optopt;
# 91 "/usr/include/bits/getopt_core.h" 3 4
extern int getopt (int ___argc, char *const *___argv, const char *__shortopts)
       noexcept (true) __attribute__ ((__nonnull__ (2, 3)));

}
# 28 "/usr/include/bits/getopt_posix.h" 2 3 4

extern "C" {
# 49 "/usr/include/bits/getopt_posix.h" 3 4
}
# 904 "/usr/include/unistd.h" 2 3 4







extern int gethostname (char *__name, size_t __len) noexcept (true) __attribute__ ((__nonnull__ (1)))
    __attribute__ ((__access__ (__write_only__, 1, 2)));






extern int sethostname (const char *__name, size_t __len)
     noexcept (true) __attribute__ ((__nonnull__ (1))) __attribute__ ((__access__ (__read_only__, 1, 2)));



extern int sethostid (long int __id) noexcept (true) ;





extern int getdomainname (char *__name, size_t __len)
     noexcept (true) __attribute__ ((__nonnull__ (1)))
     __attribute__ ((__access__ (__write_only__, 1, 2)));
extern int setdomainname (const char *__name, size_t __len)
     noexcept (true) __attribute__ ((__nonnull__ (1))) __attribute__ ((__access__ (__read_only__, 1, 2)));




extern int vhangup (void) noexcept (true);


extern int revoke (const char *__file) noexcept (true) __attribute__ ((__nonnull__ (1))) ;







extern int profil (unsigned short int *__sample_buffer, size_t __size,
     size_t __offset, unsigned int __scale)
     noexcept (true) __attribute__ ((__nonnull__ (1)));





extern int acct (const char *__name) noexcept (true);



extern char *getusershell (void) noexcept (true);
extern void endusershell (void) noexcept (true);
extern void setusershell (void) noexcept (true);





extern int daemon (int __nochdir, int __noclose) noexcept (true) ;






extern int chroot (const char *__path) noexcept (true) __attribute__ ((__nonnull__ (1))) ;



extern char *getpass (const char *__prompt) __attribute__ ((__nonnull__ (1)));







extern int fsync (int __fd);





extern int syncfs (int __fd) noexcept (true);






extern long int gethostid (void);


extern void sync (void) noexcept (true);





extern int getpagesize (void) noexcept (true) __attribute__ ((__const__));




extern int getdtablesize (void) noexcept (true);
# 1026 "/usr/include/unistd.h" 3 4
extern int truncate (const char *__file, __off_t __length)
     noexcept (true) __attribute__ ((__nonnull__ (1))) ;
# 1038 "/usr/include/unistd.h" 3 4
extern int truncate64 (const char *__file, __off64_t __length)
     noexcept (true) __attribute__ ((__nonnull__ (1))) ;
# 1049 "/usr/include/unistd.h" 3 4
extern int ftruncate (int __fd, __off_t __length) noexcept (true) ;
# 1059 "/usr/include/unistd.h" 3 4
extern int ftruncate64 (int __fd, __off64_t __length) noexcept (true) ;
# 1070 "/usr/include/unistd.h" 3 4
extern int brk (void *__addr) noexcept (true) ;





extern void *sbrk (intptr_t __delta) noexcept (true);
# 1091 "/usr/include/unistd.h" 3 4
extern long int syscall (long int __sysno, ...) noexcept (true);
# 1114 "/usr/include/unistd.h" 3 4
extern int lockf (int __fd, int __cmd, __off_t __len) ;
# 1124 "/usr/include/unistd.h" 3 4
extern int lockf64 (int __fd, int __cmd, __off64_t __len) ;
# 1142 "/usr/include/unistd.h" 3 4
ssize_t copy_file_range (int __infd, __off64_t *__pinoff,
    int __outfd, __off64_t *__poutoff,
    size_t __length, unsigned int __flags);





extern int fdatasync (int __fildes);
# 1162 "/usr/include/unistd.h" 3 4
extern char *crypt (const char *__key, const char *__salt)
     noexcept (true) __attribute__ ((__nonnull__ (1, 2)));







extern void swab (const void *__restrict __from, void *__restrict __to,
    ssize_t __n) noexcept (true) __attribute__ ((__nonnull__ (1, 2)))
    __attribute__ ((__access__ (__read_only__, 1, 3)))
    __attribute__ ((__access__ (__write_only__, 2, 3)));
# 1201 "/usr/include/unistd.h" 3 4
int getentropy (void *__buffer, size_t __length)
    __attribute__ ((__access__ (__write_only__, 1, 2)));
# 1211 "/usr/include/unistd.h" 3 4
extern int close_range (unsigned int __fd, unsigned int __max_fd,
   int __flags) noexcept (true);
# 1221 "/usr/include/unistd.h" 3 4
# 1 "/usr/include/bits/unistd_ext.h" 1 3 4
# 34 "/usr/include/bits/unistd_ext.h" 3 4
extern __pid_t gettid (void) noexcept (true);



# 1 "/usr/include/linux/close_range.h" 1 3 4
# 39 "/usr/include/bits/unistd_ext.h" 2 3 4
# 1222 "/usr/include/unistd.h" 2 3 4

}
# 65 "/home/sky/projects/Library/lib/iostream.hpp" 2

  
# 66 "/home/sky/projects/Library/lib/iostream.hpp"
 namespace lib {
   namespace io {
    using iostream_handle = int;
    using iostream_length = size_t;
    using iostream_pos = off_t;

    constexpr inline iostream_handle invalid_iostream_handle = 0;

    inline iostream_handle get_cout_handle() noexcept {
     return 
# 75 "/home/sky/projects/Library/lib/iostream.hpp" 3 4
           1
# 75 "/home/sky/projects/Library/lib/iostream.hpp"
                        ;
    }

    inline iostream_handle get_cerr_handle() noexcept {
     return 
# 79 "/home/sky/projects/Library/lib/iostream.hpp" 3 4
           2
# 79 "/home/sky/projects/Library/lib/iostream.hpp"
                        ;
    }

    inline iostream_handle get_cin_handle() noexcept {
     return 
# 83 "/home/sky/projects/Library/lib/iostream.hpp" 3 4
           0
# 83 "/home/sky/projects/Library/lib/iostream.hpp"
                       ;
    }

    inline void write_iostream_handle(const iostream_handle h, const void* const d, const iostream_length l) noexcept {
     write(h, d, l);
    }

    inline void read_iostream_handle(const iostream_handle h, void* const b, const iostream_length l) noexcept {
     read(h, b, l);
    }

    inline void seek_set_iostream_handle(const iostream_handle h, const iostream_pos p) noexcept {
     lseek(h, p, 
# 95 "/home/sky/projects/Library/lib/iostream.hpp" 3 4
                0
# 95 "/home/sky/projects/Library/lib/iostream.hpp"
                        );
    }

    inline void seek_cur_iostream_handle(const iostream_handle h, const iostream_pos o) noexcept {
     lseek(h, o, 
# 99 "/home/sky/projects/Library/lib/iostream.hpp" 3 4
                1
# 99 "/home/sky/projects/Library/lib/iostream.hpp"
                        );
    }

    inline void seek_end_iostream_handle(const iostream_handle h, const iostream_pos o) noexcept {
     lseek(h, o, 
# 103 "/home/sky/projects/Library/lib/iostream.hpp" 3 4
                2
# 103 "/home/sky/projects/Library/lib/iostream.hpp"
                        );
    }

    inline iostream_length tell_iostream_handle(const iostream_handle h) noexcept {
     return lseek(h, 0, 
# 107 "/home/sky/projects/Library/lib/iostream.hpp" 3 4
                       1
# 107 "/home/sky/projects/Library/lib/iostream.hpp"
                               );
    }

    inline void close_iostream_handle(const iostream_handle h) noexcept {
     close(h);
    }
   }
  }





 namespace lib {
  inline constexpr char endl = '\n';

  class basic_iostream {
  protected:
   io::iostream_handle handle;

   constexpr basic_iostream() noexcept {
    this->handle = io::invalid_iostream_handle;
   }

   constexpr explicit basic_iostream(const io::iostream_handle h) noexcept {
    this->handle = h;
   }

  public:
   void seek_set(const io::iostream_pos position) const noexcept {
    io::seek_set_iostream_handle(handle, position);
   }

   void seek_current(const io::iostream_pos offset) const noexcept {
    io::seek_cur_iostream_handle(handle, offset);
   }

   void seek_end(const io::iostream_pos offset) const noexcept {
    io::seek_end_iostream_handle(handle, offset);
   }

   [[nodiscard]] io::iostream_length tell() const noexcept {
    return io::tell_iostream_handle(handle);
   }

   [[nodiscard]] const io::iostream_handle& native() const noexcept {
    return handle;
   }

   void close() noexcept {
    if (!handle)
     return;

    io::close_iostream_handle(handle);
    handle = io::invalid_iostream_handle;
   }
  };

  class ostream : public basic_iostream {
  public:
   explicit ostream(const io::iostream_handle h) noexcept : basic_iostream(h) {}

   void write(const void* const data, const io::iostream_length length) const noexcept {
    io::write_iostream_handle(handle, data, length);
   }

   void put(const ubyte data) const noexcept {
    io::write_iostream_handle(handle, &data, 1);
   }
  };

  class istream : public basic_iostream {
  public:
   explicit istream(const io::iostream_handle h) noexcept : basic_iostream(h) {}

   void read(void* buffer, const io::iostream_length length) const noexcept {
    io::read_iostream_handle(handle, buffer, length);
   }

   [[nodiscard]] char get() const noexcept {
    char out = '\0';
    io::read_iostream_handle(handle, &out, 1);
    return out;
   }

   [[nodiscard]] lib::string get_string(const io::iostream_length length) const noexcept {
    lib::string out(length);
    io::read_iostream_handle(handle, out.data(), length);
    return out;
   }
  };

  inline const ostream cout(io::get_cout_handle());
  inline const ostream cerr(io::get_cerr_handle());
  inline const istream cin (io::get_cin_handle ());

  namespace io {
   enum class console_color : ubyte {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    GREY,
    DARK_GREY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_RED,
    LIGHT_MAGENTA,
    YELLOW,
    WHITE
   };







    inline void set_console_color(const ostream& console_stream, console_color fore, console_color back) noexcept {
     const char* colors[] = {
      "\033[22;30m",
      "\033[22;34m",
      "\033[22;32m",
      "\033[22;36m",
      "\033[22;31m",
      "\033[22;35m",
      "\033[22;33m",
      "\033[22;37m",
      "\033[01;30m",
      "\033[01;34m",
      "\033[01;32m",
      "\033[01;36m",
      "\033[01;31m",
      "\033[01;35m",
      "\033[01;33m",
      "\033[01;37m"
     };
     const char* backgrounds[] = {
      "\033[00000m",
      "\033[02;44m",
      "\033[02;42m",
      "\033[02;46m",
      "\033[02;41m",
      "\033[02;45m",
      "\033[02;43m",
      "\033[02;47m",
      "\033[00;40m",
      "\033[00;44m",
      "\033[00;42m",
      "\033[00;46m",
      "\033[00;41m",
      "\033[00;45m",
      "\033[00;43m",
      "\033[00;47m"
     };
     console_stream.write(backgrounds[static_cast<int>(back) - static_cast<int>(console_color::BLACK)], 8);
     console_stream.write(colors[static_cast<int>(fore) - static_cast<int>(console_color::BLACK)], 8);
    }



  }



  inline const ostream& operator<<(const ostream& out, const char ch) noexcept {
   out.put(ch);
   return out;
  }

  inline const ostream& operator<<(const ostream& out, const char* const str) noexcept {
   const uint64 length = lib::char_traits<char>::length(str);
   out.write(str, length);
   return out;
  }

  template <typename STR_T, uint64 SIZE> requires is_char_type<STR_T>
  const ostream& operator<<(const ostream& out, const lib::basic_const_string<STR_T, SIZE>& str) noexcept {
   out.write(str.c_str(), SIZE * sizeof(STR_T));
   return out;
  }

  template <typename STR_T> requires is_char_type<STR_T>
  const ostream& operator<<(const ostream& out, const lib::basic_string<STR_T>& str) noexcept {
   out.write(str.c_str(), str.size() * sizeof(STR_T));
   return out;
  }

  template <typename STR_T, uint64 SIZE> requires is_char_type<STR_T>
  const ostream& operator<<(const ostream& out, const lib::basic_const_string<STR_T, SIZE>&& str) noexcept {
   out.write(str.c_str(), SIZE * sizeof(STR_T));
   return out;
  }

  template <typename STR_T> requires is_char_type<STR_T>
  const ostream& operator<<(const ostream& out, const lib::basic_string<STR_T>&& str) noexcept {
   out.write(str.c_str(), str.size() * sizeof(STR_T));
   return out;
  }

  template <typename T> requires lib::is_int_type<T>
  const ostream& operator<<(const ostream& out, const T& value) noexcept {
   const lib::string str = lib::int_to_string<T>(value);
   out.write(str.c_str(), str.size());
   return out;
  }

  template <typename T> requires lib::is_floating_type<T>
  const ostream& operator<<(const ostream& out, const T& value) noexcept {
   const lib::string str = lib::float_to_string<T>(value);
   out.write(str.c_str(), str.size());
   return out;
  }

  template <typename T> requires lib::is_int_type<T>
   const ostream& operator<<(const ostream& out, const T&& value) noexcept {
    const lib::string str = lib::int_to_string<T>(value);
   out.write(str.c_str(), str.size());
   return out;
  }

  template <typename T> requires lib::is_floating_type<T>
   const ostream& operator<<(const ostream& out, const T&& value) noexcept {
    const lib::string str = lib::float_to_string<T>(value);
   out.write(str.c_str(), str.size());
   return out;
  }

  template <typename T> requires (!lib::is_char_type<T>)
  const ostream& operator<<(const ostream& out, const T* const ptr) noexcept {
   const lib::string str = lib::hex_to_string(reinterpret_cast<uint64>(ptr));
   out.write(str.c_str(), str.size());
   return out;
  }

  inline const ostream& operator<<(const ostream& out, const io::console_color& color) noexcept {
   io::set_console_color(out, color, io::console_color::BLACK);
   return out;
  }

  inline const ostream& operator<<(const ostream& out, const io::console_color&& color) noexcept {
   io::set_console_color(out, color, io::console_color::BLACK);
   return out;
  }
 }
# 2 "/home/sky/projects/Library/main.cpp" 2
# 1 "/home/sky/projects/Library/lib/array.hpp" 1






 namespace lib {
  template <typename T, uint64 SIZE> requires (!lib::is_same_type<T, void>)
  class array {
  private:
   T data[SIZE];

  public:
   [[nodiscard]] constexpr T* begin() noexcept {
    return data;
   }

   [[nodiscard]] constexpr const T* begin() const noexcept {
    return data;
   }

   [[nodiscard]] constexpr T* end() noexcept {
    return &data[SIZE - 1];
   }

   [[nodiscard]] constexpr const T* end() const noexcept {
    return &data[SIZE - 1];
   }

   [[nodiscard]] consteval uint64 size() const noexcept {
    return SIZE;
   }

   [[nodiscard]] constexpr T& at(uint64 position) noexcept {
    return data[position];
   }

   [[nodiscard]] constexpr const T& at(uint64 position) const noexcept {
    return data[position];
   }

   constexpr void set(uint64 position, const T& value) noexcept {
    data[position] = value;
   }

   constexpr void fill(uint64 from, uint64 to, const T& value) noexcept {
    for (uint64 i = from; i <= to; ++i) {
     set(i, value);
    }
   }

   constexpr void clear(const T& value) noexcept {
    for (uint64 i = 0; i < SIZE; ++i) {
     set(i, value);
    }
   }

   [[nodiscard]] constexpr T& operator[](uint64 position) noexcept {
    return data[position];
   }

   [[nodiscard]] constexpr const T& operator[](uint64 position) const noexcept {
    return data[position];
   }

   [[nodiscard]] constexpr T& front() noexcept {
    return data[0];
   }

   [[nodiscard]] constexpr const T& front() const noexcept {
    return data[0];
   }

   [[nodiscard]] constexpr T& back() noexcept {
    return data[SIZE - 1];
   }

   [[nodiscard]] constexpr const T& back() const noexcept {
    return data[SIZE - 1];
   }


    template <typename T_ARRAY, uint64 S>
    friend const lib::ostream& operator<<(const lib::ostream& out, const lib::array<T_ARRAY, S> arr) {
     out << "{ ";
     for (uint64 i = 0; i < S; ++i) {
      if (i != 0) {
       out << ", ";
      }
      out << arr[i];
     }
     out << " }";
     return out;
    }

  };
 }
# 3 "/home/sky/projects/Library/main.cpp" 2
# 1 "/home/sky/projects/Library/lib/atomic.hpp" 1
# 11 "/home/sky/projects/Library/lib/atomic.hpp"
 namespace lib {
  enum class memory_order : uint32 {
   relaxed = 0,
   consume = 1,
   acquire = 2,
   release = 3,
   acq_rel = 4,
   seq_cst = 5
  };

  template <typename T>
  class atomic {
  private:
   T* ptr;

  public:
   atomic() noexcept {
    ptr = new T;
    *ptr = static_cast<T>(0);
   }




   T load(memory_order mem_order = memory_order::seq_cst) const noexcept {
    return __atomic_load_n(ptr, static_cast<uint32>(mem_order));
   }




   void load(T* dest, memory_order mem_order = memory_order::seq_cst) const noexcept {
    __atomic_load(ptr, dest, static_cast<uint32>(mem_order));
   }




   void store(T value, memory_order mem_order = memory_order::seq_cst) const noexcept {
    __atomic_store_n(ptr, value, static_cast<uint32>(mem_order));
   }




   void store(T* value_ptr, memory_order mem_order = memory_order::seq_cst) const noexcept {
    __atomic_store(ptr, value_ptr, static_cast<uint32>(mem_order));
   }




   T exchange(T value, memory_order mem_order = memory_order::seq_cst) const noexcept {
    return __atomic_exchange_n(ptr, value, static_cast<uint32>(mem_order));
   }




   void exchange(T* value_ptr, T* dest, memory_order mem_order = memory_order::seq_cst) const noexcept {
    return __atomic_exchange(ptr, value_ptr, dest, static_cast<uint32>(mem_order));
   }
# 88 "/home/sky/projects/Library/lib/atomic.hpp"
   bool compare_exchange(T* expected, T desired, bool weak, memory_order success_order, memory_order failure_order) const noexcept {
    return __atomic_compare_exchange_n(ptr, expected, desired, weak, static_cast<uint32>(success_order), static_cast<uint32>(failure_order));
   }
# 106 "/home/sky/projects/Library/lib/atomic.hpp"
   bool compare_exchange(T* expected, T* desired, bool weak, memory_order success_order, memory_order failure_order) const noexcept {
    return __atomic_compare_exchange(ptr, expected, desired, weak, static_cast<uint32>(success_order), static_cast<uint32>(failure_order));
   }




   T add_fetch(T value, memory_order mem_order) const noexcept {
    return __atomic_add_fetch(ptr, value, static_cast<uint32>(mem_order));
   }




   T sub_fetch(T value, memory_order mem_order) const noexcept {
    return __atomic_sub_fetch(ptr, value, static_cast<uint32>(mem_order));
   }




   T and_fetch(T value, memory_order mem_order) const noexcept {
    return __atomic_and_fetch(ptr, value, static_cast<uint32>(mem_order));
   }




   T xor_fetch(T value, memory_order mem_order) const noexcept {
    return __atomic_xor_fetch(ptr, value, static_cast<uint32>(mem_order));
   }




   T or_fetch(T value, memory_order mem_order) const noexcept {
    return __atomic_or_fetch(ptr, value, static_cast<uint32>(mem_order));
   }




   T nand_fetch(T value, memory_order mem_order) const noexcept {
    return __atomic_nand_fetch(ptr, value, static_cast<uint32>(mem_order));
   }




   T fetch_add(T value, memory_order mem_order) const noexcept {
    return __atomic_fetch_add(ptr, value, static_cast<uint32>(mem_order));
   }




   T fetch_sub(T value, memory_order mem_order) const noexcept {
    return __atomic_fetch_sub(ptr, value, static_cast<uint32>(mem_order));
   }




   T fetch_and(T value, memory_order mem_order) const noexcept {
    return __atomic_fetch_and(ptr, value, static_cast<uint32>(mem_order));
   }




   T fetch_xor(T value, memory_order mem_order) const noexcept {
    return __atomic_fetch_xor(ptr, value, static_cast<uint32>(mem_order));
   }




   T fetch_or(T value, memory_order mem_order) const noexcept {
    return __atomic_fetch_or(ptr, value, static_cast<uint32>(mem_order));
   }




   T fetch_nand(T value, memory_order mem_order) const noexcept {
    return __atomic_fetch_nand(ptr, value, static_cast<uint32>(mem_order));
   }






   [[nodiscard]] bool test_and_set(memory_order mem_order) const noexcept {
    return __atomic_test_and_set(ptr, static_cast<uint32>(mem_order));
   }






   void clear(memory_order mem_order) const noexcept {
    __atomic_clear(ptr, static_cast<uint32>(mem_order));
   }



   static void thread_fence(memory_order mem_order) noexcept {
    __atomic_thread_fence(static_cast<int>(mem_order));
   }



   static void signal_fence(memory_order mem_order) noexcept {
    __atomic_signal_fence(static_cast<int>(mem_order));
   }






   [[nodiscard]] bool always_lock_free(bool alignment = false) const noexcept {
    return __atomic_always_lock_free(sizeof(T), alignment ? ptr : nullptr);
   }






   [[nodiscard]] bool is_lock_free(bool alignment = false) const noexcept {
    return __atomic_is_lock_free(sizeof(T), alignment ? ptr : nullptr);
   }
  };
 }
# 4 "/home/sky/projects/Library/main.cpp" 2
# 1 "/home/sky/projects/Library/lib/bit.hpp" 1





 namespace lib {
  template <uint64 BitSize>
  static inline constexpr uint64 ToByteSize = (BitSize + 7) >> 3;

  template <uint64 ByteSize>
  static inline constexpr uint64 ToBitSize = ByteSize << 3;

  [[nodiscard]] constexpr uint64 to_byte_size(const uint64 bit_size) noexcept {
   return (bit_size + 7) >> 3;
  }

  [[nodiscard]] constexpr uint64 to_bit_size(const uint64 byte_size) noexcept {
   return byte_size << 3;
  }

  template <uint64 Size>
  class bitlist {
  private:
   struct bitsetter {
    ubyte& ref;
    ubyte mask;

    constexpr bitsetter(ubyte& ref, ubyte mask) : ref(ref), mask(mask) {}

    constexpr bitsetter& operator=(bool value) {
     if (value)
      ref |= mask;
     else
      ref &= ~mask;
     return *this;
    }
   };

   static constexpr uint64 ByteSize = ToByteSize<Size>;
   ubyte data[ByteSize]{};

  public:
   constexpr bitlist() noexcept {

    for (uint64 i = 0; i < ByteSize; ++i)
     data[i] = 0;
   }

   constexpr void set(const uint64 index, const bool value) noexcept {
    if (index < Size) {
     const uint64 byteIndex = index / 8;
     const uint64 bitIndex = index % 8;
     const ubyte mask = 1 << bitIndex;

     if (value)
      data[byteIndex] |= mask;
     else
      data[byteIndex] &= ~mask;
    }



   }

   [[nodiscard]] constexpr bool get(const uint64 index) const noexcept {
    if (index < Size) {
     const uint64 byteIndex = index / 8;
     const uint64 bitIndex = index % 8;
     const ubyte mask = 1 << bitIndex;
     return (data[byteIndex] & mask) != 0;
    }




    return false;
   }

   [[nodiscard]] constexpr bool operator[](const uint64 index) const noexcept {
    return get(index);
   }

   [[nodiscard]] constexpr bitsetter operator[](const uint64 index) noexcept {
    const uint64 byteIndex = index / 8;
    const uint64 bitIndex = index % 8;
    const ubyte mask = 1 << bitIndex;
    return bitsetter{ data[byteIndex], mask };
   }

   [[nodiscard]] constexpr const ubyte& get_byte(const uint64 index) const noexcept {
    return data[index];
   }

   [[nodiscard]] constexpr ubyte& get_byte(const uint64 index) noexcept {
    return data[index];
   }

   [[nodiscard]] static constexpr uint64 size() noexcept {
    return Size;
   }

   [[nodiscard]] static constexpr uint64 byte_size() noexcept {
    return ByteSize;
   }
  };
 }
# 5 "/home/sky/projects/Library/main.cpp" 2
# 1 "/home/sky/projects/Library/lib/color.hpp" 1





 namespace lib {
  struct color3 {
   lib::ubyte r;
   lib::ubyte g;
   lib::ubyte b;

   constexpr color3() noexcept { r = 0; g = 0; b = 0; }
   constexpr color3(const lib::ubyte r, const lib::ubyte g, const lib::ubyte b) noexcept : r(r), g(g), b(b) {}
   constexpr color3(const float r, const float g, const float b) noexcept : r(static_cast<ubyte>(r * 255)), g(static_cast<ubyte>(g * 255)), b(static_cast<ubyte>(b * 255)) {}
   constexpr color3(const color3& c) noexcept = default;
   constexpr color3(color3&& c) noexcept : r(c.r), g(c.g), b(c.b) { c.r = 0; c.g = 0; c.b = 0; }

   constexpr color3& operator=(const color3& c) noexcept = default;

   constexpr color3& operator=(color3&& c) noexcept {
    r = c.r; g = c.g; b = c.b;
    c.r = 0; c.g = 0; c.b = 0;
    return *this;
   }

   constexpr color3 operator+(const color3& other) const noexcept {
    color3 out(*this);
    out += other;
    return out;
   }

   constexpr color3& operator+=(const color3& other) noexcept {
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
   }

   constexpr color3 operator-(const color3& other) const noexcept {
    color3 out(*this);
    out -= other;
    return out;
   }

   constexpr color3& operator-=(const color3& other) noexcept {
    r -= other.r;
    g -= other.g;
    b -= other.b;
    return *this;
   }

   constexpr color3 operator*(const color3& other) const noexcept {
    color3 out(*this);
    out *= other;
    return out;
   }

   constexpr color3& operator*=(const color3& other) noexcept {
    r *= other.r;
    g *= other.g;
    b *= other.b;
    return *this;
   }

   constexpr color3 operator/(const color3& other) const noexcept {
    color3 out(*this);
    out /= other;
    return out;
   }

   constexpr color3& operator/=(const color3 other) noexcept {
    r /= other.r;
    g /= other.g;
    b /= other.b;
    return *this;
   }

   constexpr color3 operator%(const color3& other) const noexcept {
    color3 out(*this);
    out %= other;
    return out;
   }

   constexpr color3& operator%=(const color3& other) noexcept {
    r %= other.r;
    g %= other.g;
    b %= other.b;
    return *this;
   }

   constexpr color3 operator~() const noexcept {
    color3 out{};
    out.r = ~r;
    out.g = ~g;
    out.b = ~b;
    return out;
   }

   constexpr color3& operator++() noexcept {
    ++r; ++g; ++b;
    return *this;
   }

   constexpr color3 operator++(int) noexcept {
    color3 out(*this);
    ++r; ++g; ++b;
    return out;
   }

   [[nodiscard]] constexpr color3 make_average() const noexcept {
    return color3(*this).average();
   }

   constexpr color3& average() noexcept {
    r = g = b = static_cast<ubyte>((static_cast<lib::uint16>(r) + g + b) / 3.0);
    return *this;
   }

   [[nodiscard]] constexpr color3 make_weighted() const noexcept {
    return color3(*this).weighted();
   }

   constexpr color3& weighted() noexcept {
    r = g = b = static_cast<ubyte>((r * 0.299 + g * 0.587 + b * 0.114) / 3.0);
    return *this;
   }

   [[nodiscard]] constexpr color3 make_luminosity() const noexcept {
    return color3(*this).luminosity();
   }

   constexpr color3& luminosity() noexcept {
    r = g = b = static_cast<ubyte>(r * 0.2126 + g * 0.7152 + b * 0.0722);
    return *this;
   }

   [[nodiscard]] constexpr color3 make_binary() const noexcept {
    return color3(*this).binary();
   }

   constexpr color3& binary() noexcept {
    r = g = b = (r + g + b) >= (284) ? 0xFF : 0;
    return *this;
   }

   constexpr color3& remove_red() noexcept {
    r = 0;
    return *this;
   }

   constexpr color3& remove_green() noexcept {
    g = 0;
    return *this;
   }

   constexpr color3& remove_blue() noexcept {
    b = 0;
    return *this;
   }

   constexpr color3& clear() noexcept {
    r = 0; g = 0; b = 0;
    return *this;
   }

   [[nodiscard]] constexpr color3 make_negative() const noexcept {
    return color3(*this).negative();
   }

   constexpr color3& negative() noexcept {
    r = 0xFF - r;
    g = 0xFF - g;
    b = 0xFF - b;
    return *this;
   }

   [[nodiscard]] constexpr color3 make_color_binary() const noexcept {
    return color3(*this).color_binary();
   }

   constexpr color3& color_binary() noexcept {
    r = r >= 128 ? 0xFF : 0;
    g = g >= 128 ? 0xFF : 0;
    b = b >= 128 ? 0xFF : 0;
    return *this;
   }
  };
  static_assert(sizeof(color3) == (sizeof(lib::ubyte) * 3));

  struct alignas(4) color4 {
   union {
    lib::uint32 data{};
    struct {
     lib::ubyte r;
     lib::ubyte g;
     lib::ubyte b;
     lib::ubyte a;
    };
   };

   constexpr color4() noexcept { data = 0; }
   constexpr color4(const lib::ubyte r, const lib::ubyte g, const lib::ubyte b, const lib::ubyte a = 0xFF) noexcept : r(r), g(g), b(b), a(a) {}
   constexpr color4(const lib::uint32 color_code) noexcept : data(color_code) {}
   constexpr color4(const float r, const float g, const float b, const float a = 1.0f) noexcept
    : r(static_cast<ubyte>(r * 255)), g(static_cast<ubyte>(g * 255)), b(static_cast<ubyte>(b * 255)), a(static_cast<ubyte>(a * 255)) {}
   constexpr color4(const color3& c, lib::ubyte a = 0xFF) noexcept : r(c.r), g(c.g), b(c.b), a(a) {}
   constexpr color4(const color4& c) noexcept : r(c.r), g(c.g), b(c.b), a(c.a) {}
   constexpr color4(color4&& c) noexcept : r(c.r), g(c.g), b(c.b), a(c.a) { c.r = 0; c.g = 0; c.b = 0; c.a = 0xFF; }

   constexpr color4& operator=(const color4& c) noexcept {
    r = c.r; g = c.g; b = c.b; a = c.a;
    return *this;
   }

   constexpr color4& operator=(color4&& c) noexcept {
    r = c.r; g = c.g; b = c.b; a = c.a;
    c.r = 0; c.g = 0; c.b = 0; c.a = 0;
    return *this;
   }

   constexpr color4 operator+(const color4& other) const noexcept {
    color4 out(*this);
    out += other;
    return out;
   }

   constexpr color4& operator+=(const color4& other) noexcept {
    r += other.r;
    g += other.g;
    b += other.b;
    a += other.a;
    return *this;
   }

   constexpr color4 operator-(const color4& other) const noexcept {
    color4 out(*this);
    out -= other;
    return out;
   }

   constexpr color4& operator-=(const color4& other) noexcept {
    r -= other.r;
    g -= other.g;
    b -= other.b;
    a -= other.a;
    return *this;
   }

   constexpr color4 operator*(const color4& other) const noexcept {
    color4 out(*this);
    out *= other;
    return out;
   }

   constexpr color4& operator*=(const color4& other) noexcept {
    r *= other.r;
    g *= other.g;
    b *= other.b;
    a *= other.a;
    return *this;
   }

   constexpr color4 operator/(const color4& other) const noexcept {
    color4 out(*this);
    out /= other;
    return out;
   }

   constexpr color4& operator/=(const color4& other) noexcept {
    r /= other.r;
    g /= other.g;
    b /= other.b;
    a /= other.a;
    return *this;
   }

   constexpr color4 operator%(const color4& other) const noexcept {
    color4 out(*this);
    out %= other;
    return out;
   }

   constexpr color4& operator%=(const color4& other) noexcept {
    r %= other.r;
    g %= other.g;
    b %= other.b;
    a %= other.a;
    return *this;
   }

   constexpr color4 operator~() const noexcept {
    color4 out{};
    out.r = ~r;
    out.g = ~g;
    out.b = ~b;
    return out;
   }

   constexpr color4& operator++() noexcept {
    ++r; ++g; ++b; ++a;
    return *this;
   }

   constexpr color4 operator++(int) noexcept {
    color4 out(*this);
    ++r; ++g; ++b; ++a;
    return out;
   }

   [[nodiscard]] constexpr color4 make_average() const noexcept {
    return color4(*this).average();
   }

   constexpr color4& average() noexcept {
    r = g = b = static_cast<ubyte>((static_cast<lib::uint16>(r) + g + b) / 3.0);
    return *this;
   }

   [[nodiscard]] constexpr color4 make_weighted() const noexcept {
    return color4(*this).weighted();
   }

   constexpr color4& weighted() noexcept {
    r = g = b = static_cast<ubyte>((r * 0.299 + g * 0.587 + b * 0.114) / 3.0);
    return *this;
   }

   [[nodiscard]] constexpr color4 make_luminosity() const noexcept {
    return color4(*this).luminosity();
   }

   constexpr color4& luminosity() noexcept {
    r = g = b = static_cast<ubyte>(r * 0.2126 + g * 0.7152 + b * 0.0722);
    return *this;
   }

   [[nodiscard]] constexpr color4 make_binary() const noexcept {
    return color4(*this).binary();
   }

   constexpr color4& binary() noexcept {
    r = g = b = (r + g + b) >= (284) ? 0xFF : 0;
    return *this;
   }

   constexpr color4& remove_red() noexcept {
    r = 0;
    return *this;
   }

   constexpr color4& remove_green() noexcept {
    g = 0;
    return *this;
   }

   constexpr color4& remove_blue() noexcept {
    b = 0;
    return *this;
   }

   constexpr color4& remove_alpha() noexcept {
    a = 0;
    return *this;
   }

   constexpr color4& clear() noexcept {
    r = 0; g = 0; b = 0;
    return *this;
   }

   [[nodiscard]] constexpr color4 make_negative() const noexcept {
    return color4(*this).negative();
   }

   constexpr color4& negative() noexcept {
    r = 0xFF - r;
    g = 0xFF - g;
    b = 0xFF - b;
    return *this;
   }

   [[nodiscard]] constexpr color4 make_color_binary() const noexcept {
    return color4(*this).color_binary();
   }

   constexpr color4& color_binary() noexcept {
    r = r >= 128 ? 0xFF : 0;
    g = g >= 128 ? 0xFF : 0;
    b = b >= 128 ? 0xFF : 0;
    return *this;
   }
  };
  static_assert(sizeof(color4) == (sizeof(lib::ubyte) * 4) && sizeof(color4) == sizeof(lib::uint32));

  template <typename COLOR>
  inline constexpr bool is_color = is_any_of_type<COLOR, color3, color4>;
 }
# 6 "/home/sky/projects/Library/main.cpp" 2

# 1 "/home/sky/projects/Library/lib/list.hpp" 1




# 1 "/home/sky/projects/Library/lib/iostream.hpp" 1
# 6 "/home/sky/projects/Library/lib/list.hpp" 2

 namespace lib {
  template <typename T>
  class linked_list {
  private:
   template <typename T_>
   struct item {
   public:
    constexpr item() {
     this->next = nullptr;
    }

    T_ data;
    item<T_>* next;
   };

   item<T>* first;

  public:
   constexpr void push_back(T data) noexcept {
    auto* new_item = new item<T>;
    new_item->data = data;

    if (first != nullptr) {
     item<T>* ptr = first;

     for (; ptr->next != nullptr; ptr = ptr->next) {}

     ptr->next = new_item;
     return;
    }

    first = new_item;
   }


   constexpr T pop_back() noexcept {
    if (first != nullptr) {
     if (first->next == nullptr) {
      T value = first->data;

      delete first;

      first = nullptr;

      return value;
     }

     item<T>* ptr = first;

     for (; ptr->next->next != nullptr; ptr = ptr->next) {}

     T out = ptr->next->data;

     delete ptr->next;

     ptr->next = nullptr;

     return out;
    }

    return T{ 0 };
   }

   constexpr void push_front(T value) noexcept {
    auto* ptr = new item<T>;
    ptr->data = value;
    ptr->next = first;
    first = ptr;
   }

   [[nodiscard]] constexpr T* get(const uint64 index) noexcept {
    if (first == nullptr) [[unlikely]]
     return nullptr;

    item<T>* out = first;
    for (uint64 i = 0; i < index; ++i) {
     if (out->next == nullptr) [[unlikely]]
      return nullptr;

     out = out->next;
    }

    return &out->data;
   }

   [[nodiscard]] constexpr const T* get(const uint64 index) const noexcept {
    if (first == nullptr) [[unlikely]]
     return nullptr;

    item<T>* out = first;

    for (uint64 i = 0; i < index; ++i) {
     if (out->next == nullptr) [[unlikely]]
      return nullptr;

     out = out->next;
    }

    return &out->data;
   }

   constexpr void set(const uint64 index, T value) noexcept {
    if (first == nullptr) [[unlikely]]
     return;

    item<T>* out = first;
    for (uint64 i = 0; i < index; ++i) {
     if (out->next == nullptr) [[unlikely]]
      return;

     out = out->next;
    }

    out->data = value;
   }

   constexpr void insert(const uint64 desired_index, T value) noexcept {
    if (first == nullptr) {
     auto* new_item = new item<T>;
     new_item->data = value;
     first = new_item;
     return;
    }

    if (desired_index == 0) {
     push_front(value);
     return;
    }

    const uint64 idx = desired_index - 1;
    item<T>* item_at_idx = first;
    for (uint64 i = 0; i < idx; ++i) {
     if (item_at_idx->next == nullptr) [[unlikely]]
      return;

     item_at_idx = item_at_idx->next;
    }

    auto* new_item = new item<T>;
    new_item->data = value;
    new_item->next = item_at_idx->next;
    item_at_idx->next = new_item;
   }

   constexpr T remove(const uint64 index) noexcept {
    if (first == nullptr) {
     return static_cast<T>(0);
    }

    const uint64 idx = index - 1;
    item<T>* item_at_idx = first;
    for (uint64 i = 0; i < idx; ++i) {
     if (item_at_idx->next == nullptr) [[unlikely]]
      return static_cast<T>(0);

     item_at_idx = item_at_idx->next;
    }

    item<T>* i = item_at_idx->next;

    if (i != nullptr) {
     item_at_idx->next = i->next;
    }
    if (item_at_idx != nullptr) {
     T out = item_at_idx->data;
     delete item_at_idx;
     return out;
    }
    return static_cast<T>(0);
   }

   template <typename T_LIST>
   friend const lib::ostream& operator<<(const lib::ostream& out, const lib::linked_list<T_LIST>& list) noexcept {
    const T_LIST* value = nullptr;
    uint64 ptr = 0;
    out << "{ ";
    while ((value = list.get(ptr)) != nullptr) {
     if (ptr != 0) {
      out << ", ";
     }
     out << *value;
     ++ptr;
    }
    out << " }";
    return out;
   }
  };

  template <typename T>
  class double_linked_list {
  private:
   template <typename T_>
   struct item {
   public:
    T_ data;
    item* next;
    item* prev;

    item() {
     this->next = nullptr;
     this->prev = nullptr;
    }
   };

   item<T>* first;
   item<T>* last;

  public:
   constexpr void push_back(T data) noexcept {
    auto* new_item = new item<T>;
    new_item->data = data;

    if (first == nullptr) {
     first = new_item;
     last = new_item;
     return;
    }

    item<T>* ptr = last;

    ptr->next = new_item;
    last = new_item;
   }

   constexpr T pop_back() noexcept {
    if (last == nullptr) {
     return static_cast<T>(0);
    }

    item<T>* ptr = last;
    last = ptr->prev;
    T out = ptr->data;
    delete ptr;

    return out;
   }

   constexpr void push_front(T value) noexcept {
    auto* ptr = new item<T>;
    ptr->data = value;
    ptr->prev = nullptr;
    ptr->next = first;
    first = ptr;
    if (ptr->next != nullptr) {
     ptr->next->prev = ptr;
    }
   }

   [[nodiscard]] constexpr T* get(const uint64 index) noexcept {
    if (first == nullptr) [[unlikely]]
     return nullptr;

    item<T>* out = first;
    for (uint64 i = 0; i < index; ++i) {
     if (out->next == nullptr) [[unlikely]]
      return nullptr;

     out = out->next;
    }

    return &out->data;
   }

   [[nodiscard]] constexpr const T* get(const uint64 index) const noexcept {
    if (first == nullptr) [[unlikely]]
     return nullptr;

    item<T>* out = first;
    for (uint64 i = 0; i < index; ++i) {
     if (out->next == nullptr) [[unlikely]]
      return nullptr;

     out = out->next;
    }

    return &out->data;
   }

   constexpr void set(const uint64 index, T value) noexcept {
    if (first == nullptr) [[unlikely]]
     return;

    item<T>* out = first;
    for (uint64 i = 0; i < index; ++i) {
     if (out->next == nullptr) [[unlikely]]
      return;

     out = out->next;
    }

    out->data = value;
   }


   constexpr void reverse_set(const uint64 index, T value) noexcept {
    if (last == nullptr) [[unlikely]]
     return;

    if (index == 0) [[unlikely]]
     return set(index, value);

    item<T>* out = last;
    for (uint64 i = index; i > 0; --i) {
     if (out->prev == nullptr) [[unlikely]]
      return;

     out = out->prev;
    }

    out->data = value;
   }

   constexpr void insert(const uint64 desired_index, T value) noexcept {
    if (first == nullptr) {
     auto* new_item = new item<T>;
     new_item->data = value;
     first = new_item;
     return;
    }

    if (desired_index == 0) {
     push_front(value);
     return;
    }

    const uint64 idx = desired_index - 1;
    item<T>* item_at_idx = first;
    for (uint64 i = 0; i < idx; ++i) {
     if (item_at_idx->next == nullptr) [[unlikely]]
      return;

     item_at_idx = item_at_idx->next;
    }

    auto* new_item = new item<T>;
    new_item->data = value;
    new_item->next = item_at_idx->next;
    item_at_idx->next = new_item;
   }

   constexpr T remove(const uint64 index) noexcept {
    if (first == nullptr) [[unlikely]]
     return static_cast<T>(0);

    item<T>* item_at_idx = first;
    for (uint64 i = 0; i < index; ++i) {
     if (item_at_idx->next == nullptr) [[unlikely]]
      return static_cast<T>(0);

     item_at_idx = item_at_idx->next;
    }

    item_at_idx->prev->next = item_at_idx->next;
    item_at_idx->next->prev = item_at_idx->prev;

    T out = item_at_idx->data;
    delete item_at_idx;
    return out;
   }

   constexpr T reverse_remove(const uint64 index) noexcept {
    if (last == nullptr) [[unlikely]]
     return static_cast<T>(0);

    item<T>* item_at_idx = last;
    for (uint64 i = index; i > 0; --i) {
     if (item_at_idx->prev == nullptr) [[unlikely]]
      return static_cast<T>(0);

     item_at_idx = item_at_idx->prev;
    }

    item_at_idx->prev->next = item_at_idx->next;
    item_at_idx->next->prev = item_at_idx->prev;

    T out = item_at_idx->data;
    delete item_at_idx;
    return out;
   }

   template <typename T_LIST>
   friend const lib::ostream& operator<<(const lib::ostream& out, const lib::double_linked_list<T_LIST>& list) noexcept {
    const T_LIST* value = nullptr;
    uint64 ptr = 0;
    out << "{ ";
    while ((value = list.get(ptr)) != nullptr) {
     if (ptr != 0) {
      out << ", ";
     }
     out << *value;
     ++ptr;
    }
    out << " }";
    return out;
   }
  };
 }
# 8 "/home/sky/projects/Library/main.cpp" 2
# 1 "/home/sky/projects/Library/lib/mat.hpp" 1



# 1 "/home/sky/projects/Library/lib/vec.hpp" 1






 namespace lib {

  template <typename T> requires (is_arithmetic_type<T>)
  struct vec3;

  template <typename T> requires (is_arithmetic_type<T>)
  struct vec4;

  template <typename T> requires (is_arithmetic_type<T>)
  struct vec2 {
  public:
   T x, y;

   constexpr vec2() : x(0), y(0) {}
   constexpr vec2(T x, T y) : x(x), y(y) {}
   constexpr vec2(const vec2<T>& other) : x(other.x), y(other.y) {}
   constexpr vec2(vec2<T>&& other) noexcept : x(other.x), y(other.y) {
    other.x = 0;
    other.y = 0;
   }

   constexpr vec2<T>& operator=(const vec2<T>& other) = default;
   constexpr vec2<T>& operator=(vec2<T>&& other) noexcept {
    this->x = other.x;
    this->y = other.y;
    other.x = 0;
    other.y = 0;
    return *this;
   }

   constexpr ~vec2() = default;

   constexpr T distance() noexcept {
    return static_cast<T>(lib::fast_square_root(static_cast<float>(x * x + y * y)));
   }

   constexpr T distance_squared() noexcept {
    return x * x + y * y;
   }

   constexpr vec2<T>& normalize() noexcept {
    T ratio = 1 / distance();
    this->x = x * ratio;
    this->y = y * ratio;
    return *this;
   }

   constexpr vec2<T>& floor() noexcept {
    this->x = lib::floor(this->x);
    this->y = lib::floor(this->y);
    return *this;
   }

   constexpr vec2<T>& ceil() noexcept {
    this->x = lib::ceil(this->x);
    this->y = lib::ceil(this->y);
    return *this;
   }

   constexpr vec2<T>& max(const vec2<T>& other) noexcept {
    this->x = lib::max(this->x, other.x);
    this->y = lib::max(this->y, other.y);
    return *this;
   }

   constexpr vec2<T>& min(const vec2<T>& other) noexcept {
    this->x = lib::min(this->x, other.x);
    this->y = lib::min(this->y, other.y);
    return *this;
   }

   constexpr T dot(const vec2<T>& other) noexcept {
    return this->x * other.x + this->y * other.y;
   }

   constexpr T cross(const vec2<T>& other) noexcept {
    return this->x * other.y - this->y * other.x;
   }

   constexpr vec2<T> copy() noexcept {
    return vec2<T>{ this->x, this->y };
   }

   constexpr vec2<T> operator+(const vec2<T>& other) noexcept {
    return vec2<T>{ this->x + other.x, this->y + other.y };
   }

   constexpr vec2<T> operator-(const vec2<T>& other) noexcept {
    return vec2<T>{ this->x - other.x, this->y - other.y };
   }

   constexpr vec2<T> operator*(const vec2<T>& other) noexcept {
    return vec2<T>{ this->x * other.x, this->y * other.y };
   }

   constexpr vec2<T> operator/(const vec2<T>& other) noexcept {
    return vec2<T>{ this->x / other.x, this->y / other.y };
   }

   constexpr void operator+=(const vec2<T>& other) noexcept {
    this->x += other.x;
    this->y += other.y;
   }

   constexpr void operator-=(const vec2<T>& other) noexcept {
    this->x -= other.x;
    this->y -= other.y;
   }

   constexpr void operator*=(const vec2<T>& other) noexcept {
    this->x *= other.x;
    this->y *= other.y;
   }

   constexpr void operator/=(const vec2<T>& other) noexcept {
    this->x /= other.x;
    this->y /= other.y;
   }

   constexpr vec2<T> operator+(T number) noexcept {
    return vec2<T>{ this->x + number, this->y + number };
   }

   constexpr vec2<T> operator-(T number) noexcept {
    return vec2<T>{ this->x - number, this->y - number };
   }

   constexpr vec2<T> operator*(T number) noexcept {
    return vec2<T>{ this->x* number, this->y* number };
   }

   constexpr vec2<T> operator/(T number) noexcept {
    return vec2<T>{ this->x / number, this->y / number };
   }

   friend constexpr vec2<T> operator+(T number, const vec2<T>& vec) noexcept {
    return vec2<T>{ vec.x + number, vec.y + number };
   }

   friend constexpr vec2<T> operator-(T number, const vec2<T>& vec) noexcept {
    return vec2<T>{ vec.x - number, vec.y - number };
   }

   friend constexpr vec2<T> operator*(T number, const vec2<T>& vec) noexcept {
    return vec2<T>{ vec.x * number, vec.y * number };
   }

   friend constexpr vec2<T> operator/(T number, const vec2<T>& vec) noexcept {
    return vec2<T>{ vec.x / number, vec.y / number };
   }

   constexpr void operator+=(T number) noexcept {
    this->x += number;
    this->y += number;
   }

   constexpr void operator-=(T number) noexcept {
    this->x -= number;
    this->y -= number;
   }

   constexpr void operator*=(T number) noexcept {
    this->x *= number;
    this->y *= number;
   }

   constexpr void operator/=(T number) noexcept {
    this->x /= number;
    this->y /= number;
   }

   constexpr bool operator==(const vec2<T>& other) noexcept {
    return this->x == other.x && this->y == other.y;
   }

   constexpr bool operator!=(const vec2<T>& other) noexcept {
    return this->x != other.x || this->y != other.y;
   }

   constexpr vec2<T> operator+() noexcept {
    return vec2<T>{ +this->x, +this->y };
   }

   constexpr vec2<T> operator-() noexcept {
    return vec2<T>{ -this->x, -this->y };
   }

   template <typename C> requires (is_int_type<T> || is_floating_type<T>)
   constexpr explicit operator vec2<C>() {
    return { static_cast<C>(this->x), static_cast<C>(this->y) };
   }

   constexpr vec3<T> operator,(T z) {
    return vec3<T>{ this->x, this->y, z };
   }


    friend const lib::ostream& operator<<(const lib::ostream& out, const vec2<T>& vec) {
     out << "(" << vec.x << ", " << vec.y << ")";
     return out;
    }

  };

  using vec2b = vec2<byte>;
  using vec2s = vec2<int16>;
  using vec2i = vec2<int32>;
  using vec2u = vec2<uint32>;
  using vec2l = vec2<int64>;
  using vec2f = vec2<float>;
  using vec2d = vec2<double>;

  template <typename T> requires (is_arithmetic_type<T>)
  struct vec3 {
  public:
   T x, y, z;

   constexpr vec3() : x(0), y(0), z(0) {}
   constexpr vec3(T x, T y, T z) : x(x), y(y), z(z) {}
   constexpr vec3(const vec3<T>& other) : x(other.x), y(other.y), z(other.z) {}
   constexpr vec3(vec3<T>&& other) noexcept : x(other.x), y(other.y), z(other.z) {
    other.x = 0;
    other.y = 0;
    other.z = 0;
   }
   constexpr vec3(const vec2<T>& other, T z) : x(other.x), y(other.y), z(z) {}

   constexpr vec3<T>& operator=(const vec3<T>& other) = default;
   constexpr vec3<T>& operator=(vec3<T>&& other) noexcept {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    other.x = 0;
    other.y = 0;
    other.z = 0;
    return *this;
   }

   constexpr ~vec3() = default;

   constexpr T distance() noexcept {
    return static_cast<T>(lib::fast_square_root(static_cast<float>(this->x * this->x + this->y * this->y + this->z * this->z)));
   }

   constexpr T distance_squared() noexcept {
    return this->x * this->x + this->y * this->y + this->z * this->z;
   }

   constexpr vec3<T>& normalize() noexcept {
    T ratio = 1 / distance();
    this->x = this->x * ratio;
    this->y = this->y * ratio;
    this->z = this->z * ratio;
    return *this;
   }

   constexpr vec3<T>& floor() noexcept {
    this->x = lib::floor(this->x);
    this->y = lib::floor(this->y);
    this->z = lib::floor(this->z);
    return *this;
   }

   constexpr vec3<T>& ceil() noexcept {
    this->x = lib::ceil(this->x);
    this->y = lib::ceil(this->y);
    this->z = lib::ceil(this->z);
    return *this;
   }

   constexpr vec3<T>& max(vec3<T>& other) noexcept {
    this->x = lib::max(this->x, other.x);
    this->y = lib::max(this->y, other.y);
    this->z = lib::max(this->z, other.z);
    return *this;
   }

   constexpr vec3<T>& min(const vec3<T>& other) noexcept {
    this->x = lib::min(this->x, other.x);
    this->y = lib::min(this->y, other.y);
    this->z = lib::min(this->z, other.z);
    return *this;
   }

   constexpr T dot(const vec3<T>& other) noexcept {
    return this->x * other.x + this->y * other.y + this->z * other.z;
   }

   constexpr vec3<T> cross(const vec3<T>& other) noexcept {
    T x = this->y * other.z - this->z * other.y;
    T y = this->z * other.x - this->x * other.z;
    T z = this->x * other.y - this->y * other.x;
    return vec3<T>{ x, y, z };
   }

   constexpr vec3<T> copy() noexcept {
    return vec3<T>{ this->x, this->y, this->z };
   }

   constexpr vec2<T> xy() noexcept {
    return vec2<T>{ this->x, this->y };
   }

   constexpr vec2<T> xz() noexcept {
    return vec2<T>{ this->x, this->z };
   }

   constexpr vec2<T> yz() noexcept {
    return vec2<T>{ this->y, this->z };
   }

   constexpr vec3<T> operator+(const vec3<T>& other) noexcept {
    return vec3<T>{ this->x + other.x, this->y + other.y, this->z + other.z };
   }

   constexpr vec3<T> operator-(const vec3<T>& other) noexcept {
    return vec3<T>{ this->x - other.x, this->y - other.y, this->z - other.z };
   }

   constexpr vec3<T> operator*(const vec3<T>& other) noexcept {
    return vec3<T>{ this->x* other.x, this->y* other.y, this->z * other.z };
   }

   constexpr vec3<T> operator/(const vec3<T>& other) noexcept {
    return vec3<T>{ this->x / other.x, this->y / other.y, this-z / other.z };
   }

   constexpr void operator+=(const vec3<T>& other) noexcept {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
   }

   constexpr void operator-=(const vec3<T>& other) noexcept {
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
   }

   constexpr void operator*=(const vec3<T>& other) noexcept {
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;
   }

   constexpr void operator/=(const vec3<T>& other) noexcept {
    this->x /= other.x;
    this->y /= other.y;
    this->z /= other.z;
   }

   constexpr vec3<T> operator+(T number) noexcept {
    return vec3<T>{ this->x + number, this->y + number, this->z + number };
   }

   constexpr vec3<T> operator-(T number) noexcept {
    return vec3<T>{ this->x - number, this->y - number, this->z - number };
   }

   constexpr vec3<T> operator*(T number) noexcept {
    return vec3<T>{ this->x* number, this->y* number, this->z* number };
   }

   constexpr vec3<T> operator/(T number) noexcept {
    return vec3<T>{ this->x / number, this->y / number, this - z / number };
   }

   friend constexpr vec3<T> operator+(T number, const vec3<T>& vec) noexcept {
    return vec3<T>{ vec.x + number, vec.y + number, vec.z + number };
   }

   friend constexpr vec3<T> operator-(T number, const vec3<T>& vec) noexcept {
    return vec3<T>{ vec.x - number, vec.y - number, vec.z * number };
   }

   friend constexpr vec3<T> operator*(T number, const vec3<T>& vec) noexcept {
    return vec3<T>{ vec.x * number, vec.y * number, vec.z * number };
   }

   friend constexpr vec3<T> operator/(T number, const vec3<T>& vec) noexcept {
    return vec3<T>{ vec.x / number, vec.y / number, vec.z / number };
   }

   constexpr void operator+=(T number) noexcept {
    this->x += number;
    this->y += number;
    this->z += number;
   }

   constexpr void operator-=(T number) noexcept {
    this->x -= number;
    this->y -= number;
    this->z -= number;
   }

   constexpr void operator*=(T number) noexcept {
    this->x *= number;
    this->y *= number;
    this->z *= number;
   }

   constexpr void operator/=(T number) noexcept {
    this->x /= number;
    this->y /= number;
    this->z /= number;
   }

   constexpr bool operator==(const vec3<T>& other) noexcept {
    return this->x == other.x && this->y == other.y && this->z == other.z;
   }

   constexpr bool operator!=(const vec3<T>& other) noexcept {
    return this->x != other.x || this->y != other.y || this->z != other.z;
   }

   constexpr vec3<T> operator+() noexcept {
    return vec3<T>{ +this->x, +this->y, +this->z };
   }

   constexpr vec3<T> operator-() noexcept {
    return vec3<T>{ -this->x, -this->y, -this->z };
   }

   template <typename C> requires (is_int_type<T> || is_floating_type<T>)
   constexpr explicit operator vec3<C>() {
    return vec3<C>{ static_cast<C>(this->x), static_cast<C>(this->y), static_cast<C>(this->z) };
   }

   constexpr explicit operator vec2<T>() {
    return vec2<T>{ this->x, this->y };
   }

   template <typename C> requires (is_int_type<T> || is_floating_type<T>)
   constexpr explicit operator vec2<C>() {
    return vec2<C>{ static_cast<C>(this->x), static_cast<C>(this->y) };
   }

   constexpr vec4<T> operator,(T w) {
    return vec4<T>{ this->x, this->y, this->z, w };
   }


    friend const lib::ostream& operator<<(const lib::ostream& out, const vec3<T>& vec) {
     out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
     return out;
    }

  };

  using vec3b = vec3<byte>;
  using vec3s = vec3<int16>;
  using vec3i = vec3<int32>;
  using vec3u = vec3<uint32>;
  using vec3l = vec3<int64>;
  using vec3f = vec3<float>;
  using vec3d = vec3<double>;

  template <typename T> requires (is_arithmetic_type<T>)
  struct vec4 {
  public:
   T x, y, z, w;

   constexpr vec4() : x(0), y(0), z(0), w(1) {}
   constexpr vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
   constexpr vec4(const vec4<T>& other) : x(other.x), y(other.y), z(other.z), w(other.w) {}
   constexpr vec4(vec4<T>&& other) noexcept : x(other.x), y(other.y), z(other.z), w(other.w) {
    other.x = 0;
    other.y = 0;
    other.z = 0;
    other.w = 1;
   }
   constexpr vec4(const vec2<T>& other, T z, T w) : x(other.x), y(other.y), z(z), w(w) {}
   constexpr vec4(vec3<T>& other, T w) : x(other.x), y(other.y), z(other.z), w(w) {}

   constexpr vec4<T>& operator=(const vec4<T>& other) = default;
   constexpr vec4<T>& operator=(vec4<T>&& other) noexcept {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    this->w = other.w;
    other.x = 0;
    other.y = 0;
    other.z = 0;
    other.w = 1;
    return *this;
   }

   constexpr ~vec4() = default;

   constexpr T distance() noexcept {
    return static_cast<T>(lib::fast_square_root(static_cast<float>(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w)));
   }

   constexpr T distance_squared() noexcept {
    return this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w;
   }

   constexpr vec4<T>& normalize() noexcept {
    T ratio = 1 / distance();
    this->x = this->x * ratio;
    this->y = this->y * ratio;
    this->z = this->z * ratio;
    return *this;
   }

   constexpr vec3<T> to_vec3() noexcept {
    T ratio = 1 / this->w;
    T x = this->x * ratio;
    T y = this->y * ratio;
    T z = this->z * ratio;
    return vec3<T>{ x, y, z };
   }

   constexpr vec4<T>& floor() noexcept {
    this->x = lib::floor(this->x);
    this->y = lib::floor(this->y);
    this->z = lib::floor(this->z);
    return *this;
   }

   constexpr vec4<T>& ceil() noexcept {
    this->x = lib::ceil(this->x);
    this->y = lib::ceil(this->y);
    this->z = lib::ceil(this->z);
    return *this;
   }

   constexpr vec4<T>& max(const vec4<T>& other) noexcept {
    this->x = lib::max(this->x, other.x);
    this->y = lib::max(this->y, other.y);
    this->z = lib::max(this->z, other.z);
    return *this;
   }

   constexpr vec4<T>& min(const vec3<T>& other) noexcept {
    this->x = lib::min(this->x, other.x);
    this->y = lib::min(this->y, other.y);
    this->z = lib::min(this->z, other.z);
    return *this;
   }

   constexpr T dot(const vec4<T>& other) noexcept {
    return this->x * other.x + this->y * other.y + this->z * other.z + this->w * other.w;
   }

   constexpr vec4<T> cross(const vec4<T>& other) noexcept {
    T x = this->y * other.z - this->z * other.y;
    T y = this->z * other.x - this->x * other.z;
    T z = this->x * other.y - this->y * other.x;
    return vec4<T>{ x, y, z };
   }

   constexpr vec4<T> copy() noexcept {
    return vec4<T>{ this->x, this->y, this->z, this->w };
   }

   constexpr vec2<T> xy() noexcept {
    return vec2<T>{ this->x, this->y };
   }

   constexpr vec2<T> xz() noexcept {
    return vec2<T>{ this->x, this->z };
   }

   constexpr vec2<T> yz() noexcept {
    return vec2<T>{ this->y, this->z };
   }

   constexpr vec3<T> xyz() noexcept {
    return vec3<T>{ this->x, this->y, this->z };
   }

   constexpr vec3<T> yzw() noexcept {
    return vec3<T>{ this->y, this->z, this->w };
   }

   constexpr vec3<T> xzw() noexcept {
    return vec3<T>{ this->x, this->z, this->w };
   }

   constexpr vec3<T> xyw() noexcept {
    return vec3<T>{ this->x, this->y, this->w };
   }

   constexpr vec4<T> operator+(const vec4<T>& other) noexcept {
    return vec4<T>{ this->x + other.x, this->y + other.y, this->z + other.z, this->w };
   }

   constexpr vec4<T> operator-(const vec4<T>& other) noexcept {
    return vec4<T>{ this->x - other.x, this->y - other.y, this->z - other.z, this->w };
   }

   constexpr vec4<T> operator*(const vec4<T>& other) noexcept {
    return vec4<T>{ this->x* other.x, this->y* other.y, this->z* other.z, this->w };
   }

   constexpr vec4<T> operator/(const vec4<T>& other) noexcept {
    return vec4<T>{ this->x / other.x, this->y / other.y, this - z / other.z, this->w };
   }

   constexpr void operator+=(const vec4<T>& other) noexcept {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
   }

   constexpr void operator-=(const vec4<T>& other) noexcept {
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
   }

   constexpr void operator*=(const vec4<T>& other) noexcept {
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;
   }

   constexpr void operator/=(const vec4<T>& other) noexcept {
    this->x /= other.x;
    this->y /= other.y;
    this->z /= other.z;
   }

   constexpr vec4<T> operator+(T number) noexcept {
    return vec4<T>{ this->x + number, this->y + number, this->z + number, this->w };
   }

   constexpr vec4<T> operator-(T number) noexcept {
    return vec4<T>{ this->x - number, this->y - number, this->z - number, this->w };
   }

   constexpr vec4<T> operator*(T number) noexcept {
    return vec4<T>{ this->x* number, this->y* number, this->z* number, this->w };
   }

   constexpr vec4<T> operator/(T number) noexcept {
    return vec4<T>{ this->x / number, this->y / number, this - z / number, this->w };
   }

   friend constexpr vec4<T> operator+(T number, const vec4<T>& vec) noexcept {
    return vec4<T>{ vec.x + number, vec.y + number, vec.z + number, vec.w };
   }

   friend constexpr vec4<T> operator-(T number, const vec4<T>& vec) noexcept {
    return vec4<T>{ vec.x - number, vec.y - number, vec.z* number, vec.w };
   }

   friend constexpr vec4<T> operator*(T number, const vec4<T>& vec) noexcept {
    return vec4<T>{ vec.x* number, vec.y* number, vec.z* number, vec.w };
   }

   friend constexpr vec4<T> operator/(T number, const vec4<T>& vec) noexcept {
    return vec4<T>{ vec.x / number, vec.y / number, vec.z / number, vec.w };
   }

   constexpr void operator+=(T number) noexcept {
    this->x += number;
    this->y += number;
    this->z += number;
   }

   constexpr void operator-=(T number) noexcept {
    this->x -= number;
    this->y -= number;
    this->z -= number;
   }

   constexpr void operator*=(T number) noexcept {
    this->x *= number;
    this->y *= number;
    this->z *= number;
   }

   constexpr void operator/=(T number) noexcept {
    this->x /= number;
    this->y /= number;
    this->z /= number;
   }

   constexpr bool operator==(const vec4<T>& other) noexcept {
    return this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w;
   }

   constexpr bool operator!=(const vec4<T>& other) noexcept {
    return this->x != other.x || this->y != other.y || this->z != other.z || this->w != other.w;
   }

   constexpr vec4<T> operator+() noexcept {
    return vec4<T>{ +this->x, +this->y, +this->z, this->w };
   }

   constexpr vec4<T> operator-() noexcept {
    return vec4<T>{ -this->x, -this->y, -this->z, this->w };
   }

   template <typename C> requires (is_int_type<T> || is_floating_type<T>)
   constexpr explicit operator vec4<C>() {
    return vec4<C>{ static_cast<C>(this->x), static_cast<C>(this->y), static_cast<C>(this->z), static_cast<C>(this->w) };
   }

   constexpr explicit operator vec3<T>() {
    return vec3<T>{ this->x, this->y, this->z };
   }

   template <typename C> requires (is_int_type<T> || is_floating_type<T>)
   constexpr explicit operator vec3<C>() {
    return vec4<C>{ static_cast<C>(this->x), static_cast<C>(this->y), static_cast<C>(this->z) };
   }

   constexpr explicit operator vec2<T>() {
    return vec2<T>{ this->x, this->y };
   }

   template <typename C> requires (is_int_type<T> || is_floating_type<T>)
   constexpr explicit operator vec2<C>() {
    return vec2<C>{ static_cast<C>(this->x), static_cast<C>(this->y) };
   }


    friend const lib::ostream& operator<<(const lib::ostream& out, const vec4<T>& vec) {
     out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
     return out;
    }

  };

  using vec4b = vec4<byte>;
  using vec4s = vec4<int16>;
  using vec4i = vec4<int32>;
  using vec4u = vec4<uint32>;
  using vec4l = vec4<int64>;
  using vec4f = vec4<float>;
  using vec4d = vec4<double>;
 }
# 5 "/home/sky/projects/Library/lib/mat.hpp" 2




 namespace lib {

  template <typename T> requires (is_arithmetic_type<T>)
  struct mat2 {
   T m00, m10;
   T m01, m11;

   constexpr mat2() noexcept {
    this->m00 = 0;
    this->m01 = 1;
    this->m10 = 1;
    this->m11 = 0;
   }
   constexpr mat2(T m00, T m01, T m10, T m11) noexcept {
    this->m00 = m00;
    this->m01 = m01;
    this->m10 = m10;
    this->m11 = m11;
   }
   constexpr mat2(mat2<T>& other) noexcept {
    this->m00 = other.m00;
    this->m01 = other.m01;
    this->m10 = other.m10;
    this->m11 = other.m11;
   }
   constexpr mat2(mat2<T>&& other) noexcept {
    this->m00 = other.m00;
    this->m01 = other.m01;
    this->m10 = other.m10;
    this->m11 = other.m11;
    other.m00 = 0;
    other.m01 = 0;
    other.m10 = 0;
    other.m11 = 0;
   }

   constexpr mat2<T>& operator=(const mat2<T>& other) noexcept = default;

   constexpr mat2<T>& operator=(mat2<T>&& other) noexcept {
    this->m00 = other.m00;
    this->m01 = other.m01;
    this->m10 = other.m10;
    this->m11 = other.m11;
    other.m00 = 0;
    other.m01 = 0;
    other.m10 = 0;
    other.m11 = 0;
    return *this;
   }

   constexpr ~mat2() noexcept = default;

   constexpr mat2<T> copy() const noexcept {
    return mat2<T>{
     this->m00, this->m01,
     this->m10, this->m11
    };
   }

   constexpr mat2<T> inverse() const noexcept {
    T oneOverDeterminant = static_cast<T>(1) / (+this->m00 * this->m11 - this->m10 * this->m01);

    mat2<T> inverse{
     +this->m11 * oneOverDeterminant,
     -this->m01 * oneOverDeterminant,
     -this->m10 * oneOverDeterminant,
     +this->m00 * oneOverDeterminant
    };

    return inverse;
   }

   constexpr mat2<T> operator+(T number) const noexcept {
    return mat2<T>{ this->m00 + number, this->m01 + number, this->m10 + number, this->m11 + number };
   }

   constexpr mat2<T> operator-(T number) const noexcept {
    return mat2<T>{ this->m00 - number, this->m01 - number, this->m10 - number, this->m11 - number };
   }

   constexpr mat2<T> operator*(T number) const noexcept {
    return mat2<T>{ this->m00 * number, this->m01 * number, this->m10 * number, this->m11 * number };
   }

   constexpr mat2<T> operator/(T number) const noexcept {
    return mat2<T>{ this->m00 / number, this->m01 / number, this->m10 / number, this->m11 / number };
   }

   friend constexpr mat2<T> operator+(T number, mat2<T>& mat) noexcept {
    return mat2<T>{ mat.m00 + number, mat.m01 + number, mat.m10 + number, mat.m11 + number };
   }

   friend constexpr mat2<T> operator-(T number, mat2<T>& mat) noexcept {
    return mat2<T>{ mat.m00 - number, mat.m01 - number, mat.m10 - number, mat.m11 - number };
   }

   friend constexpr mat2<T> operator*(T number, mat2<T>& mat) noexcept {
    return mat2<T>{ mat.m00 * number, mat.m01 * number, mat.m10 * number, mat.m11 * number };
   }

   friend constexpr mat2<T> operator/(T number, mat2<T>& mat) noexcept {
    return mat2<T>{ mat.m00 / number, mat.m01 / number, mat.m10 / number, mat.m11 / number };
   }

   constexpr void operator+=(T number) const noexcept {
    this->m00 += number;
    this->m01 += number;
    this->m10 += number;
    this->m11 += number;
   }

   constexpr void operator-=(T number) const noexcept {
    this->m00 -= number;
    this->m01 -= number;
    this->m10 -= number;
    this->m11 -= number;
   }

   constexpr void operator*=(T number) const noexcept {
    this->m00 *= number;
    this->m01 *= number;
    this->m10 *= number;
    this->m11 *= number;
   }

   constexpr void operator/=(T number) const noexcept {
    this->m00 /= number;
    this->m01 /= number;
    this->m10 /= number;
    this->m11 /= number;
   }

   constexpr vec2<T> operator*(vec2<T>& vec) const noexcept {
    return vec2<T>{ this->m00 * vec.x + this->m10 * vec.y, this->m01 * vec.x + this->m11 * vec.y };
   }

   friend constexpr vec2<T> operator*(vec2<T>& vec, mat2<T>& mat) noexcept {
    return vec2<T>{ mat.m00 * vec.x + mat.m10 * vec.y, mat.m01 * vec.x + mat.m11 * vec.y };
   }

   friend constexpr void operator*=(vec2<T>& vec, mat2<T>& mat) noexcept {
    T x = mat.m00 * vec.x + mat.m10 * vec.y;
    T y = mat.m01 * vec.x + mat.m11 * vec.y;
    vec.x = x;
    vec.y = y;
   }

   constexpr vec2<T> operator/(vec2<T>& vec) const noexcept {
    return this->inverse() * vec;
   }

   friend constexpr vec2<T> operator/(vec2<T>& vec, mat2<T>& mat) noexcept {
    return vec * mat.inverse();
   }

   friend constexpr void operator/=(vec2<T>& vec, mat2<T>& mat) noexcept {
    vec *= mat.inverse();
   }

   constexpr mat2<T> operator+(mat2<T>& mat) const noexcept {
    return mat2<T>{ this->m00 + mat.m00, this->m01 + mat.m01, this->m10 + mat.m10, this->m11 + mat.m11 };
   }

   constexpr mat2<T> operator-(mat2<T>& mat) const noexcept {
    return mat2<T>{ this->m00 - mat.m00, this->m01 - mat.m01, this->m10 - mat.m10, this->m11 - mat.m11 };
   }

   constexpr mat2<T> operator*(mat2<T>& mat) const noexcept {
    return mat2<T>{
     this->m00 * mat.m00 + this->m10 * mat.m01,
     this->m01 * mat.m00 + this->m11 * mat.m01,
     this->m00 * mat.m10 + this->m10 * mat.m11,
     this->m01 * mat.m10 + this->m11 * mat.m11
    };
   }

   constexpr mat2<T> operator/(mat2<T>& mat) const noexcept {
    mat2<T> mat_copy = copy();
    mat_copy /= mat;
    return mat_copy;
   }

   constexpr void operator+=(mat2<T>& mat) const noexcept {
    this->m00 += mat.m00;
    this->m01 += mat.m01;
    this->m10 += mat.m10;
    this->m11 += mat.m11;
   }

   constexpr void operator-=(mat2<T>& mat) const noexcept {
    this->m00 -= mat.m00;
    this->m01 -= mat.m01;
    this->m10 -= mat.m10;
    this->m11 -= mat.m11;
   }

   constexpr void operator*=(mat2<T>& mat) const noexcept {
    T x0 = this->m00 * mat.m00 + this->m10 * mat.m01;
    T y0 = this->m01 * mat.m00 + this->m11 * mat.m01;
    T x1 = this->m00 * mat.m10 + this->m10 * mat.m11;
    T y1 = this->m01 * mat.m10 + this->m11 * mat.m11;
    this->m00 = x0;
    this->m01 = y0;
    this->m10 = x1;
    this->m11 = y1;
   }

   constexpr void operator/=(mat2<T>& mat) const noexcept {
    *this *= inverse(mat);
   }

   constexpr bool operator==(mat2<T>& mat) const noexcept {
    return this->m00 == mat.m00 && this->m01 == mat.m01 && this->m10 == mat.m10 && this->m11 == mat.m11;
   }

   constexpr bool operator!=(mat2<T>& mat) const noexcept {
    return this->m00 != mat.m00 || this->m01 != mat.m01 || this->m10 != mat.m10 || this->m11 != mat.m11;
   }

   template <typename C> requires (is_arithmetic_type<C>)
   constexpr mat2<C> operator ()() const noexcept {
    return mat2<C> {
     static_cast<C>(this->m00),
     static_cast<C>(this->m01),
     static_cast<C>(this->m10),
     static_cast<C>(this->m11),
    };
   }


    friend const lib::ostream& operator<<(const lib::ostream& out, const mat2<T>& mat) {
     out << "[" << mat.m00 << ", " << mat.m10 << "]" << lib::endl;
     out << "[" << mat.m01 << ", " << mat.m11 << "]" << lib::endl;
     return out;
    }

  };

  using mat2b = mat2<byte>;
  using mat2s = mat2<int16>;
  using mat2i = mat2<int32>;
  using mat2u = mat2<uint32>;
  using mat2l = mat2<int64>;
  using mat2f = mat2<float>;
  using mat2d = mat2<double>;

  template <typename T> requires (is_arithmetic_type<T>)
  struct mat3 {
   T m00, m10, m20;
   T m01, m11, m21;
   T m02, m12, m22;

   constexpr mat3() noexcept {
    this->m00 = 0;
    this->m01 = 0;
    this->m02 = 1;

    this->m10 = 0;
    this->m11 = 1;
    this->m12 = 0;

    this->m20 = 1;
    this->m21 = 0;
    this->m22 = 0;
   }
   constexpr mat3(T m00, T m01, T m02, T m10, T m11, T m12, T m20, T m21, T m22) noexcept {
    this->m00 = m00;
    this->m01 = m01;
    this->m02 = m02;

    this->m10 = m10;
    this->m11 = m11;
    this->m12 = m12;

    this->m20 = m20;
    this->m21 = m21;
    this->m22 = m22;
   }
   constexpr mat3(mat3<T>& other) noexcept {
    this->m00 = other.m00;
    this->m01 = other.m01;
    this->m02 = other.m02;

    this->m10 = other.m10;
    this->m11 = other.m11;
    this->m12 = other.m12;

    this->m20 = other.m20;
    this->m21 = other.m21;
    this->m22 = other.m22;
   }
   constexpr mat3(mat3<T>&& other) noexcept {
    this->m00 = other.m00;
    this->m01 = other.m01;
    this->m02 = other.m02;

    this->m10 = other.m10;
    this->m11 = other.m11;
    this->m12 = other.m12;

    this->m20 = other.m20;
    this->m21 = other.m21;
    this->m22 = other.m22;

    other.m00 = 0;
    other.m01 = 0;
    other.m02 = 0;

    other.m10 = 0;
    other.m11 = 0;
    other.m12 = 0;

    other.m20 = 0;
    other.m21 = 0;
    other.m22 = 0;
   }

   constexpr mat3<T>& operator=(const mat3<T>& other) noexcept = default;

   constexpr mat3<T>& operator=(mat3<T>&& other) noexcept {
    this->m00 = other.m00;
    this->m01 = other.m01;
    this->m02 = other.m02;

    this->m10 = other.m10;
    this->m11 = other.m11;
    this->m12 = other.m12;

    this->m20 = other.m20;
    this->m21 = other.m21;
    this->m22 = other.m22;

    other.m00 = 0;
    other.m01 = 0;
    other.m02 = 0;

    other.m10 = 0;
    other.m11 = 0;
    other.m12 = 0;

    other.m20 = 0;
    other.m21 = 0;
    other.m22 = 0;
    return *this;
   }

   constexpr ~mat3() noexcept = default;

   constexpr mat3<T> copy() const noexcept {
    return mat3<T>{
     this->m00, this->m01, this->m02,
     this->m10, this->m11, this->m12,
     this->m20, this->m21, this->m22
    };
   }

   constexpr mat3<T> inverse() const noexcept {
    T oneOverDeterminant = static_cast<T>(1) / (
     + this->m00 * (this->m11 * this->m22 - this->m21 * this->m12)
     - this->m10 * (this->m01 * this->m22 - this->m21 * this->m02)
     + this->m20 * (this->m01 * this->m12 - this->m11 * this->m02)
    );

    mat3<T> inverse;
    inverse.m00 = +(this->m11 * this->m22 - this->m21 * this->m12) * oneOverDeterminant;
    inverse.m10 = -(this->m10 * this->m22 - this->m20 * this->m12) * oneOverDeterminant;
    inverse.m20 = +(this->m10 * this->m21 - this->m20 * this->m11) * oneOverDeterminant;
    inverse.m01 = -(this->m01 * this->m22 - this->m21 * this->m02) * oneOverDeterminant;
    inverse.m11 = +(this->m00 * this->m22 - this->m20 * this->m02) * oneOverDeterminant;
    inverse.m21 = -(this->m00 * this->m21 - this->m20 * this->m01) * oneOverDeterminant;
    inverse.m02 = +(this->m01 * this->m12 - this->m11 * this->m02) * oneOverDeterminant;
    inverse.m12 = -(this->m00 * this->m12 - this->m10 * this->m02) * oneOverDeterminant;
    inverse.m22 = +(this->m00 * this->m11 - this->m10 * this->m01) * oneOverDeterminant;

    return inverse;
   }

   constexpr mat3<T> operator+(T number) const noexcept {
    return mat3<T>{
     this->m00 + number,
     this->m01 + number,
     this->m02 + number,

     this->m10 + number,
     this->m11 + number,
     this->m12 + number,

     this->m20 + number,
     this->m21 + number,
     this->m22 + number
    };
   }

   constexpr mat3<T> operator-(T number) const noexcept {
    return mat3<T>{
     this->m00 - number,
     this->m01 - number,
     this->m02 - number,

     this->m10 - number,
     this->m11 - number,
     this->m12 - number,

     this->m20 - number,
     this->m21 - number,
     this->m22 - number
    };
   }

   constexpr mat3<T> operator*(T number) const noexcept {
    return mat3<T>{
     this->m00 * number,
     this->m01 * number,
     this->m02 * number,

     this->m10 * number,
     this->m11 * number,
     this->m12 * number,

     this->m20 * number,
     this->m21 * number,
     this->m22 * number
    };
   }

   constexpr mat3<T> operator/(T number) const noexcept {
    return mat3<T>{
     this->m00 / number,
     this->m01 / number,
     this->m02 / number,

     this->m10 / number,
     this->m11 / number,
     this->m12 / number,

     this->m20 / number,
     this->m21 / number,
     this->m22 / number
    };
   }

   friend constexpr mat3<T> operator+(T number, mat3<T>& mat) noexcept {
    return mat3<T>{
     mat.m00 + number,
     mat.m01 + number,
     mat.m02 + number,

     mat.m10 + number,
     mat.m11 + number,
     mat.m12 + number,

     mat.m20 + number,
     mat.m21 + number,
     mat.m22 + number
    };
   }

   friend constexpr mat3<T> operator-(T number, mat3<T>& mat) noexcept {
    return mat3<T>{
     mat.m00 - number,
     mat.m01 - number,
     mat.m02 - number,

     mat.m10 - number,
     mat.m11 - number,
     mat.m12 - number,

     mat.m20 - number,
     mat.m21 - number,
     mat.m22 - number
    };
   }

   friend constexpr mat3<T> operator*(T number, mat3<T>& mat) noexcept {
    return mat3<T>{
     mat.m00* number,
     mat.m01* number,
     mat.m02* number,

     mat.m10* number,
     mat.m11* number,
     mat.m12* number,

     mat.m20* number,
     mat.m21* number,
     mat.m22* number
    };
   }

   friend constexpr mat3<T> operator/(T number, mat3<T>& mat) noexcept {
    return mat3<T>{
     mat.m00 / number,
     mat.m01 / number,
     mat.m02 / number,

     mat.m10 / number,
     mat.m11 / number,
     mat.m12 / number,

     mat.m20 / number,
     mat.m21 / number,
     mat.m22 / number
    };
   }

   constexpr void operator+=(T number) const noexcept {
    this->m00 += number;
    this->m01 += number;
    this->m02 += number;

    this->m10 += number;
    this->m11 += number;
    this->m12 += number;

    this->m20 += number;
    this->m21 += number;
    this->m22 += number;
   }

   constexpr void operator-=(T number) const noexcept {
    this->m00 -= number;
    this->m01 -= number;
    this->m02 -= number;

    this->m10 -= number;
    this->m11 -= number;
    this->m12 -= number;

    this->m20 -= number;
    this->m21 -= number;
    this->m22 -= number;
   }

   constexpr void operator*=(T number) const noexcept {
    this->m00 *= number;
    this->m01 *= number;
    this->m02 *= number;

    this->m10 *= number;
    this->m11 *= number;
    this->m12 *= number;

    this->m20 *= number;
    this->m21 *= number;
    this->m22 *= number;
   }

   constexpr void operator/=(T number) const noexcept {
    this->m00 /= number;
    this->m01 /= number;
    this->m02 /= number;

    this->m10 /= number;
    this->m11 /= number;
    this->m12 /= number;

    this->m20 /= number;
    this->m21 /= number;
    this->m22 /= number;
   }

   constexpr vec3<T> operator*(vec3<T>& vec) const noexcept {
    return vec3<T>{
     this->m00 * vec.x + this->m10 * vec.y + this->m20 * vec.z,
     this->m01 * vec.x + this->m11 * vec.y + this->m21 * vec.z,
     this->m02 * vec.x + this->m12 * vec.y + this->m22 * vec.z
    };
   }

   friend constexpr vec3<T> operator*(vec3<T>& vec, mat3<T>& mat) noexcept {
    return vec3<T>{
     mat.m00 * vec.x + mat.m01 * vec.y + mat.m02 * vec.z,
     mat.m10 * vec.x + mat.m11 * vec.y + mat.m12 * vec.z,
     mat.m20 * vec.x + mat.m21 * vec.y + mat.m22 * vec.z
    };
   }

   friend constexpr void operator*=(vec3<T>& vec, mat3<T>& mat) noexcept {
    T x = mat.m00 * vec.x + mat.m01 * vec.y + mat.m02 * vec.z;
    T y = mat.m10 * vec.x + mat.m11 * vec.y + mat.m12 * vec.z;
    T z = mat.m20 * vec.x + mat.m21 * vec.y + mat.m22 * vec.z;
    vec.x = x;
    vec.y = y;
    vec.z = z;
   }

   constexpr vec3<T> operator/(vec3<T>& vec) const noexcept {
    return this->inverse() * vec;
   }

   friend constexpr vec3<T> operator/(vec3<T>& vec, mat3<T>& mat) noexcept {
    return vec * mat.inverse();
   }

   friend constexpr void operator/=(vec2<T>& vec, mat3<T>& mat) noexcept {
    vec *= mat.inverse();
   }

   constexpr mat3<T> operator+(mat3<T>& mat) const noexcept {
    return mat3<T>{
     this->m00 + mat.m00,
     this->m01 + mat.m01,
     this->m02 + mat.m02,

     this->m10 + mat.m10,
     this->m11 + mat.m11,
     this->m12 + mat.m12,

     this->m20 + mat.m20,
     this->m21 + mat.m21,
     this->m22 + mat.m22
    };
   }

   constexpr mat3<T> operator-(mat3<T>& mat) const noexcept {
    return mat3<T>{
     this->m00 + mat.m00,
     this->m01 + mat.m01,
     this->m02 + mat.m02,

     this->m10 + mat.m10,
     this->m11 + mat.m11,
     this->m12 + mat.m12,

     this->m20 + mat.m20,
     this->m21 + mat.m21,
     this->m22 + mat.m22
    };
   }

   constexpr mat3<T> operator*(const mat3<T>& mat) const noexcept {
    T const SrcA00 = this->m00;
    T const SrcA01 = this->m01;
    T const SrcA02 = this->m02;
    T const SrcA10 = this->m10;
    T const SrcA11 = this->m11;
    T const SrcA12 = this->m12;
    T const SrcA20 = this->m20;
    T const SrcA21 = this->m21;
    T const SrcA22 = this->m22;
    T const SrcB00 = mat.m00;
    T const SrcB01 = mat.m01;
    T const SrcB02 = mat.m02;
    T const SrcB10 = mat.m10;
    T const SrcB11 = mat.m11;
    T const SrcB12 = mat.m12;
    T const SrcB20 = mat.m20;
    T const SrcB21 = mat.m21;
    T const SrcB22 = mat.m22;

    mat3<T> Result;
    Result.m00 = SrcA00 * SrcB00 + SrcA10 * SrcB01 + SrcA20 * SrcB02;
    Result.m01 = SrcA01 * SrcB00 + SrcA11 * SrcB01 + SrcA21 * SrcB02;
    Result.m02 = SrcA02 * SrcB00 + SrcA12 * SrcB01 + SrcA22 * SrcB02;
    Result.m10 = SrcA00 * SrcB10 + SrcA10 * SrcB11 + SrcA20 * SrcB12;
    Result.m11 = SrcA01 * SrcB10 + SrcA11 * SrcB11 + SrcA21 * SrcB12;
    Result.m12 = SrcA02 * SrcB10 + SrcA12 * SrcB11 + SrcA22 * SrcB12;
    Result.m20 = SrcA00 * SrcB20 + SrcA10 * SrcB21 + SrcA20 * SrcB22;
    Result.m21 = SrcA01 * SrcB20 + SrcA11 * SrcB21 + SrcA21 * SrcB22;
    Result.m22 = SrcA02 * SrcB20 + SrcA12 * SrcB21 + SrcA22 * SrcB22;
    return Result;
   }

   constexpr mat3<T> operator/(mat3<T>& mat) const noexcept {
    mat3<T> mat_copy = copy();
    mat_copy /= mat;
    return mat_copy;
   }

   constexpr void operator+=(mat3<T>& mat) const noexcept {
    this->m00 += mat.m00;
    this->m01 += mat.m01;
    this->m02 += mat.m02;

    this->m10 += mat.m10;
    this->m11 += mat.m11;
    this->m12 += mat.m12;

    this->m20 += mat.m20;
    this->m21 += mat.m21;
    this->m22 += mat.m22;
   }

   constexpr void operator-=(mat3<T>& mat) const noexcept {
    this->m00 -= mat.m00;
    this->m01 -= mat.m01;
    this->m02 -= mat.m02;

    this->m10 -= mat.m10;
    this->m11 -= mat.m11;
    this->m12 -= mat.m12;

    this->m20 -= mat.m20;
    this->m21 -= mat.m21;
    this->m22 -= mat.m22;
   }

   constexpr void operator*=(mat3<T>& mat) const noexcept {
    *this = *this * mat;
   }

   constexpr void operator/=(mat3<T>& mat) const noexcept {
    *this *= inverse(mat);
   }

   constexpr bool operator==(mat3<T>& mat) const noexcept {
    return this->m00 == mat.m00 &&
     this->m01 == mat.m01 &&
     this->m02 == mat.m02 &&

     this->m10 == mat.m10 &&
     this->m11 == mat.m11 &&
     this->m12 == mat.m12 &&

     this->m20 == mat.m20 &&
     this->m21 == mat.m21 &&
     this->m22 == mat.m22;
   }

   constexpr bool operator!=(mat3<T>& mat) const noexcept {
    return this->m00 != mat.m00 ||
     this->m01 != mat.m01 ||
     this->m02 != mat.m02 ||

     this->m10 != mat.m10 ||
     this->m11 != mat.m11 ||
     this->m12 != mat.m12 ||

     this->m20 != mat.m20 ||
     this->m21 != mat.m21 ||
     this->m22 != mat.m22;
   }

   template <typename C> requires (is_arithmetic_type<C>)
   constexpr mat3<C> operator ()() const noexcept {
    return mat3<C>{
     static_cast<C>(this->m00), static_cast<C>(this->m01), static_cast<C>(this->m02),
     static_cast<C>(this->m10), static_cast<C>(this->m11), static_cast<C>(this->m12),
     static_cast<C>(this->m20), static_cast<C>(this->m21), static_cast<C>(this->m22)
    };
   }


    friend const lib::ostream& operator<<(const lib::ostream& out, const mat3<T>& mat) {
     out << "[" << mat.m00 << ", " << mat.m10 << ", " << mat.m20 << "]" << lib::endl;
     out << "[" << mat.m01 << ", " << mat.m11 << ", " << mat.m21 << "]" << lib::endl;
     out << "[" << mat.m02 << ", " << mat.m12 << ", " << mat.m22 << "]" << lib::endl;
     return out;
    }

  };

  using mat3b = mat3<byte>;
  using mat3s = mat3<int16>;
  using mat3i = mat3<int32>;
  using mat3u = mat3<uint32>;
  using mat3l = mat3<int64>;
  using mat3f = mat3<float>;
  using mat3d = mat3<double>;

  template <typename T> requires (is_arithmetic_type<T>)
  struct mat4 {
   T m00, m10, m20, m30;
   T m01, m11, m21, m31;
   T m02, m12, m22, m32;
   T m03, m13, m23, m33;

   constexpr mat4() noexcept {
    this->m00 = 0;
    this->m01 = 0;
    this->m02 = 0;
    this->m03 = 1;

    this->m10 = 0;
    this->m11 = 0;
    this->m12 = 1;
    this->m13 = 0;

    this->m20 = 0;
    this->m21 = 1;
    this->m22 = 0;
    this->m23 = 0;

    this->m30 = 1;
    this->m31 = 0;
    this->m32 = 0;
    this->m33 = 0;
   }
   constexpr mat4(
    T m00, T m01, T m02, T m03,
    T m10, T m11, T m12, T m13,
    T m20, T m21, T m22, T m23,
    T m30, T m31, T m32, T m33
   ) noexcept {
    this->m00 = m00;
    this->m01 = m01;
    this->m02 = m02;
    this->m03 = m03;

    this->m10 = m10;
    this->m11 = m11;
    this->m12 = m12;
    this->m13 = m13;

    this->m20 = m20;
    this->m21 = m21;
    this->m22 = m22;
    this->m23 = m23;

    this->m30 = m30;
    this->m31 = m31;
    this->m32 = m32;
    this->m33 = m33;
   }
   constexpr mat4(mat4<T>& other) noexcept {
    this->m00 = other.m00;
    this->m01 = other.m01;
    this->m02 = other.m02;
    this->m03 = other.m03;

    this->m10 = other.m10;
    this->m11 = other.m11;
    this->m12 = other.m12;
    this->m13 = other.m13;

    this->m20 = other.m20;
    this->m21 = other.m21;
    this->m22 = other.m22;
    this->m23 = other.m23;

    this->m30 = other.m30;
    this->m31 = other.m31;
    this->m32 = other.m32;
    this->m33 = other.m33;
   }
   constexpr mat4(mat4<T>&& other) noexcept {
    this->m00 = other.m00;
    this->m01 = other.m01;
    this->m02 = other.m02;
    this->m03 = other.m03;

    this->m10 = other.m10;
    this->m11 = other.m11;
    this->m12 = other.m12;
    this->m13 = other.m13;

    this->m20 = other.m20;
    this->m21 = other.m21;
    this->m22 = other.m22;
    this->m23 = other.m23;

    this->m30 = other.m30;
    this->m31 = other.m31;
    this->m32 = other.m32;
    this->m33 = other.m33;

    other.m00 = 0;
    other.m01 = 0;
    other.m02 = 0;
    other.m03 = 0;

    other.m10 = 0;
    other.m11 = 0;
    other.m12 = 0;
    other.m13 = 0;

    other.m20 = 0;
    other.m21 = 0;
    other.m22 = 0;
    other.m23 = 0;

    other.m30 = 0;
    other.m31 = 0;
    other.m32 = 0;
    other.m33 = 0;
   }

   constexpr mat4<T>& operator=(const mat4<T>& other) noexcept = default;

   constexpr mat4<T>& operator=(mat4<T>&& other) noexcept {
    this->m00 = other.m00;
    this->m01 = other.m01;
    this->m02 = other.m02;
    this->m03 = other.m03;

    this->m10 = other.m10;
    this->m11 = other.m11;
    this->m12 = other.m12;
    this->m13 = other.m13;

    this->m20 = other.m20;
    this->m21 = other.m21;
    this->m22 = other.m22;
    this->m23 = other.m23;

    this->m30 = other.m30;
    this->m31 = other.m31;
    this->m32 = other.m32;
    this->m33 = other.m33;

    other.m00 = 0;
    other.m01 = 0;
    other.m02 = 0;
    other.m03 = 0;

    other.m10 = 0;
    other.m11 = 0;
    other.m12 = 0;
    other.m13 = 0;

    other.m20 = 0;
    other.m21 = 0;
    other.m22 = 0;
    other.m23 = 0;

    other.m30 = 0;
    other.m31 = 0;
    other.m32 = 0;
    other.m33 = 0;
    return *this;
   }

   constexpr ~mat4() noexcept = default;

   constexpr mat4<T> copy() const noexcept {
    return mat4<T>{
     this->m00, this->m01, this->m02, this->m03,
     this->m10, this->m11, this->m12, this->m13,
     this->m20, this->m21, this->m22, this->m23,
     this->m30, this->m31, this->m32, this->m33
    };
   }

   constexpr mat4<T> inverse() const noexcept {
    T Coef00 = this->m22 * this->m33 - this->m32 * this->m23;
    T Coef02 = this->m12 * this->m33 - this->m32 * this->m13;
    T Coef03 = this->m12 * this->m23 - this->m22 * this->m13;

    T Coef04 = this->m21 * this->m33 - this->m31 * this->m23;
    T Coef06 = this->m11 * this->m33 - this->m31 * this->m13;
    T Coef07 = this->m11 * this->m23 - this->m21 * this->m13;

    T Coef08 = this->m21 * this->m32 - this->m31 * this->m22;
    T Coef10 = this->m11 * this->m32 - this->m31 * this->m12;
    T Coef11 = this->m11 * this->m22 - this->m21 * this->m12;

    T Coef12 = this->m20 * this->m33 - this->m30 * this->m23;
    T Coef14 = this->m10 * this->m33 - this->m30 * this->m13;
    T Coef15 = this->m10 * this->m23 - this->m20 * this->m13;

    T Coef16 = this->m20 * this->m32 - this->m30 * this->m22;
    T Coef18 = this->m10 * this->m32 - this->m30 * this->m12;
    T Coef19 = this->m10 * this->m22 - this->m20 * this->m12;

    T Coef20 = this->m20 * this->m31 - this->m30 * this->m21;
    T Coef22 = this->m10 * this->m31 - this->m30 * this->m11;
    T Coef23 = this->m10 * this->m21 - this->m20 * this->m11;

    vec4<T> Fac0(Coef00, Coef00, Coef02, Coef03);
    vec4<T> Fac1(Coef04, Coef04, Coef06, Coef07);
    vec4<T> Fac2(Coef08, Coef08, Coef10, Coef11);

    vec4<T> Fac3(Coef12, Coef12, Coef14, Coef15);
    vec4<T> Fac4(Coef16, Coef16, Coef18, Coef19);
    vec4<T> Fac5(Coef20, Coef20, Coef22, Coef23);

    vec4<T> Vec0(this->m10, this->m00, this->m00, this->m00);
    vec4<T> Vec1(this->m11, this->m01, this->m01, this->m01);
    vec4<T> Vec2(this->m12, this->m02, this->m02, this->m02);
    vec4<T> Vec3(this->m13, this->m03, this->m03, this->m03);

    vec4<T> Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
    vec4<T> Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
    vec4<T> Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
    vec4<T> Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);

    vec4<T> SignA(+1, -1, +1, -1);
    vec4<T> SignB(-1, +1, -1, +1);

    mat4<T> Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);

    vec4<T> Row0(Inverse.m00, Inverse.m10, Inverse.m20, Inverse.m30);

    vec4<T> Col0(this->m00, this->m01, this->m02, this->m03);
    vec4<T> Dot0(Col0 * Row0);

    T Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

    T OneOverDeterminant = static_cast<T>(1) / Dot1;

    return Inverse * OneOverDeterminant;
   }

   constexpr mat4<T> operator+(T number) const noexcept {
    return mat4<T>{
     this->m00 + number,
     this->m01 + number,
     this->m02 + number,
     this->m03 + number,

     this->m10 + number,
     this->m11 + number,
     this->m12 + number,
     this->m13 + number,

     this->m20 + number,
     this->m21 + number,
     this->m22 + number,
     this->m23 + number,

     this->m30 + number,
     this->m31 + number,
     this->m32 + number,
     this->m33 + number
    };
   }

   constexpr mat4<T> operator-(T number) const noexcept {
    return mat4<T>{
     this->m00 - number,
     this->m01 - number,
     this->m02 - number,
     this->m03 - number,

     this->m10 - number,
     this->m11 - number,
     this->m12 - number,
     this->m13 - number,

     this->m20 - number,
     this->m21 - number,
     this->m22 - number,
     this->m23 - number,

     this->m30 - number,
     this->m31 - number,
     this->m32 - number,
     this->m33 - number
    };
   }

   constexpr mat4<T> operator*(T number) const noexcept {
    return mat4<T>{
     this->m00 * number,
     this->m01 * number,
     this->m02 * number,
     this->m03 * number,

     this->m10 * number,
     this->m11 * number,
     this->m12 * number,
     this->m13 * number,

     this->m20 * number,
     this->m21 * number,
     this->m22 * number,
     this->m23 * number,

     this->m30 * number,
     this->m31 * number,
     this->m32 * number,
     this->m33 * number
    };
   }

   constexpr mat4<T> operator/(T number) const noexcept {
    return mat4<T>{
     this->m00 / number,
     this->m01 / number,
     this->m02 / number,
     this->m03 / number,

     this->m10 / number,
     this->m11 / number,
     this->m12 / number,
     this->m13 / number,

     this->m20 / number,
     this->m21 / number,
     this->m22 / number,
     this->m23 / number,

     this->m30 / number,
     this->m31 / number,
     this->m32 / number,
     this->m33 / number
    };
   }

   friend constexpr mat4<T> operator+(T number, mat4<T>& mat) noexcept {
    return mat4<T>{
     mat.m00 + number,
     mat.m01 + number,
     mat.m02 + number,
     mat.m03 + number,

     mat.m10 + number,
     mat.m11 + number,
     mat.m12 + number,
     mat.m13 + number,

     mat.m20 + number,
     mat.m21 + number,
     mat.m22 + number,
     mat.m23 + number,

     mat.m30 + number,
     mat.m31 + number,
     mat.m32 + number,
     mat.m33 + number
    };
   }

   friend constexpr mat4<T> operator-(T number, mat4<T>& mat) noexcept {
    return mat4<T>{
     mat.m00 - number,
     mat.m01 - number,
     mat.m02 - number,
     mat.m03 - number,

     mat.m10 - number,
     mat.m11 - number,
     mat.m12 - number,
     mat.m13 - number,

     mat.m20 - number,
     mat.m21 - number,
     mat.m22 - number,
     mat.m23 - number,

     mat.m30 - number,
     mat.m31 - number,
     mat.m32 - number,
     mat.m33 - number
    };
   }

   friend constexpr mat4<T> operator*(T number, mat4<T>& mat) noexcept {
    return mat4<T>{
     mat.m00 * number,
     mat.m01 * number,
     mat.m02 * number,
     mat.m03 * number,

     mat.m10 * number,
     mat.m11 * number,
     mat.m12 * number,
     mat.m13 * number,

     mat.m20 * number,
     mat.m21 * number,
     mat.m22 * number,
     mat.m23 * number,

     mat.m30 * number,
     mat.m31 * number,
     mat.m32 * number,
     mat.m33 * number
    };
   }

   friend constexpr mat4<T> operator/(T number, mat4<T>& mat) noexcept {
    return mat4<T>{
     mat.m00 / number,
     mat.m01 / number,
     mat.m02 / number,
     mat.m03 / number,

     mat.m10 / number,
     mat.m11 / number,
     mat.m12 / number,
     mat.m13 / number,

     mat.m20 / number,
     mat.m21 / number,
     mat.m22 / number,
     mat.m23 / number,

     mat.m30 / number,
     mat.m31 / number,
     mat.m32 / number,
     mat.m33 / number
    };
   }

   constexpr void operator+=(T number) const noexcept {
    this->m00 += number;
    this->m01 += number;
    this->m02 += number;
    this->m03 += number;

    this->m10 += number;
    this->m11 += number;
    this->m12 += number;
    this->m13 += number;

    this->m20 += number;
    this->m21 += number;
    this->m22 += number;
    this->m23 += number;

    this->m30 += number;
    this->m31 += number;
    this->m32 += number;
    this->m33 += number;
   }

   constexpr void operator-=(T number) const noexcept {
    this->m00 -= number;
    this->m01 -= number;
    this->m02 -= number;
    this->m03 -= number;

    this->m10 -= number;
    this->m11 -= number;
    this->m12 -= number;
    this->m13 -= number;

    this->m20 -= number;
    this->m21 -= number;
    this->m22 -= number;
    this->m23 -= number;

    this->m30 -= number;
    this->m31 -= number;
    this->m32 -= number;
    this->m33 -= number;
   }

   constexpr void operator*=(T number) const noexcept {
    this->m00 *= number;
    this->m01 *= number;
    this->m02 *= number;
    this->m03 *= number;

    this->m10 *= number;
    this->m11 *= number;
    this->m12 *= number;
    this->m13 *= number;

    this->m20 *= number;
    this->m21 *= number;
    this->m22 *= number;
    this->m23 *= number;

    this->m30 *= number;
    this->m31 *= number;
    this->m32 *= number;
    this->m33 *= number;
   }

   constexpr void operator/=(T number) const noexcept {
    this->m00 /= number;
    this->m01 /= number;
    this->m02 /= number;
    this->m03 /= number;

    this->m10 /= number;
    this->m11 /= number;
    this->m12 /= number;
    this->m13 /= number;

    this->m20 /= number;
    this->m21 /= number;
    this->m22 /= number;
    this->m23 /= number;

    this->m30 /= number;
    this->m31 /= number;
    this->m32 /= number;
    this->m33 /= number;
   }

   constexpr vec4<T> operator*(vec4<T>& vec) const noexcept {
    return vec4<T>{
     this->m00 * vec.x + this->m10 * vec.y + this->m20 * vec.z + this->m30 * vec.w,
     this->m01 * vec.x + this->m11 * vec.y + this->m21 * vec.z + this->m31 * vec.w,
     this->m02 * vec.x + this->m12 * vec.y + this->m22 * vec.z + this->m32 * vec.w,
     this->m03 * vec.x + this->m13 * vec.y + this->m23 * vec.z + this->m33 * vec.w
    };
   }

   friend constexpr vec4<T> operator*(vec4<T>& vec, mat4<T>& mat) noexcept {
    return vec4<T>{
     mat.m00 * vec.x + mat.m01 * vec.y + mat.m02 * vec.z + mat.m03 * vec.w,
     mat.m10 * vec.x + mat.m11 * vec.y + mat.m12 * vec.z + mat.m13 * vec.w,
     mat.m20 * vec.x + mat.m21 * vec.y + mat.m22 * vec.z + mat.m23 * vec.w,
     mat.m30 * vec.x + mat.m31 * vec.y + mat.m32 * vec.z + mat.m33 * vec.w
    };
   }

   friend constexpr void operator*=(vec4<T>& vec, mat4<T>& mat) noexcept {
    T x = mat.m00 * vec.x + mat.m01 * vec.y + mat.m02 * vec.z + mat.m03 * vec.w;
    T y = mat.m10 * vec.x + mat.m11 * vec.y + mat.m12 * vec.z + mat.m13 * vec.w;
    T z = mat.m20 * vec.x + mat.m21 * vec.y + mat.m22 * vec.z + mat.m23 * vec.w;
    T w = mat.m30 * vec.x + mat.m31 * vec.y + mat.m32 * vec.z + mat.m33 * vec.w;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    vec.w = w;
   }

   constexpr vec3<T> operator/(vec3<T>& vec) const noexcept {
    return this->inverse() * vec;
   }

   friend constexpr vec3<T> operator/(vec3<T>& vec, mat4<T>& mat) noexcept {
    return vec * mat.inverse();
   }

   friend constexpr void operator/=(vec2<T>& vec, mat4<T>& mat) noexcept {
    vec *= mat.inverse();
   }

   constexpr mat4<T> operator+(mat4<T>& mat) const noexcept {
    return mat4<T>{
     this->m00 + mat.m00,
     this->m01 + mat.m01,
     this->m02 + mat.m02,
     this->m03 + mat.m03,

     this->m10 + mat.m10,
     this->m11 + mat.m11,
     this->m12 + mat.m12,
     this->m13 + mat.m13,

     this->m20 + mat.m20,
     this->m21 + mat.m21,
     this->m22 + mat.m22,
     this->m23 + mat.m23,

     this->m30 + mat.m30,
     this->m31 + mat.m31,
     this->m32 + mat.m32,
     this->m33 + mat.m33
    };
   }

   constexpr mat4<T> operator-(mat4<T>& mat) const noexcept {
    return mat4<T>{
     this->m00 - mat.m00,
     this->m01 - mat.m01,
     this->m02 - mat.m02,
     this->m03 - mat.m03,

     this->m10 - mat.m10,
     this->m11 - mat.m11,
     this->m12 - mat.m12,
     this->m13 - mat.m13,

     this->m20 - mat.m20,
     this->m21 - mat.m21,
     this->m22 - mat.m22,
     this->m23 - mat.m23,

     this->m30 - mat.m30,
     this->m31 - mat.m31,
     this->m32 - mat.m32,
     this->m33 - mat.m33
    };
   }

   constexpr mat4<T> operator*(mat4<T>& mat) const noexcept {
    vec4<T> const SrcA0 = vec4<T>{ this->m00, this->m01, this->m02, this->m03 };
    vec4<T> const SrcA1 = vec4<T>{ this->m10, this->m11, this->m12, this->m13 };
    vec4<T> const SrcA2 = vec4<T>{ this->m20, this->m21, this->m22, this->m23 };
    vec4<T> const SrcA3 = vec4<T>{ this->m30, this->m31, this->m32, this->m33 };

    vec4<T> const SrcB0 = vec4<T>{ mat.m00, mat.m01, mat.m02, mat.m03 };
    vec4<T> const SrcB1 = vec4<T>{ mat.m10, mat.m11, mat.m12, mat.m13 };
    vec4<T> const SrcB2 = vec4<T>{ mat.m20, mat.m21, mat.m22, mat.m23 };
    vec4<T> const SrcB3 = vec4<T>{ mat.m30, mat.m31, mat.m32, mat.m33 };

    mat4<T> Result;
    Result[0] = SrcA0 * SrcB0[0] + SrcA1 * SrcB0[1] + SrcA2 * SrcB0[2] + SrcA3 * SrcB0[3];
    Result[1] = SrcA0 * SrcB1[0] + SrcA1 * SrcB1[1] + SrcA2 * SrcB1[2] + SrcA3 * SrcB1[3];
    Result[2] = SrcA0 * SrcB2[0] + SrcA1 * SrcB2[1] + SrcA2 * SrcB2[2] + SrcA3 * SrcB2[3];
    Result[3] = SrcA0 * SrcB3[0] + SrcA1 * SrcB3[1] + SrcA2 * SrcB3[2] + SrcA3 * SrcB3[3];
    return Result;
   }

   constexpr mat4<T> operator/(mat4<T>& mat) const noexcept {
    mat4<T> mat_copy = copy();
    mat_copy /= mat;
    return mat_copy;
   }

   constexpr void operator+=(mat4<T>& mat) const noexcept {
    this->m00 += mat.m00;
    this->m01 += mat.m01;
    this->m02 += mat.m02;
    this->m03 += mat.m03;

    this->m10 += mat.m10;
    this->m11 += mat.m11;
    this->m12 += mat.m12;
    this->m13 += mat.m13;

    this->m20 += mat.m20;
    this->m21 += mat.m21;
    this->m22 += mat.m22;
    this->m23 += mat.m23;

    this->m30 += mat.m30;
    this->m31 += mat.m31;
    this->m32 += mat.m32;
    this->m33 += mat.m33;
   }

   constexpr void operator-=(mat4<T>& mat) const noexcept {
    this->m00 -= mat.m00;
    this->m01 -= mat.m01;
    this->m02 -= mat.m02;
    this->m03 -= mat.m03;

    this->m10 -= mat.m10;
    this->m11 -= mat.m11;
    this->m12 -= mat.m12;
    this->m13 -= mat.m13;

    this->m20 -= mat.m20;
    this->m21 -= mat.m21;
    this->m22 -= mat.m22;
    this->m23 -= mat.m23;

    this->m30 -= mat.m30;
    this->m31 -= mat.m31;
    this->m32 -= mat.m32;
    this->m33 -= mat.m33;
   }

   constexpr void operator*=(mat4<T>& mat) const noexcept {
    *this = *this * mat;
   }

   constexpr void operator/=(mat4<T>& mat) const noexcept {
    *this *= inverse(mat);
   }

   constexpr bool operator==(mat4<T>& mat) const noexcept {
    return this->m00 == mat.m00 &&
     this->m01 == mat.m01 &&
     this->m02 == mat.m02 &&
     this->m03 == mat.m03 &&

     this->m10 == mat.m10 &&
     this->m11 == mat.m11 &&
     this->m12 == mat.m12 &&
     this->m13 == mat.m13 &&

     this->m20 == mat.m20 &&
     this->m21 == mat.m21 &&
     this->m22 == mat.m22 &&
     this->m23 == mat.m23 &&

     this->m30 == mat.m30 &&
     this->m31 == mat.m31 &&
     this->m32 == mat.m32 &&
     this->m33 == mat.m33;
   }

   constexpr bool operator!=(mat4<T>& mat) const noexcept {
    return this->m00 == mat.m00 ||
     this->m01 != mat.m01 ||
     this->m02 != mat.m02 ||
     this->m03 != mat.m03 ||

     this->m10 != mat.m10 ||
     this->m11 != mat.m11 ||
     this->m12 != mat.m12 ||
     this->m13 != mat.m13 ||

     this->m20 != mat.m20 ||
     this->m21 != mat.m21 ||
     this->m22 != mat.m22 ||
     this->m23 != mat.m23 ||

     this->m30 != mat.m30 ||
     this->m31 != mat.m31 ||
     this->m32 != mat.m32 ||
     this->m33 != mat.m33;
   }

   template <typename C> requires (is_arithmetic_type<C>)
   constexpr mat4<C> operator ()() const noexcept {
    return mat4<C> {
     static_cast<C>(this->m00), static_cast<C>(this->m01), static_cast<C>(this->m02), static_cast<C>(this->m03),
     static_cast<C>(this->m10), static_cast<C>(this->m11), static_cast<C>(this->m12), static_cast<C>(this->m13),
     static_cast<C>(this->m20), static_cast<C>(this->m21), static_cast<C>(this->m22), static_cast<C>(this->m23),
     static_cast<C>(this->m30), static_cast<C>(this->m31), static_cast<C>(this->m32), static_cast<C>(this->m33)
    };
   }


    friend const lib::ostream& operator<<(const lib::ostream& out, const mat4<T>& mat) {
     out << "[" << mat.m00 << ", " << mat.m10 << ", " << mat.m20 << ", " << mat.m30 << "]" << lib::endl;
     out << "[" << mat.m01 << ", " << mat.m11 << ", " << mat.m21 << ", " << mat.m31 << "]" << lib::endl;
     out << "[" << mat.m02 << ", " << mat.m12 << ", " << mat.m22 << ", " << mat.m32 << "]" << lib::endl;
     out << "[" << mat.m03 << ", " << mat.m13 << ", " << mat.m23 << ", " << mat.m33 << "]" << lib::endl;
     return out;
    }

  };

  using mat4b = mat4<byte>;
  using mat4s = mat4<int16>;
  using mat4i = mat4<int32>;
  using mat4u = mat4<uint32>;
  using mat4l = mat4<int64>;
  using mat4f = mat4<float>;
  using mat4d = mat4<double>;
 }
# 9 "/home/sky/projects/Library/main.cpp" 2
# 1 "/home/sky/projects/Library/lib/math.hpp" 1
# 10 "/home/sky/projects/Library/main.cpp" 2
# 1 "/home/sky/projects/Library/lib/memory.hpp" 1
# 11 "/home/sky/projects/Library/main.cpp" 2
# 1 "/home/sky/projects/Library/lib/string.hpp" 1
# 12 "/home/sky/projects/Library/main.cpp" 2
# 1 "/home/sky/projects/Library/lib/time.hpp" 1





 namespace lib {
  [[nodiscard]] constexpr inline int64 make_denominator(int64 numerator, int64 denominator) noexcept {
   if (numerator == 0 && denominator == 0) {
    return 1;
   }

   numerator = numerator >= 0 ? numerator : -numerator;
   denominator = denominator >= 0 ? denominator : -denominator;

   const int64 denom = denominator;

   while (denominator != 0) {
    const int64 temp = numerator;
    numerator = denominator;
    denominator = temp % denominator;
   }

   return denom / numerator;
  }

  [[nodiscard]] constexpr inline int64 make_numerator(int64 numerator, int64 denominator) noexcept {
   const int64 sign = (numerator >= 0 ? 1 : -1) * (denominator >= 0 ? 1 : -1);

   if (numerator == 0 && denominator == 0) {
    return sign;
   }

   numerator = numerator >= 0 ? numerator : -numerator;
   denominator = denominator >= 0 ? denominator : -denominator;

   const int64 denom = denominator;

   while (denominator != 0) {
    const int64 temp = numerator;
    numerator = denominator;
    denominator = temp % denominator;
   }

   return sign * (denom / numerator);
  }

  template <int64 x1, int64 x2>
  struct time_ratio {
   constexpr static int64 numerator = lib::make_numerator(x1, x2);
   constexpr static int64 denominator = lib::make_denominator(x1, x2);
  };

  template <typename ratio1, typename ratio2>
  using time_ratio_mul = time_ratio<ratio1::numerator * ratio2::numerator, ratio1::denominator * ratio2::denominator>;

  template <typename ratio1, typename ratio2>
  using time_ratio_div = time_ratio<ratio1::numerator / ratio2::numerator, ratio1::denominator / ratio2::denominator>;

  template <typename data_type, typename period>
  class time_value;

  template <typename cast_type, typename data_type, typename period>
  [[nodiscard]] constexpr cast_type time_cast(const time_value<data_type, period>& val) noexcept {
   using convert_ratio = lib::time_ratio_div<period, typename cast_type::period>;

   uint64 i = (val.count() * convert_ratio::numerator) / convert_ratio::denominator;

   return cast_type{ static_cast<typename cast_type::data_type>(i) };
  }

  template <typename data_type_, typename period_>
  class time_value {
  public:
   using this_type = time_value<data_type_, period_>;
   using data_type = data_type_;
   using period = period_;

  private:
   data_type data;

  public:
   constexpr time_value() noexcept = default;

   constexpr explicit time_value(const data_type& value) noexcept {
    this->data = value;
   }

   constexpr time_value(const this_type& other) noexcept {
    this->data = other.data;
   }

   template <typename other_data_type, typename other_period>
   constexpr time_value(const time_value<other_data_type, other_period>& other) {
    this->data = lib::time_cast<this_type>(other);
   }

   [[nodiscard]] constexpr data_type count() const noexcept {
    return data;
   }

   [[nodiscard]] constexpr this_type& operator+() const noexcept {
    this->data = +this->data;
    return *this;
   }

   [[nodiscard]] constexpr this_type& operator-() const noexcept {
    this->data = -this->data;
    return *this;
   }

   constexpr this_type& operator++() noexcept {
    ++data;
    return *this;
   }

   [[nodiscard]] constexpr this_type operator++(int) noexcept {
    return this_type(data++);
   }

   constexpr this_type& operator--() noexcept {
    --data;
    return *this;
   }

   [[nodiscard]] constexpr this_type operator--(int) noexcept {
    return this_type(data--);
   }

   constexpr this_type& operator+=(const this_type& other) noexcept {
    data = other.data;
    return *this;
   }

   constexpr this_type& operator-=(const this_type& other) noexcept {
    data -= other.data;
    return *this;
   }

   constexpr this_type& operator*=(const data_type& value) noexcept {
    data *= value;
    return *this;
   }

   constexpr this_type& operator/=(const data_type& value) noexcept {
    data /= value;
    return *this;
   }

   constexpr this_type& operator%=(const data_type& value) noexcept {
    data %= value;
    return *this;
   }
  };

  struct time_point {
   using nanoseconds = time_value<uint64, time_ratio<1, 1'000'000'000ULL>>;
   using microseconds = time_value<uint64, time_ratio<1, 1'000'000ULL>>;
   using milliseconds = time_value<uint64, time_ratio<1, 1'000>>;
   using seconds = time_value<uint64, time_ratio<1, 1>>;
   using minutes = time_value<uint32, time_ratio<60, 1>>;
   using hours = time_value<uint32, time_ratio<3600, 1>>;
   using days = time_value<uint32, time_ratio<24 * 3600, 1>>;
   using weeks = time_value<uint32, time_ratio<7 * 24 * 3600, 1>>;
   using months = time_value<uint32, time_ratio<146097ULL * 24 * 3600, 12 * 400>>;
   using years = time_value<uint32, time_ratio<146097ULL * 24 * 3600, 400>>;

  private:
   time_point() = default;
  };

  struct time_duration {
   using nanoseconds = time_value<int64, time_ratio<1, 1'000'000'000ULL>>;
   using microseconds = time_value<int64, time_ratio<1, 1'000'000ULL>>;
   using milliseconds = time_value<int64, time_ratio<1, 1'000>>;
   using seconds = time_value<int64, time_ratio<1, 1>>;
   using minutes = time_value<int32, time_ratio<60, 1>>;
   using hours = time_value<int32, time_ratio<3600, 1>>;
   using days = time_value<int32, time_ratio<24 * 3600, 1>>;
   using weeks = time_value<int32, time_ratio<7 * 24 * 3600, 1>>;
   using months = time_value<int32, time_ratio<146097ULL * 24 * 3600, 12 * 400>>;
   using years = time_value<int32, time_ratio<146097ULL * 24 * 3600, 400>>;

  private:
   time_duration() = default;
  };




  class system_clock {
  public:
   using data_type = uint64;
   using period = time_ratio<1, 10'000'000ULL>;
   using value = time_value<data_type, period>;

   [[nodiscard]] static value now() noexcept;
  };




  class high_res_clock {
  public:
   using data_type = uint64;
   using period = time_point::nanoseconds::period;
   using value = time_point::nanoseconds;

   [[nodiscard]] static value now() noexcept;
  };
 }
# 274 "/home/sky/projects/Library/lib/time.hpp"
# 1 "/usr/include/time.h" 1 3 4
# 29 "/usr/include/time.h" 3 4
# 1 "/usr/lib/gcc/x86_64-pc-linux-gnu/14.1.1/include/stddef.h" 1 3 4
# 30 "/usr/include/time.h" 2 3 4



# 1 "/usr/include/bits/time.h" 1 3 4
# 73 "/usr/include/bits/time.h" 3 4
# 1 "/usr/include/bits/timex.h" 1 3 4
# 22 "/usr/include/bits/timex.h" 3 4
# 1 "/usr/include/bits/types/struct_timeval.h" 1 3 4








# 8 "/usr/include/bits/types/struct_timeval.h" 3 4
struct timeval
{




  __time_t tv_sec;
  __suseconds_t tv_usec;

};
# 23 "/usr/include/bits/timex.h" 2 3 4



struct timex
{
# 58 "/usr/include/bits/timex.h" 3 4
  unsigned int modes;
  __syscall_slong_t offset;
  __syscall_slong_t freq;
  __syscall_slong_t maxerror;
  __syscall_slong_t esterror;
  int status;
  __syscall_slong_t constant;
  __syscall_slong_t precision;
  __syscall_slong_t tolerance;
  struct timeval time;
  __syscall_slong_t tick;
  __syscall_slong_t ppsfreq;
  __syscall_slong_t jitter;
  int shift;
  __syscall_slong_t stabil;
  __syscall_slong_t jitcnt;
  __syscall_slong_t calcnt;
  __syscall_slong_t errcnt;
  __syscall_slong_t stbcnt;

  int tai;


  int :32; int :32; int :32; int :32;
  int :32; int :32; int :32; int :32;
  int :32; int :32; int :32;

};
# 74 "/usr/include/bits/time.h" 2 3 4

extern "C" {


extern int clock_adjtime (__clockid_t __clock_id, struct timex *__utx) noexcept (true) __attribute__ ((__nonnull__ (2)));
# 90 "/usr/include/bits/time.h" 3 4
}
# 34 "/usr/include/time.h" 2 3 4



# 1 "/usr/include/bits/types/clock_t.h" 1 3 4






typedef __clock_t clock_t;
# 38 "/usr/include/time.h" 2 3 4
# 1 "/usr/include/bits/types/time_t.h" 1 3 4
# 10 "/usr/include/bits/types/time_t.h" 3 4
typedef __time_t time_t;
# 39 "/usr/include/time.h" 2 3 4
# 1 "/usr/include/bits/types/struct_tm.h" 1 3 4






struct tm
{
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;


  long int tm_gmtoff;
  const char *tm_zone;




};
# 40 "/usr/include/time.h" 2 3 4


# 1 "/usr/include/bits/types/struct_timespec.h" 1 3 4





# 1 "/usr/include/bits/endian.h" 1 3 4
# 35 "/usr/include/bits/endian.h" 3 4
# 1 "/usr/include/bits/endianness.h" 1 3 4
# 36 "/usr/include/bits/endian.h" 2 3 4
# 7 "/usr/include/bits/types/struct_timespec.h" 2 3 4




struct timespec
{



  __time_t tv_sec;




  __syscall_slong_t tv_nsec;
# 31 "/usr/include/bits/types/struct_timespec.h" 3 4
};
# 43 "/usr/include/time.h" 2 3 4



# 1 "/usr/include/bits/types/clockid_t.h" 1 3 4






typedef __clockid_t clockid_t;
# 47 "/usr/include/time.h" 2 3 4
# 1 "/usr/include/bits/types/timer_t.h" 1 3 4






typedef __timer_t timer_t;
# 48 "/usr/include/time.h" 2 3 4
# 1 "/usr/include/bits/types/struct_itimerspec.h" 1 3 4







struct itimerspec
  {
    struct timespec it_interval;
    struct timespec it_value;
  };
# 49 "/usr/include/time.h" 2 3 4
struct sigevent;
# 60 "/usr/include/time.h" 3 4
# 1 "/usr/include/bits/types/locale_t.h" 1 3 4
# 22 "/usr/include/bits/types/locale_t.h" 3 4
# 1 "/usr/include/bits/types/__locale_t.h" 1 3 4
# 27 "/usr/include/bits/types/__locale_t.h" 3 4
struct __locale_struct
{

  struct __locale_data *__locales[13];


  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;


  const char *__names[13];
};

typedef struct __locale_struct *__locale_t;
# 23 "/usr/include/bits/types/locale_t.h" 2 3 4

typedef __locale_t locale_t;
# 61 "/usr/include/time.h" 2 3 4







extern "C" {



extern clock_t clock (void) noexcept (true);



extern time_t time (time_t *__timer) noexcept (true);


extern double difftime (time_t __time1, time_t __time0)
     noexcept (true) __attribute__ ((__const__));


extern time_t mktime (struct tm *__tp) noexcept (true);
# 100 "/usr/include/time.h" 3 4
extern size_t strftime (char *__restrict __s, size_t __maxsize,
   const char *__restrict __format,
   const struct tm *__restrict __tp)
   noexcept (true) __attribute__ ((__nonnull__ (1, 3, 4)));




extern char *strptime (const char *__restrict __s,
         const char *__restrict __fmt, struct tm *__tp)
     noexcept (true);






extern size_t strftime_l (char *__restrict __s, size_t __maxsize,
     const char *__restrict __format,
     const struct tm *__restrict __tp,
     locale_t __loc) noexcept (true);



extern char *strptime_l (const char *__restrict __s,
    const char *__restrict __fmt, struct tm *__tp,
    locale_t __loc) noexcept (true);






extern struct tm *gmtime (const time_t *__timer) noexcept (true);



extern struct tm *localtime (const time_t *__timer) noexcept (true);
# 155 "/usr/include/time.h" 3 4
extern struct tm *gmtime_r (const time_t *__restrict __timer,
       struct tm *__restrict __tp) noexcept (true);



extern struct tm *localtime_r (const time_t *__restrict __timer,
          struct tm *__restrict __tp) noexcept (true);
# 180 "/usr/include/time.h" 3 4
extern char *asctime (const struct tm *__tp) noexcept (true);



extern char *ctime (const time_t *__timer) noexcept (true);
# 198 "/usr/include/time.h" 3 4
extern char *asctime_r (const struct tm *__restrict __tp,
   char *__restrict __buf) noexcept (true);



extern char *ctime_r (const time_t *__restrict __timer,
        char *__restrict __buf) noexcept (true);
# 218 "/usr/include/time.h" 3 4
extern char *__tzname[2];
extern int __daylight;
extern long int __timezone;




extern char *tzname[2];



extern void tzset (void) noexcept (true);



extern int daylight;
extern long int timezone;
# 247 "/usr/include/time.h" 3 4
extern time_t timegm (struct tm *__tp) noexcept (true);
# 264 "/usr/include/time.h" 3 4
extern time_t timelocal (struct tm *__tp) noexcept (true);







extern int dysize (int __year) noexcept (true) __attribute__ ((__const__));
# 282 "/usr/include/time.h" 3 4
extern int nanosleep (const struct timespec *__requested_time,
        struct timespec *__remaining);


extern int clock_getres (clockid_t __clock_id, struct timespec *__res) noexcept (true);


extern int clock_gettime (clockid_t __clock_id, struct timespec *__tp)
     noexcept (true) __attribute__ ((__nonnull__ (2)));


extern int clock_settime (clockid_t __clock_id, const struct timespec *__tp)
     noexcept (true) __attribute__ ((__nonnull__ (2)));
# 324 "/usr/include/time.h" 3 4
extern int clock_nanosleep (clockid_t __clock_id, int __flags,
       const struct timespec *__req,
       struct timespec *__rem);
# 339 "/usr/include/time.h" 3 4
extern int clock_getcpuclockid (pid_t __pid, clockid_t *__clock_id) noexcept (true);




extern int timer_create (clockid_t __clock_id,
    struct sigevent *__restrict __evp,
    timer_t *__restrict __timerid) noexcept (true);


extern int timer_delete (timer_t __timerid) noexcept (true);



extern int timer_settime (timer_t __timerid, int __flags,
     const struct itimerspec *__restrict __value,
     struct itimerspec *__restrict __ovalue) noexcept (true);


extern int timer_gettime (timer_t __timerid, struct itimerspec *__value)
     noexcept (true);
# 377 "/usr/include/time.h" 3 4
extern int timer_getoverrun (timer_t __timerid) noexcept (true);






extern int timespec_get (struct timespec *__ts, int __base)
     noexcept (true) __attribute__ ((__nonnull__ (1)));
# 400 "/usr/include/time.h" 3 4
extern int timespec_getres (struct timespec *__ts, int __base)
     noexcept (true);
# 426 "/usr/include/time.h" 3 4
extern int getdate_err;
# 435 "/usr/include/time.h" 3 4
extern struct tm *getdate (const char *__string);
# 449 "/usr/include/time.h" 3 4
extern int getdate_r (const char *__restrict __string,
        struct tm *__restrict __resbufp);


}
# 275 "/home/sky/projects/Library/lib/time.hpp" 2

  
# 276 "/home/sky/projects/Library/lib/time.hpp"
 namespace lib {
   namespace posix {
    [[nodiscard]] inline constexpr high_res_clock::value high_res_time_to_ns(const timespec time) noexcept {
     return high_res_clock::value{ static_cast<unsigned long>(time.tv_sec * 1'000'000'000 + time.tv_nsec) };
    }

    [[nodiscard]] inline constexpr system_clock::value sys_time_to_100ns(const timespec time) noexcept {
     return system_clock::value{ static_cast<unsigned long>(time.tv_sec * 1'000'000'000 + time.tv_nsec / 100) };
    }
   }

   [[nodiscard]] inline system_clock::value system_clock::now() noexcept {
    timespec out{};
    clock_gettime(
# 289 "/home/sky/projects/Library/lib/time.hpp" 3 4
                 2
# 289 "/home/sky/projects/Library/lib/time.hpp"
                                         , &out);
    return lib::posix::sys_time_to_100ns(out);
   }

   [[nodiscard]] inline high_res_clock::value high_res_clock::now() noexcept {
    timespec out{};
    clock_gettime(
# 295 "/home/sky/projects/Library/lib/time.hpp" 3 4
                 2
# 295 "/home/sky/projects/Library/lib/time.hpp"
                                         , &out);
    return lib::posix::high_res_time_to_ns(out);
   }
  }
# 13 "/home/sky/projects/Library/main.cpp" 2
# 1 "/home/sky/projects/Library/lib/types.hpp" 1
# 14 "/home/sky/projects/Library/main.cpp" 2
# 1 "/home/sky/projects/Library/lib/vec.hpp" 1
# 15 "/home/sky/projects/Library/main.cpp" 2
# 1 "/home/sky/projects/Library/lib/vector.hpp" 1






 namespace lib {
  template <typename T>
  class vector {
  public:
   using type = T;

   template <typename T_>
   struct vector_heap_data {
    static constexpr auto flag_bits = 1;
    static constexpr auto reserved_bits = 8 - flag_bits;

    ubyte from_stack : flag_bits;
    ubyte reserved : reserved_bits;
    T_* data;
    uint64 size;

    constexpr void init(uint64 size) noexcept {
     this->from_stack = false;
     this->data = new T_[size];
     this->size = size;
    }

    constexpr void destroy() const noexcept {
     if (data)
      delete[] reinterpret_cast<ubyte*>(data);
    }
   };

   template <typename T_>
   struct vector_stack_data {
    static constexpr auto flag_bits = 1;
    static constexpr auto size_bits = 8 - flag_bits;
    static constexpr auto buffer_size = (sizeof(vector_heap_data<T_>) - 1) / sizeof(T_);
    static constexpr auto max_size = 1ULL << size_bits;

    ubyte from_stack : flag_bits;
    ubyte size : size_bits;
    T_ data[buffer_size];

    constexpr void init(uint64 size) noexcept {
     this->from_stack = true;
     this->size = static_cast<ubyte>(size);
    }
   };

  private:
   union {
    vector_heap_data<T> heap_data;
    vector_stack_data<T> stack_data;
   };

  public:
   constexpr vector() noexcept {
    init(0);
   }

   constexpr explicit vector(const uint64 size) noexcept {
    init(size);
   }

   constexpr vector(const T* data, const T& null_data) noexcept {

    uint64 size = 0;
    while (data[size++] != null_data) {}

    init(size);


    size = 0;
    while (data[size++] != null_data) {
     this->data()[size] = data[size];
    }
   }

   constexpr vector(const T* data, const uint64 size) noexcept {
    init(size);

    for (uint64 i = 0; i < size; ++i) {
     this->data()[i] = data[i];
    }
   }

   constexpr ~vector() noexcept {
    if (!heap_data.from_stack) {
     heap_data.destroy();
    }
   }

   constexpr T& at(uint64 idx) noexcept {
    return data()[idx];
   }

   constexpr const T& at(uint64 idx) const noexcept {
    return data()[idx];
   }

   constexpr void set(uint64 idx, T& value) noexcept {
    data()[idx] = value;
   }

   constexpr void set(uint64 idx, T&& value) noexcept {
    data()[idx] = value;
   }

   constexpr void clear(T& clear_value) noexcept {
    for (uint64 i = 0; i < size(); ++i) {
     set(i, clear_value);
    }
   }


   constexpr bool set_size(uint64 new_size) noexcept {
    if (new_size <= vector_stack_data<T>::buffer_size) {
     stack_data.size = new_size;
     stack_data.from_stack = true;
     return true;
    }

    const uint64 old_size = size();
    T* old_data = new T[old_size];
    for (uint64 i = 0; i < old_size; ++i) {
     old_data[i] = data()[i];
    }

    if (!from_stack()) {
     heap_data.destroy();
    }

    init(new_size);

    for (uint64 i = 0; i < old_size; ++i) {
     data()[i] = old_data[i];
    }

    delete[] old_data;

    if (old_size < new_size) {
     for (uint64 i = old_size; i < new_size; ++i) {
      data()[i] = T{ 0 };
     }
    }

    return false;
   }

   constexpr void push_back(T& value) noexcept {
    const int64 old_size = size();
    set_size(old_size + 1);
    set(old_size, value);
   }

   constexpr void push_back(T&& value) noexcept {
    const int64 old_size = size();
    set_size(old_size + 1);
    set(old_size, value);
   }

   constexpr void pop_back() noexcept {
    set_size(size() - 1);
   }

   constexpr T* data() noexcept {
    return heap_data.from_stack ? stack_data.data : heap_data.data;
   }

   constexpr const T* data() const noexcept {
    return heap_data.from_stack ? stack_data.data : heap_data.data;
   }

   [[nodiscard]] constexpr uint64 size() const noexcept {
    return heap_data.from_stack ? stack_data.size : heap_data.size;
   }

   [[nodiscard]] constexpr bool from_stack() const noexcept {
    return heap_data.from_stack;
   }

   constexpr T* begin() noexcept {
    return data();
   }

   constexpr T* end() noexcept {
    return &data()[size()];
   }

   constexpr T* front() noexcept {
    return data();
   }

   constexpr T* back() noexcept {
    return &data()[size()];
   }

   constexpr const T* begin() const noexcept {
    return data();
   }

   constexpr const T* end() const noexcept {
    return &data()[size()];
   }

   constexpr const T* front() const noexcept {
    return data();
   }

   constexpr const T* back() const noexcept {
    return &data()[size()];
   }

   constexpr T& operator[](uint64 index) noexcept {
    return at(index);
   }

   constexpr const T& operator[](uint64 index) const noexcept {
    return at(index);
   }


    template <typename T_>
    friend const lib::ostream& operator<<(const lib::ostream& out, const lib::vector<T_>& vec) {
     out << "{ ";
     for (uint64 i = 0; i < vec.size(); ++i) {
      if (i != 0) {
       out << ", ";
      }
      out << vec[i];
     }
     out << " }";
     return out;
    }


  private:
   constexpr void init(uint64 size) noexcept {
    if (size <= vector_stack_data<T>::buffer_size) {
     stack_data.init(size);
    } else {
     heap_data.init(size);
    }
   }
  };
 }
# 16 "/home/sky/projects/Library/main.cpp" 2



int main() {
    constexpr lib::mat2i test{};
    auto temp = test.inverse();

    constexpr lib::string str = "readonly";
    const lib::uint64 str_pos = str.find("only");
    lib::uint64 ch_pos = str.find('o');

    lib::cout << "hi";
    lib::cout << str_pos << ", " << ch_pos << lib::endl;

    return (temp.m00 = 0);
}
