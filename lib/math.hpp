//###############################################
//# TODO Constants:                             #
//###############################################
//# 1.  PI                                      # finished
//# 2.  E                                       # finished
//# 3.  C_LIGHT                                 # finished
//###############################################
//# TODO Functions:                             #
//###############################################
//# 1.  min                                     # finished
//# 2.  max                                     # finished
//# 3.  union_cast                              # finished
//# 4.  square_root                             #
//# 5.  cubic_root                              #
//# 5.  fast_inverse_square_root                # finished
//# 6.  fast_square_root                        # finished
//# 7.  floor                                   # finished
//# 8.  floori                                  # finished
//# 9.  ceil                                    # finished
//# 10. ceili                                   # finished
//# 11. abs                                     # finished
//# 12. is_subnormal                            # finished
//# 13. is_nan                                  # finished
//# 14. is_inf                                  # finished
//# 15. pow                                     #
//# 16. powi                                    # finished
//# 17. sin                                     #
//# 18. cos                                     #
//# 19. tan                                     #
//# 20. asin                                    #
//# 21. acos                                    #
//# 22. atan                                    #
//# 23. log                                     #
//# 24. log2                                    #
//# 25. lg                                      #
//# 26. ln                                      #
//# 27. deg                                     # finished
//# 28. rad                                     #
//###############################################

#ifndef MATH_HPP
	#define MATH_HPP

    #include "types.hpp"

	namespace lib {
        // constants
        static constexpr auto PI = 3.1415926535897932384626433832795028841971;
        static constexpr auto E  = 2.7182818284590452353602874713526624977572;
        static constexpr auto C_LIGHT = 299'792'458; // m/s (vacuum)
        // calculation constants
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

            // Efficient Iterative Approximation Improvement in horner polynomial form.
            v.f = v.f * (2 - w);     // Single iteration, Err = -3.36e-3 * 2^(-flr(log2(x)))
            //v.f = v.f * (4 + w * (-6 + w * (4 - w)));  // Second iteration, Err = -1.13e-5 * 2^(-flr(log2(x)))
            //v.f = v.f * (8 + w * (-28 + w * (56 + w * (-70 + w *(56 + w * (-28 + w * (8 - w)))))));  // Third Iteration, Err = +-6.8e-8 *  2^(-flr(log2(x)))

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
                float  f;
                uint32 i;
            } val { .f = number };

            uint32 exponent = (val.i >> 23) & 0xff; // extract the exponent field
            uint32 fractional_bits = 150 - exponent;

            if (fractional_bits > 23) // abs(x) < 1.0
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
            #ifdef __has_builtin
                #if __has_builtin(__builtin_isinf_sign)
                    #define BUILTINT_ISINF
                    return __builtin_isinf_sign(value);
                #endif
            #endif
            #ifndef BUILTINT_ISINF
                union { uint64 u; double f; } ieee754;
                ieee754.f = static_cast<double>(value);
                return ((uint32)(ieee754.u >> 32) & 0x7fffffff) == 0x7ff00000 &&
                    ((uint32)ieee754.u == 0);
            #endif
            #undef BUILTIN_ISINF
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

#endif