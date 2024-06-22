# This is the documentation of the project: "[Library](../wiki.md)":

## Enums:
- [lib::memory_order]()

## Classes:
- [lib::atomic<T>](#libatomicT)

## lib::memory_order
- [relaxed]()
- [consume]()
- [acquire]()
- [release]()
- [acq_rel]()
- [seq_cst]()

## lib::atomic<T>
- [T load(memory_order mem_order = memory_order::seq_cst) const noexcept;]()
- [void load(T* dest, memory_order mem_order = memory_order::seq_cst) const noexcept;]()
- [void store(T value, memory_order mem_order = memory_order::seq_cst) const noexcept;]()
- [void store(T* value_ptr, memory_order mem_order = memory_order::seq_cst) const noexcept;]()
- [T exchange(T value, memory_order mem_order = memory_order::seq_cst) const noexcept;]()
- [void exchange(T* value_ptr, T* dest, memory_order mem_order = memory_order::seq_cst) const noexcept;]()
- [bool compare_exchange(T* expected, T desired, bool weak, memory_order success_order, memory_order failure_order) const noexcept;]()
- [bool compare_exchange(T* expected, T* desired, bool weak, memory_order success_order, memory_order failure_order) const noexcept;]()
- [T add_fetch(T value, memory_order mem_order) const noexcept;]()
- [T sub_fetch(T value, memory_order mem_order) const noexcept;]()
- [T and_fetch(T value, memory_order mem_order) const noexcept;]()
- [T xor_fetch(T value, memory_order mem_order) const noexcept;]()
- [T or_fetch(T value, memory_order mem_order) const noexcept;]()
- [T nand_fetch(T value, memory_order mem_order) const noexcept;]()
- [T fetch_add(T value, memory_order mem_order) const noexcept;]()
- [T fetch_sub(T value, memory_order mem_order) const noexcept;]()
- [T fetch_and(T value, memory_order mem_order) const noexcept;]()
- [T fetch_xor(T value, memory_order mem_order) const noexcept;]()
- [T fetch_or(T value, memory_order mem_order) const noexcept;]()
- [T fetch_nand(T value, memory_order mem_order) const noexcept;]()
- [[[nodiscard]] bool test_and_set(memory_order mem_order) const noexcept]()
- [void clear(memory_order mem_order) const noexcept;]()
- [static void thread_fence(memory_order mem_order) noexcept;]()
- [static void signal_fence(memory_order mem_order) noexcept;]()
- [[[nodiscard]] bool always_lock_free(bool alignment = false) const noexcept;]()
- [[[nodiscard]] bool is_lock_free(bool alignment = false) const noexcept;]()

##
### 
