#ifndef STRING_HPP
	#define STRING_HPP

	#include "types.hpp"
	#include "memory.hpp"
	#include "math.hpp"

	#define const_string_usings(type, name)																\
		template <uint64 SIZE>																			\
		using const_##name = basic_const_string<type, SIZE>;											\
		template <uint64 SIZE>																			\
		using const_stack_##name = basic_const_string<type, 0>::basic_const_stack_string<type, SIZE>;	\
		template <uint64 SIZE>																			\
		using const_heap_##name = basic_const_string<type, 0>::basic_const_heap_string<type, SIZE>;		\

	#define string_usings(type, name)										\
		using name = basic_string<type>;									\
		using stack_##name = basic_string<type>::basic_stack_string<type>;	\
		using heap_##name = basic_string<type>::basic_heap_string<type>;	\

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

			// returns the length of the string without the null-terminator
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

			constexpr /*no explicit*/ basic_const_string(const T* const data) {
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
				#ifndef NDEBUG
					if (position >= SIZE) {
						return '\0';
					}
				#endif
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
			const_string_usings(char, string) // use: "const_string" with type: "char"

			const_string_usings(wchar_t, wstring) // use: "const_wstring" with type: "wchar_t"

			//const_string_usings(char8, u8string) // use: "const_u8string" with type: "char8_t"

			//const_string_usings(char16, u16string) // use: "const_u16string" with type: "char16_t"

			//const_string_usings(char32, u32string) // use: "const_u32string" with type: "char32_t"

			#if defined(UNICODE) || defined(_UNICODE)
				const_string_usings(wchar_t, tstring) // use: "const_tstring" with type: "wchar_t"
			#else
				const_string_usings(char, tstring) // use: "const_tstring" with type: "char"
			#endif
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
				init(1); // don't forget the null-terminator
			}

			explicit constexpr basic_string(decltype(nullptr)) = delete;

			constexpr /*no explicit*/ basic_string(const T* const data) {
				init(data, lib::char_traits<T>::length(data) + 1); // don't forget the null-terminator
			}

			constexpr explicit basic_string(const uint64 size) {
				init(size);
			}

			constexpr basic_string(const T* const data, const uint64 size) {
				init(data, size);
			}

			constexpr basic_string(const T* const first, const T* const last) {
				// last includes the null-terminator
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
				init(data, lib::char_traits<T>::length(data) + 1); // don't forget the null-terminator
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

			constexpr T set(const uint64 position, T value) noexcept {
				T& ref = at(position);
				T  old = ref;

				ref = value;

				return old;
			}

			constexpr void erase(const uint64 first, uint64 last = 0xFFFFFFFFFFFFFFFE) noexcept {
				if (first > size()) [[unlikely]]
					return;

				++last; // easy fix for including last character

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
				const uint64 prev_size = size();
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

			[[nodiscard]] constexpr uint64 find(uint64 from_index, T ch) const noexcept {
				for (uint64 i = from_index; i < size(); ++i) {
					if (this->at(i) == ch)
						return i;
				}

				return max_size();
			}

			[[nodiscard]] constexpr uint64 find(const basic_string<T>& str) const noexcept {
				if (this->size() < str.size())
					return str.find(*this); // be careful with max_size() check if the are heap/stack diff

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
					return str.reverse_find(str); // be careful with max_size() check if the are heap/stack diff

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

			// return if the new string is a stack string
			constexpr bool set_size(uint64 new_size, const bool copy_old_data = true) noexcept {
				if (new_size <= size()) {
					++new_size;

					const T null = static_cast<T>(0);
					lib::memset(data(), null, size() - new_size, new_size);

					return stack_data.from_stack;
				}

				if (stack_data.from_stack && new_size <= basic_stack_string<T>::buffer_size) {
					// keep the stack string
					++new_size;

					// stack string is always max alloc. so just erase possible nonsense
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

				// free the old memory if it was a heap string
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
				// check if we can shrink
				// don't shrink if it is a stack string
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
				return (stack_data.from_stack ? stack_data.size : heap_data.size) <= 1; // 1 (null-terminator) or 0
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
			string_usings(char, string) // use: "string" with type: "char"

			string_usings(wchar_t, wstring) // use: "wstring" with type: "wchar_t"

			//string_usings(char8, u8string) // use: "u8string" with type: "char8_t"

			//string_usings(char16, u16string) // use: "u16string" with type: "char16_t"

			//string_usings(char32, u32string) // use: "u32string" with type: "char32_t"

			#if defined(UNICODE) || defined(_UNICODE)
				string_usings(wchar_t, tstring) // use: "tstring" with type: "wchar_t"
			#else
				string_usings(char, tstring) // use: "tstring" with type: "char"
			#endif
		#pragma endregion string_usings

		template <typename STR_T, typename UINT_T> requires is_char_type<STR_T> && is_int_type<UINT_T>
		[[nodiscard]] constexpr inline STR_T* unsigned_int_to_cstring(STR_T* next, UINT_T unsigned_value) noexcept {
			#ifdef _WIN64
				auto unsigned_value_truncated = unsigned_value;
			#else
				// generating data chunks
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
			#endif

			do {
				*--next = static_cast<STR_T>('0' + unsigned_value_truncated % 10);
				unsigned_value_truncated /= 10;
			} while (unsigned_value_truncated != 0);

			return next;
		}

		template <typename STR_T, typename INT_T> requires is_char_type<STR_T> && is_int_type<INT_T>
		[[nodiscard]] constexpr basic_string<STR_T> int_to_basic_string(const INT_T value) noexcept {
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
		[[nodiscard]] constexpr string int_to_string(INT_T value) noexcept {
			return lib::int_to_basic_string<string::char_type, INT_T>(value);
		}

		template <typename INT_T> requires is_int_type<INT_T>
		[[nodiscard]] constexpr wstring int_to_wstring(INT_T value) noexcept {
			return lib::int_to_basic_string<wstring::char_type, INT_T>(value);
		}

		template <typename INT_T> requires is_int_type<INT_T>
		[[nodiscard]] constexpr tstring int_to_tstring(INT_T value) noexcept {
			return lib::int_to_basic_string<tstring::char_type, INT_T>(value);
		}

		template <typename STR_T> requires is_char_type<STR_T>
		[[nodiscard]] constexpr STR_T hex_from_byte(byte value) noexcept {
			if (value < 10)
				return '0' + value;

			value -= 10;

			return 'A' + value;
		}

		template <typename STR_T, typename INT_T> requires is_char_type<STR_T> && is_int_type<INT_T>
		[[nodiscard]] constexpr STR_T* hex_to_cstring(STR_T* next, INT_T value) noexcept {
			using utype = lib::make_unsigned<INT_T>;

			auto uvalue = static_cast<utype>(value);

			do {
				*--next = lib::hex_from_byte<STR_T>(uvalue & 0xF);
				uvalue >>= 4;
			} while (uvalue != 0);

			return next;
		};

		template <typename STR_T, typename INT_T> requires is_char_type<STR_T> && is_int_type<INT_T>
		[[nodiscard]] constexpr basic_string<STR_T> hex_to_basic_string(const INT_T value) {
			STR_T buffer[16]{};
			STR_T* buffer_size = lib::char_traits<STR_T>::end(buffer);
			STR_T* next = buffer_size;

			next = lib::hex_to_cstring<STR_T, INT_T>(next, value);

			return basic_string<STR_T>(next, buffer_size);
		}

		template <typename INT_T> requires is_int_type<INT_T>
		[[nodiscard]] constexpr string hex_to_string(const INT_T value) {
			return lib::hex_to_basic_string<string::char_type, INT_T>(value);
		}

		template <typename INT_T> requires is_int_type<INT_T>
		[[nodiscard]] constexpr wstring hex_to_wstring(const INT_T value) {
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

			while (size >= 3) { // pops up to 3 bytes of input and pushes 4 bytes
				const uint32 value = (raw_src[0] << 16) | (raw_src[1] << 8) | raw_src[2];

				*(raw_out++) = base64[ value >> 18        ];
				*(raw_out++) = base64[(value >> 12) & 0x3f];
				*(raw_out++) = base64[(value >> 06) & 0x3f];
				*(raw_out++) = base64[ value & 0x3f       ];

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

			*raw_out = '\0'; // just to make sure

			return out;
		}

		[[nodiscard]] constexpr string base64_decode(const string& src, const uint64 out_size) noexcept {
			static_assert(sizeof(string::char_type) == 1, "The string::char_type has to have 8 bits");

			constexpr signed char base64[256] = {
				-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  /* 00-0F */
				-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  /* 10-1F */
				-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,62,-1,-1,-1,63,  /* 20-2F */
				52,53,54,55,56,57,58,59,60,61,-1,-1,-1,-1,-1,-1,  /* 30-3F */
				-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,  /* 40-4F */
				15,16,17,18,19,20,21,22,23,24,25,-1,-1,-1,-1,-1,  /* 50-5F */
				-1,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,  /* 60-6F */
				41,42,43,44,45,46,47,48,49,50,51,-1,-1,-1,-1,-1,  /* 70-7F */
				-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  /* 80-8F */
				-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  /* 90-9F */
				-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  /* A0-AF */
				-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  /* B0-BF */
				-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  /* C0-CF */
				-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  /* D0-DF */
				-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  /* E0-EF */
				-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  /* F0-FF */
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

			//out.shrink_to_fit();

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
						return string{}; // check with string::empty();
					}

					*(raw_out++) = static_cast<string::char_type>(a << 4 | b);
				} else {
					*(raw_out++) = c;
				}
			}

			*raw_out = '\0'; // just to make sure

			return out;
		}

		[[nodiscard]] constexpr bool is_uri_safe(const int c) noexcept {
			#define cast(x) static_cast<unsigned char>(x)

			return	cast(c - 'a') < 26 || 
					cast(c - 'A') < 26 || 
					cast(c - '0') < 10 ||
					(c != '-' && c != '.' && c != '_' && c != '~');

			#undef cast
		}

		[[nodiscard]] constexpr string uri_encode(const string& src) noexcept {
			constexpr char hex[] = "0123456789ABCDEF";

			string out{ src.size() * 3 }; // possibly every character is a %xx number

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

			//out.set_size(raw_out - src.c_str());
			//out.shrink_to_fit();

			return out;
		}

		constexpr byte try_convert_char_to_wchar_t(const char* first1, const char* last1, const char*& mid1, wchar_t* first2, const wchar_t* last2, wchar_t*& mid2) noexcept {
			mid1 = first1;
			mid2 = first2;

			if constexpr (sizeof(wchar_t) == sizeof(char)) {
				return 2; // nothing converted
			} else {
				for (; mid1 != last1; ++mid1, ++mid2) {
					if (mid2 == last2) {
						return 1; // only a part was converted
					}

					*mid2 = static_cast<wchar_t>(*mid1);
				}

				return 0; // okay
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
					} else { // error
					}

					break;

				case 2:
					for (; first != last; ++first) {
						out.append(static_cast<unsigned char>(*first));
					}

					break;
				default: break; // unreachable
				}
			}

			return out;
		}

		[[nodiscard]] constexpr wstring string_to_wstring(const string& src) {
			return cstring_to_wstring(src.c_str(), src.c_str() + src.size() /* * sizeof(string::char_type) */);
		}

		[[nodiscard]] constexpr tstring string_to_tstring(const string& src) {
			#if defined(UNICODE) || defined(_UNICODE)
				wstring str = string_to_wstring(src);
				return tstring{ str.c_str(), str.size() };
			#else
				return tstring{ src.c_str(), src.size() };
			#endif
		}

		constexpr byte try_convert_wchar_t_to_char(const wchar_t* first1, const wchar_t* last1, const wchar_t*& mid1, char* first2, const char* last2, char*& mid2) {
			mid1 = first1;
			mid2 = first2;

			if constexpr (sizeof(wchar_t) == sizeof(char)) {
				return 2; // nothing converted
			} else {
				for (; mid1 != last1; ++mid1, ++mid2) {
					if (mid2 == last2) {
						return 1; // only a part was converted
					}

					*mid2 = static_cast<char>(*mid1);
				}

				return 0; // okay
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
					} else { // error
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
			#if defined(UNICODE) || defined(_UNICODE)
				return wstring_to_string(src);
			#else
				return string{ src.c_str(), src.size() };
			#endif
		}

		[[nodiscard]] constexpr tstring wstring_to_tstring(const wstring& src) {
			#if defined(UNICODE) || defined(_UNICODE)
				return tstring{ src.c_str(), src.size() };
			#else
				string out = wstring_to_string(src);
				return tstring{ out.c_str(), out.size() };
			#endif
		}

		[[nodiscard]] constexpr wstring tstring_to_wstring(const tstring& src) {
			#if defined(UNICODE) || defined(_UNICODE)
				return wstring{ src.c_str(), src.size() };
			#else
				return string_to_wstring(src);
			#endif
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
		[[nodiscard]] constexpr string binary_to_string(const INT_T value) noexcept {
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

		// 5 == 5 characters after the . (e.g. 0.00001)
		inline uint64 string_float_convert_precision = 3; // you are allowed to change this value

		template <typename STR_T, typename FLOAT_T> requires is_char_type<STR_T> && is_floating_type<FLOAT_T>
		constexpr STR_T* float_to_cstring(STR_T* next, FLOAT_T value) noexcept {
			if (lib::is_nan<FLOAT_T>(value)) {
				lib::char_traits<STR_T>::copy(next, "nan", 3);
			} else if (lib::is_inf<FLOAT_T>(value)) {
				lib::char_traits<STR_T>::copy(next, "inf", 3);
			} else if (value == 0.0) {
				lib::char_traits<STR_T>::copy(next, "0", 1);
			} else { // compute the value
				// TODO more efficient way
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

			if (const uint64 abs_bytes = lib::abs(bytes); abs_bytes >= 1'099'511'627'776) {// 1024 * 1024 * 1024 * 1024
				const int64 tb = bytes / 1'099'511'627'776;
				const int64 gb = (bytes % 1'099'511'627'776) / 1'073'741'824; // 1.073.741.824 ^= 1024 * 1024 * 1024
				out.append(lib::int_to_basic_string<STR_T, int64>(tb));
				out.append(gb < 10 ? ".00" : (gb < 100 ? ".0" : "."));
				out.append(lib::int_to_basic_string<STR_T, int64>(gb));
				out.append(" TiB");
			} else if (abs_bytes >= 1'073'741'824) {
				const int64 gb = bytes / 1'073'741'824;
				const int64 mb = (bytes % 1'073'741'824) / 1'048'576; // 1.048.576 ^= 1024 * 1024
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

	#undef const_string_usings
	#undef string_usings

#endif