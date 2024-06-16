#ifndef ARRAY_HPP
	#define ARRAY_HPP

	#include "types.hpp"
	#include "iostream.hpp"

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

			constexpr void fill(const uint64 from, const uint64 to, const T& value) noexcept {
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

			#ifdef IOSTREAM_HPP
				template <typename T_ARRAY, uint64 S>
				friend const lib::ostream& operator<<(const lib::ostream& out, const lib::array<T_ARRAY, S> arr) noexcept {
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
			#endif
		};
	}

#endif