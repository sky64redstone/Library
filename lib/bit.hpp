#ifndef BIT_HPP
	#define BIT_HPP

	#include "types.hpp"

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
				// should be always executed at compile-time
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
				//else {
				//	std::cerr << "Index out of range" << std::endl;
				//}
			}

			[[nodiscard]] constexpr bool get(const uint64 index) const noexcept {
				if (index < Size) {
					const uint64 byteIndex = index / 8;
					const uint64 bitIndex = index % 8;
					const ubyte mask = 1 << bitIndex;
					return (data[byteIndex] & mask) != 0;
				}
				//else {
				//	std::cerr << "Index out of range" << std::endl;
				//	return false;
				//}
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

#endif