#ifndef TIME_HPP
	#define TIME_HPP

	#include "types.hpp"

	namespace lib {
		[[nodiscard]] constexpr int64 make_denominator(int64 numerator, int64 denominator) noexcept {
			if (numerator == 0 && denominator == 0) {
				return 1;
			}

			numerator = numerator >= 0 ? numerator : -numerator;
			denominator = denominator >= 0 ? denominator : -denominator;

			const int64 denom = denominator; // temp variable

			while (denominator != 0) {
				const int64 temp = numerator;
				numerator = denominator;
				denominator = temp % denominator;
			}

			return denom / numerator;
		}

		[[nodiscard]] constexpr int64 make_numerator(int64 numerator, int64 denominator) noexcept {
			const int64 sign = (numerator >= 0 ? 1 : -1) * (denominator >= 0 ? 1 : -1);

			if (numerator == 0 && denominator == 0) {
				return sign;
			}

			numerator = numerator >= 0 ? numerator : -numerator;
			denominator = denominator >= 0 ? denominator : -denominator;

			const int64 denom = denominator; // temp variable

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
			using type = time_value;
			using data_type = data_type_;
			using period = period_;

		private:
			data_type data;

		public:
			constexpr time_value() noexcept = default;

			constexpr explicit time_value(const data_type& value) noexcept {
				this->data = value;
			}

			constexpr time_value(const type& other) noexcept {
				this->data = other.data;
			}

			template <typename other_data_type, typename other_period>
			constexpr time_value(const time_value<other_data_type, other_period>& other) {
				this->data = lib::time_cast<type>(other);
			}

			[[nodiscard]] constexpr data_type count() const noexcept {
				return data;
			}

			[[nodiscard]] constexpr type& operator+() const noexcept {
				this->data = +this->data;
				return *this;
			}

			[[nodiscard]] constexpr type& operator-() const noexcept {
				this->data = -this->data;
				return *this;
			}

			constexpr type& operator++() noexcept {
				++data;
				return *this;
			}

			[[nodiscard]] constexpr type operator++(int) noexcept {
				return this_type(data++);
			}

			constexpr type& operator--() noexcept {
				--data;
				return *this;
			}

			[[nodiscard]] constexpr type operator--(int) noexcept {
				return this_type(data--);
			}

			constexpr type& operator+=(const type& other) noexcept {
				data = other.data;
				return *this;
			}

			constexpr type& operator-=(const type& other) noexcept {
				data -= other.data;
				return *this;
			}

			constexpr type& operator*=(const data_type& value) noexcept {
				data *= value;
				return *this;
			}

			constexpr type& operator/=(const data_type& value) noexcept {
				data /= value;
				return *this;
			}

			constexpr type& operator%=(const data_type& value) noexcept {
				data %= value;
				return *this;
			}
		};

		// time_point time_values are unsigned
		namespace time_point {
			using nanoseconds	= time_value<uint64, time_ratio<1, 1'000'000'000ULL>>;
			using microseconds	= time_value<uint64, time_ratio<1, 1'000'000ULL>>;
			using milliseconds	= time_value<uint64, time_ratio<1, 1'000>>;
			using seconds		= time_value<uint64, time_ratio<1, 1>>;
			using minutes		= time_value<uint32, time_ratio<60, 1>>;
			using hours			= time_value<uint32, time_ratio<3600, 1>>;
			using days			= time_value<uint32, time_ratio<24 * 3600, 1>>;
			using weeks			= time_value<uint32, time_ratio<7 * 24 * 3600, 1>>;
			using months		= time_value<uint32, time_ratio<146097ULL * 24 * 3600, 12 * 400>>;
			using years			= time_value<uint32, time_ratio<146097ULL * 24 * 3600, 400>>;
		};

		// time_duration time_values are signed
		namespace time_duration {
			using nanoseconds	= time_value<int64, time_ratio<1, 1'000'000'000ULL>>;
			using microseconds	= time_value<int64, time_ratio<1, 1'000'000ULL>>;
			using milliseconds	= time_value<int64, time_ratio<1, 1'000>>;
			using seconds		= time_value<int64, time_ratio<1, 1>>;
			using minutes		= time_value<int32, time_ratio<60, 1>>;
			using hours			= time_value<int32, time_ratio<3600, 1>>;
			using days			= time_value<int32, time_ratio<24 * 3600, 1>>;
			using weeks			= time_value<int32, time_ratio<7 * 24 * 3600, 1>>;
			using months		= time_value<int32, time_ratio<146097ULL * 24 * 3600, 12 * 400>>;
			using years			= time_value<int32, time_ratio<146097ULL * 24 * 3600, 400>>;
		};

		// 100ns precision (win32: <1us)
		// win32: GetSystemTimePreciseAsFileTime/GetSystemTimeAsFileTime
		// posix: CLOCK_PROCESS_CPUTIME_ID
		class system_clock {
		public:
			using data_type = uint64;
			using period = time_ratio<1, 10'000'000ULL>;
			using value = time_value<data_type, period>;

			[[nodiscard]] static value now() noexcept;
		};

		// 1ns precision
		// win32: QueryPerformanceCounter
		// posix: CLOCK_PROCESS_CPUTIME_ID
		class high_res_clock {
		public:
			using data_type = uint64;
			using period = time_point::nanoseconds::period;
			using value = time_point::nanoseconds;

			[[nodiscard]] static value now() noexcept;
		};
	}

	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)

		#include <windows.h>

		#if defined(_M_ARM) || defined(_M_ARM64)
			#define LIKELY_ARM [[likely]]
			#define LIKELY_X86
		#elif defined(_M_IX86) || defined(_M_X64)
			#define LIKELY_ARM
			#define LIKELY_X86 [[likely]]
		#else
			#define LIKELY_ARM
			#define LIKELY_X86
		#endif

		namespace lib {
			namespace windows {
				inline LARGE_INTEGER frequency{ .QuadPart = 0 };
			}

			[[nodiscard]] system_clock::value system_clock::now() noexcept {
				FILETIME time{};
				GetSystemTimePreciseAsFileTime(&time);
				ULARGE_INTEGER out{};
				out.HighPart = time.dwHighDateTime;
				out.LowPart = time.dwLowDateTime;
				return system_clock::value{ out.QuadPart };
			}

			[[nodiscard]] high_res_clock::value high_res_clock::now() noexcept {
				if (windows::frequency.QuadPart == 0) [[unlikely]]
					QueryPerformanceFrequency(&windows::frequency);

				LARGE_INTEGER tmp{};
				QueryPerformanceCounter(&tmp);

				const int64 freq = windows::frequency.QuadPart;
				const int64 cntr = tmp.QuadPart;

				constexpr int64 MHz10 = 10'000'000;
				constexpr int64 MHz24 = 24'000'000;

				if (freq == MHz10) LIKELY_X86 {
					constexpr int64 multiplier = high_res_clock::period::denominator;
					return high_res_clock::value{ cntr * multiplier };
				} else if (freq == MHz24) LIKELY_ARM {
					const int64 whole = (cntr / MHz24) * high_res_clock::period::denominator;
					const int64 part_ = (cntr % MHz24) * high_res_clock::period::denominator / MHz24;
					return high_res_clock::value{ whole + part_ };
				} else {
					const int64 whole = (cntr / freq) * high_res_clock::period::denominator;
					const int64 part_ = (cntr % freq) * high_res_clock::period::denominator / freq;
					return high_res_clock::value{ whole + part_ };
				}
			}
		}

		#undef LIKELY_ARM
		#undef LIKELY_X86

	#elif defined(unix) ||	defined(__unix) || defined(__unix__)
		// https://www.man7.org/linux/man-pages/man3/timespec.3type.html
		#include <time.h>

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
				clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &out);
				return lib::posix::sys_time_to_100ns(out);
			}

			[[nodiscard]] inline high_res_clock::value high_res_clock::now() noexcept {
				timespec out{};
				clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &out);
				return lib::posix::high_res_time_to_ns(out);
			}
		}
	#else
		#error unsupported platform
	#endif
#endif