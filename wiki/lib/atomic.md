# This is the documentation of the project: "[Library](../wiki.md)":

## Enums:
- [lib::memory_order]()

## Classes:
- [lib::atomic<T>](#libatomicT)

## lib::memory_order
- [relaxed](#mem_relaxed)
- [consume](#mem_consume)
- [acquire](#mem_acquire)
- [release](#mem_release)
- [acq_rel](#mem_acq_rel)
- [seq_cst](#mem_seq_cst)

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
### <p id="mem_relaxed> memory_order::relaxed
  Implies no inter-thread ordering constrains.
### <p id="mem_consume> memory_order::consume
  This is currently implemented using the stronger memory_order::acquire because of a deficiency semantics for memory_order::consume
### <p id="mem_acquire> memory_order::acquire
  Creates an inter-thread happens-before constraint from the release (or stronger) semantic store to this acquire load. Can prevent hoisting of code to before the operation.
### <p id="mem_release> memory_order::release
  Creates an inter-thread happens-before constraint to acquire (or stronger) semantic load that read from this release store. Can prevent sinking of code to after the operation.
### <p id="mem_acq_rel> memory_order::acq_rel
  Combines the effects of both acquire and release
### <p id="mem_seq_cst> memory_order::seq_cst
  Enforces total ordering with all other seq_cst operations
