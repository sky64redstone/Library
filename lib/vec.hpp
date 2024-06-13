#ifndef VEC_HPP
	#define VEC_HPP

	#include "types.hpp"
	#include "math.hpp"
	#include "iostream.hpp"

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

			#ifdef IOSTREAM_HPP
				friend const lib::ostream& operator<<(const lib::ostream& out, const vec2<T>& vec) {
					out << "(" << vec.x << ", " << vec.y << ")";
					return out;
				}
			#endif
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
			constexpr vec3(vec3<T>&& other)  noexcept : x(other.x), y(other.y), z(other.z) {
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

			#ifdef IOSTREAM_HPP
				friend const lib::ostream& operator<<(const lib::ostream& out, const vec3<T>& vec) {
					out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
					return out;
				}
			#endif
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

			#ifdef IOSTREAM_HPP
				friend const lib::ostream& operator<<(const lib::ostream& out, const vec4<T>& vec) {
					out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
					return out;
				}
			#endif
		};

		using vec4b = vec4<byte>;
		using vec4s = vec4<int16>;
		using vec4i = vec4<int32>;
		using vec4u = vec4<uint32>;
		using vec4l = vec4<int64>;
		using vec4f = vec4<float>;
		using vec4d = vec4<double>;
	}

#endif