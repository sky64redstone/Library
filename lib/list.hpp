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
				item<T>* new_item = new item<T>;
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

			[[nodiscard]] constexpr T* get(uint64 index) noexcept {
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

			[[nodiscard]] constexpr const T* get(uint64 index) const noexcept {
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

			constexpr void set(uint64 index, T value) noexcept {
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

			constexpr void insert(uint64 desired_index, T value) noexcept {
				if (first == nullptr) {
					item<T>* new_item = new item<T>;
					new_item->data = value;
					first = new_item;
					return;
				}

				uint64 idx = desired_index - 1;
				item<T>* item_at_idx = first;
				for (uint64 i = 0; i < idx; ++i) {
					if (item_at_idx->next == nullptr) [[unlikely]]
						return; // the list hasn't even the item before the desired_index

					item_at_idx = item_at_idx->next;
				}

				item<T>* new_item = new item<T>;
				new_item->data = value;
				new_item->next = item_at_idx->next; // set next ptr
				item_at_idx->next = new_item; // set prev ptr
			}

			constexpr void remove(uint64 index, item<T>** out = nullptr) noexcept {
				if (first == nullptr) {
					return;
				}

				uint64 idx = index - 1;
				item<T>* item_at_idx = first;
				for (uint64 i = 0; i < idx; ++i) {
					if (item_at_idx->next == nullptr) [[unlikely]]
						return; // the list hasn't even the item before the index

					item_at_idx = item_at_idx->next;
				}

				item<T>* i = item_at_idx->next;

				if (i != nullptr) {
					item_at_idx->next = i->next;

					if (out != nullptr) {
						*out = i;
					} else {
						delete i;
					}
				}
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
				item<T>* new_item = new item<T>;
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

			[[nodiscard]] constexpr T* get(uint64 index) noexcept {
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

			[[nodiscard]] constexpr const T* get(uint64 index) const noexcept {
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