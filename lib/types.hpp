//
// Created by sky on 06.06.24.
//

//
// Contains Definitions for:
//
// 0.1: byte, ubyte, int16, uint16
// 0.1: int32, uin32, int64, uint64
// 1.0: conditional_type<enable, t1, t2>
// 1.0: type_from_size<size, unsigned>
// 1.0: intptr, uintptr
// 1.0: min / max size of every predefined type
// 1.0: type_traits<type>
// 1.0: is_same_type<type, type>
// 1.0: is_any_of_type<type, types...>
// 1.0: is_int_type<type>
// 1.0: is_floating_type<type>
// 1.0: is_arithmetic_type<type>
// 1.0: is_void_type<type>
// 1.0: is_bool_type<type>
// 1.0: is_char_type<type>
// 1.0: is_integral_type<type>
// 1.0: make_unsigned_with_size<size>
// 1.0: make_unsigned<type>
// 1.0: make_signed_with_size<size>
// 1.0: make_signed<type>
// 1.0: remove_reference<type>
// 1.0: remove_const<type>
// 1.0: remove_volatile<type>
// 1.0: remove_const_volatile<type>
// 1.0: is_signed<type>
// 1.0: is_unsigned<type>
// 1.0: is_const<type>
// 1.0: is_object<type>
// 1.0: cycle_value<type>
// 1.0: constant<type, value>
// 1.0: true_type
// 1.0: false_type
// 1.0: is_lvalue_reference<type>
// 1.0: is_rvalue_reference<type>
// 1.0: forward<type>(type&)
// 1.0: enable_if_type<enable, type>
// 1.0: optional<type>
// 1.1: uint128
//
#ifndef TYPES_HPP
    #define TYPES_HPP

    namespace lib {
        #ifdef _MSC_VER // msvc or clang vvv
            using byte   = __int8;
            using ubyte  = unsigned __int8;
            using int16  = __int16;
            using uint16 = unsigned __int16;
            using int32  = __int32;
            using uint32 = unsigned __int32;
            using int64  = __int64;
            using uint64 = unsigned __int64;
        #else // msvc or clang ^^^ gcc vvv
            #ifdef __INT8_TYPE__
                using byte = __INT8_TYPE__;
            #else
                using byte = signed char;
            #endif

            #ifdef __UINT8_TYPE__
                using ubyte = __UINT8_TYPE__;
            #else
                using ubyte = unsigned char;
            #endif

            #ifdef __INT16_TYPE__
                using int16 = __INT16_TYPE__;
            #else
                using int16 = signed short int;
            #endif

            #ifdef __UINT16_TYPE__
                using uint16 = __UINT16_TYPE__;
            #else
                using uint16 = unsigned short int;
            #endif

            #ifdef __INT32_TYPE__
                using int32 = __INT32_TYPE__;
            #else
                using int32 = signed long int;
            #endif

            #ifdef __UINT32_TYPE__
                using uint32 = __UINT32_TYPE__;
            #else
                using uint32 = unsigned long int;
            #endif

            #ifdef __INT64_TYPE__
                using int64 = __INT64_TYPE__;
            #else
                using int64 = signed long long int;
            #endif

            #ifdef __UINT64_TYPE__
                using uint64 = __UINT64_TYPE__;
            #else
                using uint64 = unsigned long long int;
            #endif
        #endif // _MSC_VER gcc ^^^

		union alignas(16) uint128 {
			struct {} empty;
			ubyte as_bytes[16];
			uint16 as_uint16[8];
			uint32 as_uint32[4];
			uint64 as_uint64[2];

			constexpr uint128() noexcept : empty() {}
			constexpr /*no explicit*/ uint128(const uint64 v1, const uint64 v2 = 0) noexcept : as_uint64{ v1, v2 } {}
			constexpr uint128(const uint32 v1, const uint32 v2, const uint32 v3, const uint32 v4) noexcept : as_uint32{ v1, v2, v3, v4 } {}

			constexpr /*no explicit*/ operator bool() const noexcept { return as_uint64[0] != 0 || as_uint64[1] != 0; }
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
				return as_uint64[0] ^ as_uint64[1]; // easy hash function
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

        using intptr  = type_from_size<sizeof(void*), false>;
        using uintptr = type_from_size<sizeof(void*), true>;

        constexpr byte   min_byte   = static_cast<byte>  (0x80);				// -128
		constexpr byte   max_byte   = static_cast<byte>  (0x7F);				//  127
		constexpr ubyte  min_ubyte  = static_cast<ubyte> (0x00);				//  0
		constexpr ubyte  max_ubyte  = static_cast<ubyte> (0xFF);				//  255
		constexpr int16  min_int16  = static_cast<int16> (0x8000);				// -32 Thousand
		constexpr int16  max_int16  = static_cast<int16> (0x7FFF);				//  32 Thousand
		constexpr uint16 min_uint16 = static_cast<uint16>(0x0000);				//  0
		constexpr uint16 max_uint16 = static_cast<uint16>(0xFFFF);				//  65 Thousand
		constexpr int32  min_int32  = static_cast<int32> (0x80000000);			// -2 Billion
		constexpr int32  max_int32  = static_cast<int32> (0x7FFFFFFF);			//  2 Billion
		constexpr uint32 min_uint32 = static_cast<uint32>(0x00000000);			//  0
		constexpr uint32 max_uint32 = static_cast<uint32>(0xFFFFFFFF);			//  4 Billion
		constexpr int64  min_int64  = static_cast<int64> (0x8000000000000000);	// -9 Quintillion
		constexpr int64  max_int64  = static_cast<int64> (0x7FFFFFFFFFFFFFFF);	//  9 Quintillion
		constexpr uint64 min_uint64 = static_cast<uint64>(0x0000000000000000);	//  0
		constexpr uint64 max_uint64 = static_cast<uint64>(0xFFFFFFFFFFFFFFFF);	//  18 Quintillion

		constexpr float  min_pos_float  = static_cast<float> (1.175494351e-38F);
		constexpr float  max_float      = static_cast<float> (3.402823466e+38F);
		constexpr float  min_float		= static_cast<float> (-3.402823466e+38F);

		constexpr double min_pos_double = static_cast<double>(2.2250738585072014e-308);
		constexpr double max_double     = static_cast<double>(1.7976931348623158e+308);
		constexpr double min_double		= static_cast<double>(-1.7976931348623158e+308);

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

		// template <typename>
		// constexpr inline bool is_pointer = false;
		//
		// template <typename T>
		// constexpr inline bool is_pointer<lib::remove_const_volatile<T>*> = true;

		template <typename T>
		constexpr inline bool is_const = false;

		template <typename T>
		constexpr inline bool is_const<const T> = true;

		template <typename T>
		constexpr inline bool is_object = lib::is_const<const T> && !lib::is_void_type<T>;

		/*template <typename T>
		struct remove_pointer_struct {
			using type = T;
		};

		template <typename T>
		struct remove_pointer_struct<lib::remove_const_volatile<T>*> {
			using type = T;
		};

    	template <typename T>
    	using remove_pointer = typename remove_pointer_struct<T>::type;*/

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

				// make max & min values for this type
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

    } // namespace lib

#endif // TYPES_HPP