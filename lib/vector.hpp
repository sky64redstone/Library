#ifndef VECTOR_HPP
	#define VECTOR_HPP

	#include "types.hpp"
	#include "iostream.hpp"

	namespace lib {
		template <typename T>
		class vector {
		public:
			using type = T;

			template <typename T_>
			struct vector_heap_data {
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
						delete[] reinterpret_cast<ubyte*>(data);
				}
			};

			template <typename T_>
			struct vector_stack_data {
				static constexpr auto flag_bits = 1;
				static constexpr auto size_bits = 8 - flag_bits;
				static constexpr auto buffer_size = (sizeof(vector_heap_data<T_>) - 1) / sizeof(T_);
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
				vector_heap_data<T> heap_data;
				vector_stack_data<T> stack_data;
			};

		public:
			constexpr vector() noexcept {
				init(0);
			}

			constexpr explicit vector(const uint64 size) noexcept {
				init(size);
			}

			constexpr vector(const T* data, const T& null_data) noexcept {
				// get size
				uint64 size = 0;
				while (data[size++] != null_data) {}

				init(size);

				// copy data
				size = 0;
				while (data[size++] != null_data) {
					this->data()[size] = data[size];
				}
			}

			constexpr vector(const T* data, const uint64 size) noexcept {
				init(size);

				for (uint64 i = 0; i < size; ++i) {
					this->data()[i] = data[i];
				}
			}

			constexpr ~vector() noexcept {
				if (!heap_data.from_stack) {
					heap_data.destroy();
				}
			}

			constexpr T& at(uint64 idx) noexcept {
				return data()[idx];
			}

			constexpr const T& at(uint64 idx) const noexcept {
				return data()[idx];
			}

			constexpr void set(uint64 idx, T& value) noexcept {
				data()[idx] = value;
			}

			constexpr void set(uint64 idx, T&& value) noexcept {
				data()[idx] = value;
			}

			constexpr void clear(T& clear_value) noexcept {
				for (uint64 i = 0; i < size(); ++i) {
					set(i, clear_value);
				}
			}

			// returns true if the new size fits on the stack
			constexpr bool set_size(uint64 new_size) noexcept {
				if (new_size <= vector_stack_data<T>::buffer_size) {
					stack_data.size = new_size;
					stack_data.from_stack = true;
					return true;
				}

				const uint64 old_size = size();
				T* old_data = new T[old_size];
				for (uint64 i = 0; i < old_size; ++i) {
					old_data[i] = data()[i];
				}

				if (!from_stack()) {
					heap_data.destroy();
				}

				init(new_size);

				for (uint64 i = 0; i < old_size; ++i) {
					data()[i] = old_data[i];
				}

				delete[] old_data;

				if (old_size < new_size) {
					for (uint64 i = old_size; i < new_size; ++i) {
						data()[i] = T{ 0 };
					}
				}

				return false;
			}

			constexpr void push_back(T& value) noexcept {
				const int64 old_size = size();
				set_size(old_size + 1);
				set(old_size, value);
			}

			constexpr void push_back(T&& value) noexcept {
				const int64 old_size = size();
				set_size(old_size + 1);
				set(old_size, value);
			}

			constexpr void pop_back() noexcept {
				set_size(size() - 1);
			}

			constexpr T* data() noexcept {
				return heap_data.from_stack ? stack_data.data : heap_data.data;
			}

			constexpr const T* data() const noexcept {
				return heap_data.from_stack ? stack_data.data : heap_data.data;
			}

			[[nodiscard]] constexpr uint64 size() const noexcept {
				return heap_data.from_stack ? stack_data.size : heap_data.size;
			}

			[[nodiscard]] constexpr bool from_stack() const noexcept {
				return heap_data.from_stack;
			}

			constexpr T* begin() noexcept {
				return data();
			}

			constexpr T* end() noexcept {
				return &data()[size()];
			}

			constexpr T* front() noexcept {
				return data();
			}

			constexpr T* back() noexcept {
				return &data()[size()];
			}

			constexpr const T* begin() const noexcept {
				return data();
			}

			constexpr const T* end() const noexcept {
				return &data()[size()];
			}

			constexpr const T* front() const noexcept {
				return data();
			}

			constexpr const T* back() const noexcept {
				return &data()[size()];
			}

			constexpr T& operator[](uint64 index) noexcept {
				return at(index);
			}

			constexpr const T& operator[](uint64 index) const noexcept {
				return at(index);
			}

			#ifdef IOSTREAM_HPP
				template <typename T_>
				friend const lib::ostream& operator<<(const lib::ostream& out, const lib::vector<T_>& vec) {
					out << "{ ";
					for (uint64 i = 0; i < vec.size(); ++i) {
						if (i != 0) {
							out << ", ";
						}
						out << vec[i];
					}
					out << " }";
					return out;
				}
			#endif

		private:
			constexpr void init(uint64 size) noexcept {
				if (size <= vector_stack_data<T>::buffer_size) {
					stack_data.init(size);
				} else {
					heap_data.init(size);
				}
			}
		};
	}

#endif