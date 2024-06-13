#ifndef MAT_HPP
	#define MAT_HPP

	#include "vec.hpp"
	#include "iostream.hpp"

	// TODO
	// 1. helper (make_rotation_mat / translation / projection / point_at_mat)

	namespace lib {

		template <typename T> requires (is_arithmetic_type<T>)
		struct mat2 {
			T m00, m10; // x-values
			T m01, m11; // y-values

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
					+this->m11 * oneOverDeterminant, // x0
					-this->m01 * oneOverDeterminant, // y0
					-this->m10 * oneOverDeterminant, // x1
					+this->m00 * oneOverDeterminant  // y1
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

			#ifdef IOSTREAM_HPP
				friend const lib::ostream& operator<<(const lib::ostream& out, const mat2<T>& mat) {
					out << "[" << mat.m00 << ", " << mat.m10 << "]" << lib::endl;
					out << "[" << mat.m01 << ", " << mat.m11 << "]" << lib::endl;
					return out;
				}
			#endif
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
			T m00, m10, m20; // x-values
			T m01, m11, m21; // y-values
			T m02, m12, m22; // z-values

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

			#ifdef IOSTREAM_HPP
				friend const lib::ostream& operator<<(const lib::ostream& out, const mat3<T>& mat) {
					out << "[" << mat.m00 << ", " << mat.m10 << ", " << mat.m20 << "]" << lib::endl;
					out << "[" << mat.m01 << ", " << mat.m11 << ", " << mat.m21 << "]" << lib::endl;
					out << "[" << mat.m02 << ", " << mat.m12 << ", " << mat.m22 << "]" << lib::endl;
					return out;
				}
			#endif
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
			T m00, m10, m20, m30; // x-values
			T m01, m11, m21, m31; // y-values
			T m02, m12, m22, m32; // z-values
			T m03, m13, m23, m33; // w-values

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
				T m00, T m01, T m02, T m03, // x0, y0, z0, w0
				T m10, T m11, T m12, T m13, // x1, y1, z1, w1
				T m20, T m21, T m22, T m23, // x2, y2, z2, w2
				T m30, T m31, T m32, T m33  // x3, y3, z3, w3
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

			#ifdef IOSTREAM_HPP
				friend const lib::ostream& operator<<(const lib::ostream& out, const mat4<T>& mat) {
					out << "[" << mat.m00 << ", " << mat.m10 << ", " << mat.m20 << ", " << mat.m30 << "]" << lib::endl;
					out << "[" << mat.m01 << ", " << mat.m11 << ", " << mat.m21 << ", " << mat.m31 << "]" << lib::endl;
					out << "[" << mat.m02 << ", " << mat.m12 << ", " << mat.m22 << ", " << mat.m32 << "]" << lib::endl;
					out << "[" << mat.m03 << ", " << mat.m13 << ", " << mat.m23 << ", " << mat.m33 << "]" << lib::endl;
					return out;
				}
			#endif
		};

		using mat4b = mat4<byte>;
		using mat4s = mat4<int16>;
		using mat4i = mat4<int32>;
		using mat4u = mat4<uint32>;
		using mat4l = mat4<int64>;
		using mat4f = mat4<float>;
		using mat4d = mat4<double>;
	}

#endif