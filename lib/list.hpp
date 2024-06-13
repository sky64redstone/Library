#ifndef LIST_HPP
	#define LIST_HPP

	#include "types.hpp"
	#include "iostream.hpp"

	namespace lib {
		template <typename T>
		class linked_list {
		private:
			template <typename T_>
			struct item {
			public:
				constexpr item() {
					this->next = nullptr;
				}

				T_ data;
				item<T_>* next;
			};

			item<T>* first;

		public:
			constexpr void push_back(T data) noexcept {
				auto* new_item = new item<T>;
				new_item->data = data;

				if (first != nullptr) {
					item<T>* ptr = first;

					for (; ptr->next != nullptr; ptr = ptr->next) {}

					ptr->next = new_item;
					return;
				}

				first = new_item;
			}

			// returns removed item
			constexpr T pop_back() noexcept {
				if (first != nullptr) {
					if (first->next == nullptr) {
						T value = first->data;

						delete first;
						
						first = nullptr;

						return value;
					}

					item<T>* ptr = first;

					for (; ptr->next->next != nullptr; ptr = ptr->next) {}

					T out = ptr->next->data;

					delete ptr->next;

					ptr->next = nullptr;

					return out;
				}

				return T{ 0 };
			}

			constexpr void push_front(T value) noexcept {
				auto* ptr = new item<T>;
				ptr->data = value;
				ptr->next = first;
				first = ptr;
			}

			[[nodiscard]] constexpr T* get(const uint64 index) noexcept {
				if (first == nullptr) [[unlikely]]
					return nullptr;

				item<T>* out = first;
				for (uint64 i = 0; i < index; ++i) {
					if (out->next == nullptr) [[unlikely]]
						return nullptr;

					out = out->next;
				}

				return &out->data;
			}

			[[nodiscard]] constexpr const T* get(const uint64 index) const noexcept {
				if (first == nullptr) [[unlikely]]
					return nullptr;

				item<T>* out = first;

				for (uint64 i = 0; i < index; ++i) {
					if (out->next == nullptr) [[unlikely]]
						return nullptr;

					out = out->next;
				}

				return &out->data;
			}

			constexpr void set(const uint64 index, T value) noexcept {
				if (first == nullptr) [[unlikely]]
					return;

				item<T>* out = first;
				for (uint64 i = 0; i < index; ++i) {
					if (out->next == nullptr) [[unlikely]]
						return;

					out = out->next;
				}

				out->data = value;
			}

			constexpr void insert(const uint64 desired_index, T value) noexcept {
				if (first == nullptr) {
					auto* new_item = new item<T>;
					new_item->data = value;
					first = new_item;
					return;
				}

				if (desired_index == 0) {
					push_front(value);
					return;
				}

				const uint64 idx = desired_index - 1;
				item<T>* item_at_idx = first;
				for (uint64 i = 0; i < idx; ++i) {
					if (item_at_idx->next == nullptr) [[unlikely]]
						return; // the list hasn't even the item before the desired_index

					item_at_idx = item_at_idx->next;
				}

				auto* new_item = new item<T>;
				new_item->data = value;
				new_item->next = item_at_idx->next; // set next ptr
				item_at_idx->next = new_item; // set prev ptr
			}

			constexpr T remove(const uint64 index) noexcept {
				if (first == nullptr) {
					return static_cast<T>(0);
				}

				const uint64 idx = index - 1;
				item<T>* item_at_idx = first;
				for (uint64 i = 0; i < idx; ++i) {
					if (item_at_idx->next == nullptr) [[unlikely]]
						return static_cast<T>(0); // the list hasn't even the item before the index

					item_at_idx = item_at_idx->next;
				}

				item<T>* i = item_at_idx->next;

				if (i != nullptr) {
					item_at_idx->next = i->next;
				}
				if (item_at_idx != nullptr) {
					T out = item_at_idx->data;
					delete item_at_idx;
					return out;
				}
				return static_cast<T>(0);
			}

			template <typename T_LIST>
			friend const lib::ostream& operator<<(const lib::ostream& out, const lib::linked_list<T_LIST>& list) noexcept {
				const T_LIST* value = nullptr;
				uint64 ptr = 0;
				out << "{ ";
				while ((value = list.get(ptr)) != nullptr) {
					if (ptr != 0) {
						out << ", ";
					}
					out << *value;
					++ptr;
				}
				out << " }";
				return out;
			}
		};

		template <typename T>
		class double_linked_list {
		private:
			template <typename T_>
			struct item {
			public:
				T_ data;
				item* next;
				item* prev;

				item() {
					this->next = nullptr;
					this->prev = nullptr;
				}
			};

			item<T>* first;
			item<T>* last;

		public:
			constexpr void push_back(T data) noexcept {
				auto* new_item = new item<T>;
				new_item->data = data;

				if (first == nullptr) {
					first = new_item;
					last = new_item;
					return;
				}

				item<T>* ptr = last;

				ptr->next = new_item;
				last = new_item;
			}

			constexpr T pop_back() noexcept {
				if (last == nullptr) {
					return static_cast<T>(0);
				}

				item<T>* ptr = last;
				last = ptr->prev;
				T out = ptr->data;
				delete ptr;

				return out;
			}

			constexpr void push_front(T value) noexcept {
				auto* ptr = new item<T>;
				ptr->data = value;
				ptr->prev = nullptr;
				ptr->next = first;
				first = ptr;
				if (ptr->next != nullptr) {
					ptr->next->prev = ptr;
				}
			}

			[[nodiscard]] constexpr T* get(const uint64 index) noexcept {
				if (first == nullptr) [[unlikely]]
					return nullptr;

				item<T>* out = first;
				for (uint64 i = 0; i < index; ++i) {
					if (out->next == nullptr) [[unlikely]]
						return nullptr;

					out = out->next;
				}

				return &out->data;
			}

			[[nodiscard]] constexpr const T* get(const uint64 index) const noexcept {
				if (first == nullptr) [[unlikely]]
					return nullptr;

				item<T>* out = first;
				for (uint64 i = 0; i < index; ++i) {
					if (out->next == nullptr) [[unlikely]]
						return nullptr;

					out = out->next;
				}

				return &out->data;
			}

			constexpr void set(const uint64 index, T value) noexcept {
				if (first == nullptr) [[unlikely]]
					return;

				item<T>* out = first;
				for (uint64 i = 0; i < index; ++i) {
					if (out->next == nullptr) [[unlikely]]
						return;

					out = out->next;
				}

				out->data = value;
			}

			// don't use a 0 for the index!!!
			constexpr void reverse_set(const uint64 index, T value) noexcept {
				if (last == nullptr) [[unlikely]]
					return;

				if (index == 0) [[unlikely]]
					return set(index, value);

				item<T>* out = last;
				for (uint64 i = index; i > 0; --i) {
					if (out->prev == nullptr) [[unlikely]]
						return;

					out = out->prev;
				}

				out->data = value;
			}

			constexpr void insert(const uint64 desired_index, T value) noexcept {
				if (first == nullptr) {
					auto* new_item = new item<T>;
					new_item->data = value;
					first = new_item;
					return;
				}

				if (desired_index == 0) {
					push_front(value);
					return;
				}

				const uint64 idx = desired_index - 1;
				item<T>* item_at_idx = first;
				for (uint64 i = 0; i < idx; ++i) {
					if (item_at_idx->next == nullptr) [[unlikely]]
						return; // the list hasn't even the item before the desired_index

					item_at_idx = item_at_idx->next;
				}

				auto* new_item = new item<T>;
				new_item->data = value;
				new_item->next = item_at_idx->next; // set next ptr
				item_at_idx->next = new_item; // set prev ptr
			}

			constexpr T remove(const uint64 index) noexcept {
				if (first == nullptr) [[unlikely]]
					return static_cast<T>(0);

				item<T>* item_at_idx = first;
				for (uint64 i = 0; i < index; ++i) {
					if (item_at_idx->next == nullptr) [[unlikely]]
						return static_cast<T>(0);

					item_at_idx = item_at_idx->next;
				}

				item_at_idx->prev->next = item_at_idx->next;
				item_at_idx->next->prev = item_at_idx->prev;

				T out = item_at_idx->data;
				delete item_at_idx;
				return out;
			}

			constexpr T reverse_remove(const uint64 index) noexcept {
				if (last == nullptr) [[unlikely]]
					return static_cast<T>(0);

				item<T>* item_at_idx = last;
				for (uint64 i = index; i > 0; --i) {
					if (item_at_idx->prev == nullptr) [[unlikely]]
						return static_cast<T>(0);

					item_at_idx = item_at_idx->prev;
				}

				item_at_idx->prev->next = item_at_idx->next;
				item_at_idx->next->prev = item_at_idx->prev;

				T out = item_at_idx->data;
				delete item_at_idx;
				return out;
			}

			template <typename T_LIST>
			friend const lib::ostream& operator<<(const lib::ostream& out, const lib::double_linked_list<T_LIST>& list) noexcept {
				const T_LIST* value = nullptr;
				uint64 ptr = 0;
				out << "{ ";
				while ((value = list.get(ptr)) != nullptr) {
					if (ptr != 0) {
						out << ", ";
					}
					out << *value;
					++ptr;
				}
				out << " }";
				return out;
			}
		};
	}

#endif