#ifndef COLOR_HPP
	#define COLOR_HPP

	#include "types.hpp"

	namespace lib {
		struct color3 {
			lib::ubyte r;
			lib::ubyte g;
			lib::ubyte b;

			constexpr color3() noexcept { r = 0; g = 0; b = 0; }
			constexpr color3(const lib::ubyte r, const lib::ubyte g, const  lib::ubyte b) noexcept : r(r), g(g), b(b) {}
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
			constexpr /*no explicit*/ color4(const lib::uint32 color_code) noexcept : data(color_code) {}
			constexpr color4(const float r, const float g, const float b, const float a = 1.0f) noexcept
				: r(static_cast<ubyte>(r * 255)), g(static_cast<ubyte>(g * 255)), b(static_cast<ubyte>(b * 255)), a(static_cast<ubyte>(a * 255)) {}
			constexpr /*no explicit*/ color4(const color3& c, lib::ubyte a = 0xFF) noexcept : r(c.r), g(c.g), b(c.b), a(a) {}
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
		inline constexpr bool is_color3 = is_same_type<COLOR, color3>;

		template <typename COLOR>
		inline constexpr bool is_color4 = is_same_type<COLOR, color4>;

		template <typename COLOR>
		inline constexpr bool is_color = is_any_of_type<COLOR, color3, color4>;
	}

#endif