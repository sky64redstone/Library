#ifndef MEMORY_HPP
	#define MEMORY_HPP

	#include "types.hpp"
	#include "math.hpp"

	namespace lib {
		template <typename T>
		constexpr inline T* memcpy(const T* const src, T* const dest, const uint64 count, const uint64 offset = 0) noexcept {
			if (src == nullptr || dest == nullptr)
				return nullptr;

			// allow: 2, 4, 8 bytes
			#define is_size(x) (sizeof(T) == x)
			constexpr bool elemental_type = is_size(2) || is_size(4) || is_size(8);
			#undef is_size

			if constexpr (elemental_type) {
				// make elemental type
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

			// allow: 2, 4, 8 bytes
			#define is_size(x) (sizeof(T) == x)
			constexpr bool elemental_type = is_size(2) || is_size(4) || is_size(8);
			#undef is_size

			if constexpr (elemental_type) {
				// make elemental type
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

			// allow: 2, 4, 8 bytes
			#define is_size(x) (sizeof(T) == x)
			constexpr bool elemental_type = is_size(2) || is_size(4) || is_size(8);
			#undef is_size

			if constexpr (elemental_type) {
				// make elemental type
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

		// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
		// todo: code more efficient way to set the value at p(x, y)
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

		// https://en.wikipedia.org/wiki/Xiaolin_Wu's_line_algorithm
		template <typename T>
		constexpr inline void memset_line_antialised(T* ptr, const T& value, double x0, double y0, double x1, double y1, const uint64 size_w) noexcept {
			if (ptr == nullptr)
				return;

			#define ipart(x) static_cast<uint64>(x)
			#define round(x) ipart(x + 0.5)
			#define fpart(x) (x - ipart(x))
			#define rfpart(x) (1 - fpart(x))
			#define abs(x) (x > 0 ? x : -x)
			#define swap(x, y) { auto temp = x; x = y; y = temp; }

			const bool steep = abs(y1 - y0) > abs(x1 - x0);

			if (steep) {
				swap(x0, y0);
				swap(x1, y1);
			}
			if (x0 > x1) {
				swap(x0, x1);
				swap(y0, y1);
			}

			auto dx = x1 - x0;
			auto dy = y1 - y0;
			double gradient = 0.0;

			if (dx == 0.0) {
				gradient = 1.0;
			} else {
				gradient = dy / dx;
			}

			auto xend = round(x0);
			auto yend = y0 + gradient * (xend - x0);
			auto xgap = rfpart(x0 + 0.5);
			const auto xpxl1 = xend;
			const auto ypxl1 = ipart(yend);

			if (steep) {
				lib::memset_point<T>(ptr, value * (rfpart(yend) * xgap), ypxl1, xpxl1, size_w);
				lib::memset_point<T>(ptr, value * (fpart(yend) * xgap), ypxl1 + 1, xpxl1, size_w);
			} else {
				lib::memset_point<T>(ptr, value * (rfpart(yend) * xgap), xpxl1, ypxl1, size_w);
				lib::memset_point<T>(ptr, value * (fpart(yend) * xgap), xpxl1, ypxl1 + 1, size_w);
			}

			auto intery = yend + gradient;

			xend = round(x1);
			yend = y1 + gradient * (xend - x1);
			xgap = fpart(x1 + 0.5);
			const auto xpxl2 = xend;
			const auto ypxl2 = ipart(yend);

			if (steep) {
				lib::memset_point<T>(ptr, value * (rfpart(yend) * xgap), ypxl2, xpxl2, size_w);
				lib::memset_point<T>(ptr, value * (fpart(yend) * xgap), ypxl2 + 1, xpxl2, size_w);

				const auto xstartloop = xpxl1 + 1;
				const auto xendloop = xpxl2 - 1;

				const uint64 increment = xstartloop < xendloop ? 1 : -1;
				for (auto x = xpxl1 + 1; x != xpxl2 - 1; x += increment) {
					lib::memset_point<T>(ptr, value * rfpart(intery), ipart(intery), x, size_w);
					lib::memset_point<T>(ptr, value * fpart(intery), ipart(intery) + 1, x, size_w);

					intery += gradient;
				}

			} else {
				lib::memset_point<T>(ptr, value * (rfpart(yend) * xgap), xpxl1, ypxl1, size_w);
				lib::memset_point<T>(ptr, value * (fpart(yend) * xgap), xpxl1, ypxl1 + 1, size_w);

				const auto xstartloop = xpxl1 + 1;
				const auto xendloop = xpxl2 - 1;

				const uint64 increment = xstartloop < xendloop ? 1 : -1;
				for (auto x = xpxl1 + 1; x != xpxl2 - 1; x += increment) {
					lib::memset_point<T>(ptr, value * rfpart(intery), x, ipart(intery), size_w);
					lib::memset_point<T>(ptr, value * fpart(intery), x, ipart(intery) + 1, size_w);

					intery += gradient;
				}
			}

			#undef ipart
			#undef round
			#undef fpart
			#undef rfpart
			#undef abs
			#undef swap
		}

		template <typename T>
		constexpr inline void memset_rect(T* ptr, const T& value, uint64 x, const uint64 y, const uint64 w, const uint64 h, const uint64 size_w) noexcept {
			if (ptr == nullptr)
				return;

			const uint64 yh = h + y;
			// 'w'-times left, 1 down
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

			const auto* const first8  = reinterpret_cast<const ubyte* const>(first);
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
				// constructor: ptr is nullptr
				//if (ptr)
				//	delete ptr;

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
				// TODO search if clang / msvc implemented it the same
				//if (ptr) // Clang-Tidy: 'if' statement is unnecessary; deleting null pointer has no effect
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

#endif