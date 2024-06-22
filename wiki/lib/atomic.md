# This is the documentation of the project: "[Library](../wiki.md)":

## Enums:
- [lib::memory_order](#libmemory_order)

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
- [T load(memory_order mem_order = memory_order::seq_cst) const noexcept;](#load_t)
- [void load(T* dest, memory_order mem_order = memory_order::seq_cst) const noexcept;](#load_v)
- [void store(T value, memory_order mem_order = memory_order::seq_cst) const noexcept;](#store_t)
- [void store(T* value_ptr, memory_order mem_order = memory_order::seq_cst) const noexcept;](#store_p)
- [T exchange(T value, memory_order mem_order = memory_order::seq_cst) const noexcept;](#exchange_t)
- [void exchange(T* value_ptr, T* dest, memory_order mem_order = memory_order::seq_cst) const noexcept;](#exchange_v)
- [bool compare_exchange(T* expected, T desired, bool weak, memory_order success_order, memory_order failure_order) const noexcept;](#compare_exchange_t)
- [bool compare_exchange(T* expected, T* desired, bool weak, memory_order success_order, memory_order failure_order) const noexcept;](#compare_exchange_v)
- [T add_fetch(T value, memory_order mem_order) const noexcept;](#add_fetch)
- [T sub_fetch(T value, memory_order mem_order) const noexcept;](#sub_fetch)
- [T and_fetch(T value, memory_order mem_order) const noexcept;](#and_fetch)
- [T xor_fetch(T value, memory_order mem_order) const noexcept;](#xor_fetch)
- [T or_fetch(T value, memory_order mem_order) const noexcept;](#or_fetch)
- [T nand_fetch(T value, memory_order mem_order) const noexcept;](#nand_fetch)
- [T fetch_add(T value, memory_order mem_order) const noexcept;](#fetch_add)
- [T fetch_sub(T value, memory_order mem_order) const noexcept;](#fetch_sub)
- [T fetch_and(T value, memory_order mem_order) const noexcept;](#fetch_and)
- [T fetch_xor(T value, memory_order mem_order) const noexcept;](#fetch_xor)
- [T fetch_or(T value, memory_order mem_order) const noexcept;](#fetch_or)
- [T fetch_nand(T value, memory_order mem_order) const noexcept;](#fetch_nand)
- [[[nodiscard]] bool test_and_set(memory_order mem_order) const noexcept](#test_and_set)
- [void clear(memory_order mem_order) const noexcept;](#clear)
- [static void thread_fence(memory_order mem_order) noexcept;](#thread_fence)
- [static void signal_fence(memory_order mem_order) noexcept;](#signal_fence)
- [[[nodiscard]] bool always_lock_free(bool alignment = false) const noexcept;](#always_lock_free)
- [[[nodiscard]] bool is_lock_free(bool alignment = false) const noexcept;](#is_lock_free)

##
### <p id="mem_relaxed"> memory_order::relaxed
    Implies no inter-thread ordering constrains.
### <p id="mem_consume"> memory_order::consume
    This is currently implemented using the stronger memory_order::acquire 
    because of a deficiency semantics for memory_order::consume
### <p id="mem_acquire"> memory_order::acquire
    Creates an inter-thread happens-before constraint from the release 
    (or stronger) semantic store to this acquire load. Can prevent 
    hoisting of code to before the operation.
### <p id="mem_release"> memory_order::release
    Creates an inter-thread happens-before constraint to acquire 
    (or stronger) semantic load that read from this release store. 
    Can prevent sinking of code to after the operation.
### <p id="mem_acq_rel"> memory_order::acq_rel
    Combines the effects of both acquire and release
### <p id="mem_seq_cst"> memory_order::seq_cst
    Enforces total ordering with all other seq_cst operations
### <p id="load_t"> T load(memory_order mem_order = memory_order::seq_cst) const noexcept;
    Returns the stored value.
    possible memory_order values:
    relaxed, seq_cst, acquire, and consume
### <p id="load_v"> void load(memory_order mem_order = memory_order::seq_cst) const noexcept;
    Copies the stored value in dest.
    possible memory_orders values:
    relaxed, seq_cst, acquire, and consume
### <p id="store_t"> void store(T value, memory_order mem_order = memory_order::seq_cst) const noexcept;
    Stores the value in the atomic value.
    possible memory_order values:
    relaxed, release, and seq_cst
### <p id="store_p"> void store(T* value_ptr, memory_order mem_order = memory_order::seq_cst) const noexcept;
    Stores the value at the value_ptr in the atomic value
    possible memory_order values:
    relaxed, release, and seq_cst
### <p id="exchange_t"> T exchange(T value, memory_order mem_order = memory_order::seq_cst) const noexcept;
    Exchanges value with the atomic value and returns the previous value stored
### <p id="exchange_v"> void exchange(T* value_ptr, T* dest, memory_order mem_order = memory_order::seq_cst) const noexcept;
    Exchanges the value at value_ptr with the atomic value and
    returns the previous value at dest
### <p id="compare_exchange_t"> void compare_exchange(T* expected, T desired, bool weak, memory_order success_order, memory_order failure_order) const noexcept;
	This function implements an atomic compare and exchange operation.
	This compares the contents of *ptr with the contents of expected. If equal, 
	the operation is a read-modify-write operation that writes desired into *ptr. 
	If they are not equal, the operation is a read and the current contents of *ptr 
	are written into expected. weak is true for weak compare_exchange, which may 
	fail spuriously, and false for the strong variation, which never fails spuriously. 
	Many targets only offer the strong variation and ignore the parameter. 
	When in doubt, use the strong variation.
	If desired is written into* ptr then true is returned and memory is affected 
	according to the memory order specified by success_memorder.There are no restrictions 
	on what memory order can be used here.
	Otherwise, false is returned and memory is affected according to failure_memorder.
	This memory order cannot be __ATOMIC_RELEASE nor __ATOMIC_ACQ_REL.
    It also cannot be a stronger order than that specified by success_memorder.
### <p id="compare_exchange_p"> void compare_exchange(T* expected, T* desired, bool weak, memory_order success_order, memory_order failure_order) const noexcept;
	This function implements an atomic compare and exchange operation.
	This compares the contents of *ptr with the contents of *expected. If equal, 
	the operation is a read-modify-write operation that writes desired into *ptr. 
	If they are not equal, the operation is a read and the current contents of *ptr 
	are written into *expected. weak is true for weak compare_exchange, which may 
	fail spuriously, and false for the strong variation, which never fails spuriously. 
	Many targets only offer the strong variation and ignore the parameter. 
	When in doubt, use the strong variation.
	If desired is written into* ptr then true is returned and memory is affected 
	according to the memory order specified by success_memorder.There are no restrictions 
	on what memory order can be used here.
	Otherwise, false is returned and memory is affected according to failure_memorder.
	This memory order cannot be __ATOMIC_RELEASE nor __ATOMIC_ACQ_REL.
    It also cannot be a stronger order than that specified by success_memorder.
### <p id="add_fetch"> T add_fetch(T value, memory_order mem_order) const noexcept;
	This function performs the operation suggested by the name, and returns the result of the operation. 
	Operations on pointer arguments are performed as if the operands were of the uintptr type.
    That is, they are not scaled by the size of the type to which the pointer points. 
### <p id="sub_fetch"> T sub_fetch(T value, memory_order mem_order) const noexcept;
	This function performs the operation suggested by the name, and returns the result of the operation. 
	Operations on pointer arguments are performed as if the operands were of the uintptr type.
    That is, they are not scaled by the size of the type to which the pointer points.
### <p id="and_fetch"> T and_fetch(T value, memory_order mem_order) const noexcept;
	This function performs the operation suggested by the name, and returns the result of the operation. 
	Operations on pointer arguments are performed as if the operands were of the uintptr type.
    That is, they are not scaled by the size of the type to which the pointer points.
### <p id="xor_fetch"> T xor_fetch(T value, memory_order mem_order) const noexcept;
	This function performs the operation suggested by the name, and returns the result of the operation. 
	Operations on pointer arguments are performed as if the operands were of the uintptr type.
    That is, they are not scaled by the size of the type to which the pointer points.
### <p id="or_fetch"> T or_fetch(T value, memory_order mem_order) const noexcept;
	This function performs the operation suggested by the name, and returns the result of the operation. 
	Operations on pointer arguments are performed as if the operands were of the uintptr type.
    That is, they are not scaled by the size of the type to which the pointer points.
### <p id="nand_fetch"> T nand_fetch(T value, memory_order mem_order) const noexcept;
	This function performs the operation suggested by the name, and returns the result of the operation. 
	Operations on pointer arguments are performed as if the operands were of the uintptr type.
    That is, they are not scaled by the size of the type to which the pointer points.
### <p id="fetch_add"> T fetch_add(T value, memory_order mem_order) const noexcept;
	This function performs the operation suggested by the name, and returns the value that had previously 
	been in *ptr.Operations on pointer arguments are performed as if the operands were of the uintptr type.
    That is, they are not scaled by the size of the type to which the pointer points.
### <p id="fetch_sub"> T fetch_sub(T value, memory_order mem_order) const noexcept;
	This function performs the operation suggested by the name, and returns the value that had previously 
	been in *ptr.Operations on pointer arguments are performed as if the operands were of the uintptr type.
    That is, they are not scaled by the size of the type to which the pointer points.
### <p id="fetch_and"> T fetch_and(T value, memory_order mem_order) const noexcept;
	This function performs the operation suggested by the name, and returns the value that had previously 
	been in *ptr.Operations on pointer arguments are performed as if the operands were of the uintptr type.
    That is, they are not scaled by the size of the type to which the pointer points.
### <p id="fetch_xor"> T fetch_xor(T value, memory_order mem_order) const noexcept;
	This function performs the operation suggested by the name, and returns the value that had previously 
	been in *ptr.Operations on pointer arguments are performed as if the operands were of the uintptr type.
    That is, they are not scaled by the size of the type to which the pointer points.
### <p id="fetch_or"> T fetch_or(T value, memory_order mem_order) const noexcept;
	This function performs the operation suggested by the name, and returns the value that had previously 
	been in *ptr.Operations on pointer arguments are performed as if the operands were of the uintptr type.
    That is, they are not scaled by the size of the type to which the pointer points.
### <p id="fetch_nand"> T fetch_nand(T value, memory_order mem_order) const noexcept;
	This function performs the operation suggested by the name, and returns the value that had previously 
	been in *ptr.Operations on pointer arguments are performed as if the operands were of the uintptr type.
    That is, they are not scaled by the size of the type to which the pointer points.
### <p id="test_and_set"> [[nodiscard]] bool test_and_set(memory_order mem_order) const noexcept;
	This function performs an atomic test - and -set operation on the byte at *ptr.
	The byte is set to some implementation defined nonzero �set� value and the return value is true if and 
	only if the previous contents were �set�.It should be only used for operands of type bool or char.
	For other types only part of the value may be set.
    All memory orders are valid.
### <p id="clear"> void clear(memory_order mem_order) const noexcept;
    This function returns true if objects of size bytes always generate lock - free atomic instructions
    for the target architecture.size must resolve to a compile - time constant and the result also resolves
    to a compile - time constant.
    ptr is an optional pointer to the object that may be used to determine alignment.
    A value of 0 indicates typical alignment should be used.The compiler may also ignore this parameter.
### <p id="thread_fence"> static void thread_fence(memory_order mem_order) noexcept;
	This function acts as a synchronization fence between threads based on the specified memory order.
    All memory orders are valid.
### <p id="signal_fence"> static void signal_fence(memory_order mem_order) noexcept;
    This function acts as a synchronization fence between a thread and signal handlers based in the same thread.
    All memory orders are valid.
### <p id="always_lock_free"> [[nodiscard]] bool always_lock_free(bool alignment = false) const noexcept;
	This function returns true if objects of size bytes always generate lock - free atomic instructions
	for the target architecture.size must resolve to a compile - time constant and the result also resolves 
	to a compile - time constant.
    ptr is an optional pointer to the object that may be used to determine alignment. 
    A value of 0 indicates typical alignment should be used.The compiler may also ignore this parameter.
### <p id="is_lock_free"> [[nodiscard]] bool is_lock_free(bool alignment = false) const noexcept;
	This function returns true if objects of size bytes always generate lock - free atomic instructions 
	for the target architecture.If the built - in function is not known to be lock - free, 
	a call is made to a runtime routine named __atomic_is_lock_free.
	ptr is an optional pointer to the object that may be used to determine alignment.
    A value of 0 indicates typical alignment should be used.The compiler may also ignore this parameter.