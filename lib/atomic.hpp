#ifndef ATOMIC_HPP
	#define ATOMIC_HPP

	#include "types.hpp"

	// for now lib::atomic values are clang & GCC only
	#if defined(_MSC_VER) && !defined(__clang__)
		#error [ATOMICS ONLY] Not supported compiler!!!
	#endif

	namespace lib {
		enum class memory_order : uint32 {
			relaxed = __ATOMIC_RELAXED,
			consume = __ATOMIC_CONSUME,
			acquire = __ATOMIC_ACQUIRE,
			release = __ATOMIC_RELEASE,
			acq_rel = __ATOMIC_ACQ_REL,
			seq_cst = __ATOMIC_SEQ_CST
		};

		template <typename T>
		class atomic {
		private:
			T* ptr;

		public:
			atomic() noexcept {
				ptr = new T;
				*ptr = static_cast<T>(0);
			}

			// returns the stored value
			// possible memory_order values:
			// relaxed, seq_cst, acquire, and consume
			T load(memory_order mem_order = memory_order::seq_cst) const noexcept {
				return __atomic_load_n(ptr, static_cast<uint32>(mem_order));
			}

			// copies the stored value in dest
			// possible memory_order values:
			// relaxed, seq_cst, acquire, and consume
			void load(T* dest, memory_order mem_order = memory_order::seq_cst) const noexcept {
				__atomic_load(ptr, dest, static_cast<uint32>(mem_order));
			}

			// stores the value in the atomic value
			// possible memory_order values:
			// relaxed, release, and seq_cst
			void store(T value, memory_order mem_order = memory_order::seq_cst) const noexcept {
				__atomic_store_n(ptr, value, static_cast<uint32>(mem_order));
			}

			// stores the value at the value_ptr in the atomic value
			// possible memory_order values:
			// relaxed, release, and seq_cst
			void store(T* value_ptr, memory_order mem_order = memory_order::seq_cst) const noexcept {
				__atomic_store(ptr, value_ptr, static_cast<uint32>(mem_order));
			}

			// exchanges value with the atomic value and returns the previous value stored
			// possible memory_order value:
			// TODO find out!
			T exchange(T value, memory_order mem_order = memory_order::seq_cst) const noexcept {
				return __atomic_exchange_n(ptr, value, static_cast<uint32>(mem_order));
			}

			// exchanges the value at value_ptr with the atomic value and returns the previous value at dest
			// possible memory_order values:
			// TODO find out!
			void exchange(T* value_ptr, T* dest, memory_order mem_order = memory_order::seq_cst) const noexcept {
				return __atomic_exchange(ptr, value_ptr, dest, static_cast<uint32>(mem_order));
			}

			// This function implements an atomic compare and exchange operation.
			// This compares the contents of *ptr with the contents of expected. If equal, 
			// the operation is a read-modify-write operation that writes desired into *ptr. 
			// If they are not equal, the operation is a read and the current contents of *ptr 
			// are written into expected. weak is true for weak compare_exchange, which may 
			// fail spuriously, and false for the strong variation, which never fails spuriously. 
			// Many targets only offer the strong variation and ignore the parameter. 
			// When in doubt, use the strong variation.
			// If desired is written into* ptr then true is returned and memory is affected 
			// according to the memory order specified by success_memorder.There are no restrictions 
			// on what memory order can be used here.
			// Otherwise, false is returned and memory is affected according to failure_memorder.
			// This memory order cannot be __ATOMIC_RELEASE nor __ATOMIC_ACQ_REL.
			// It also cannot be a stronger order than that specified by success_memorder.
			bool compare_exchange(T* expected, T desired, bool weak, memory_order success_order, memory_order failure_order) const noexcept {
				return __atomic_compare_exchange_n(ptr, expected, desired, weak, static_cast<uint32>(success_order), static_cast<uint32>(failure_order));
			}

			// This function implements an atomic compare and exchange operation.
			// This compares the contents of *ptr with the contents of *expected. If equal, 
			// the operation is a read-modify-write operation that writes desired into *ptr. 
			// If they are not equal, the operation is a read and the current contents of *ptr 
			// are written into *expected. weak is true for weak compare_exchange, which may 
			// fail spuriously, and false for the strong variation, which never fails spuriously. 
			// Many targets only offer the strong variation and ignore the parameter. 
			// When in doubt, use the strong variation.
			// If desired is written into* ptr then true is returned and memory is affected 
			// according to the memory order specified by success_memorder.There are no restrictions 
			// on what memory order can be used here.
			// Otherwise, false is returned and memory is affected according to failure_memorder.
			// This memory order cannot be __ATOMIC_RELEASE nor __ATOMIC_ACQ_REL.
			// It also cannot be a stronger order than that specified by success_memorder.
			bool compare_exchange(T* expected, T* desired, bool weak, memory_order success_order, memory_order failure_order) const noexcept {
				return __atomic_compare_exchange(ptr, expected, desired, weak, static_cast<uint32>(success_order), static_cast<uint32>(failure_order));
			}

			// This function performs the operation suggested by the name, and returns the result of the operation. 
			// Operations on pointer arguments are performed as if the operands were of the uintptr type. 
			// That is, they are not scaled by the size of the type to which the pointer points. 
			T add_fetch(T value, memory_order mem_order) const noexcept {
				return __atomic_add_fetch(ptr, value, static_cast<uint32>(mem_order));
			}

			// This function performs the operation suggested by the name, and returns the result of the operation. 
			// Operations on pointer arguments are performed as if the operands were of the uintptr type. 
			// That is, they are not scaled by the size of the type to which the pointer points. 
			T sub_fetch(T value, memory_order mem_order) const noexcept {
				return __atomic_sub_fetch(ptr, value, static_cast<uint32>(mem_order));
			}

			// This function performs the operation suggested by the name, and returns the result of the operation. 
			// Operations on pointer arguments are performed as if the operands were of the uintptr type. 
			// That is, they are not scaled by the size of the type to which the pointer points. 
			T and_fetch(T value, memory_order mem_order) const noexcept {
				return __atomic_and_fetch(ptr, value, static_cast<uint32>(mem_order));
			}

			// This function performs the operation suggested by the name, and returns the result of the operation. 
			// Operations on pointer arguments are performed as if the operands were of the uintptr type. 
			// That is, they are not scaled by the size of the type to which the pointer points. 
			T xor_fetch(T value, memory_order mem_order) const noexcept {
				return __atomic_xor_fetch(ptr, value, static_cast<uint32>(mem_order));
			}

			// This function performs the operation suggested by the name, and returns the result of the operation. 
			// Operations on pointer arguments are performed as if the operands were of the uintptr type. 
			// That is, they are not scaled by the size of the type to which the pointer points. 
			T or_fetch(T value, memory_order mem_order) const noexcept {
				return __atomic_or_fetch(ptr, value, static_cast<uint32>(mem_order));
			}

			// This function performs the operation suggested by the name, and returns the result of the operation. 
			// Operations on pointer arguments are performed as if the operands were of the uintptr type. 
			// That is, they are not scaled by the size of the type to which the pointer points. 
			T nand_fetch(T value, memory_order mem_order) const noexcept {
				return __atomic_nand_fetch(ptr, value, static_cast<uint32>(mem_order));
			}

			// This function performs the operation suggested by the name, and returns the value that had previously 
			// been in *ptr.Operations on pointer arguments are performed as if the operands were of the uintptr type.
			// That is, they are not scaled by the size of the type to which the pointer points.
			T fetch_add(T value, memory_order mem_order) const noexcept {
				return __atomic_fetch_add(ptr, value, static_cast<uint32>(mem_order));
			}

			// This function performs the operation suggested by the name, and returns the value that had previously 
			// been in *ptr.Operations on pointer arguments are performed as if the operands were of the uintptr type.
			// That is, they are not scaled by the size of the type to which the pointer points.
			T fetch_sub(T value, memory_order mem_order) const noexcept {
				return __atomic_fetch_sub(ptr, value, static_cast<uint32>(mem_order));
			}

			// This function performs the operation suggested by the name, and returns the value that had previously 
			// been in *ptr.Operations on pointer arguments are performed as if the operands were of the uintptr type.
			// That is, they are not scaled by the size of the type to which the pointer points.
			T fetch_and(T value, memory_order mem_order) const noexcept {
				return __atomic_fetch_and(ptr, value, static_cast<uint32>(mem_order));
			}

			// This function performs the operation suggested by the name, and returns the value that had previously 
			// been in *ptr.Operations on pointer arguments are performed as if the operands were of the uintptr type.
			// That is, they are not scaled by the size of the type to which the pointer points.
			T fetch_xor(T value, memory_order mem_order) const noexcept {
				return __atomic_fetch_xor(ptr, value, static_cast<uint32>(mem_order));
			}

			// This function performs the operation suggested by the name, and returns the value that had previously 
			// been in *ptr.Operations on pointer arguments are performed as if the operands were of the uintptr type.
			// That is, they are not scaled by the size of the type to which the pointer points.
			T fetch_or(T value, memory_order mem_order) const noexcept {
				return __atomic_fetch_or(ptr, value, static_cast<uint32>(mem_order));
			}

			// This function performs the operation suggested by the name, and returns the value that had previously 
			// been in *ptr.Operations on pointer arguments are performed as if the operands were of the uintptr type.
			// That is, they are not scaled by the size of the type to which the pointer points.
			T fetch_nand(T value, memory_order mem_order) const noexcept {
				return __atomic_fetch_nand(ptr, value, static_cast<uint32>(mem_order));
			}

			// This function performs an atomic test - and -set operation on the byte at *ptr.
			// The byte is set to some implementation defined nonzero �set� value and the return value is true if and 
			// only if the previous contents were �set�.It should be only used for operands of type bool or char.
			// For other types only part of the value may be set.
			// All memory orders are valid.
			[[nodiscard]] bool test_and_set(memory_order mem_order) const noexcept {
				return __atomic_test_and_set(ptr, static_cast<uint32>(mem_order));
			}

			// This function returns true if objects of size bytes always generate lock - free atomic instructions 
			// for the target architecture.size must resolve to a compile - time constant and the result also resolves 
			// to a compile - time constant.
			// ptr is an optional pointer to the object that may be used to determine alignment.
			// A value of 0 indicates typical alignment should be used.The compiler may also ignore this parameter.
			void clear(memory_order mem_order) const noexcept {
				__atomic_clear(ptr, static_cast<uint32>(mem_order));
			}

			// This function acts as a synchronization fence between threads based on the specified memory order.
			// All memory orders are valid.
			static void thread_fence(memory_order mem_order) noexcept {
				__atomic_thread_fence(static_cast<int>(mem_order));
			}

			// This function acts as a synchronization fence between a thread and signal handlers based in the same thread.
			// All memory orders are valid.
			static void signal_fence(memory_order mem_order) noexcept {
				__atomic_signal_fence(static_cast<int>(mem_order));
			}

			// This function returns true if objects of size bytes always generate lock - free atomic instructions
			// for the target architecture.size must resolve to a compile - time constant and the result also resolves 
			// to a compile - time constant.
			// ptr is an optional pointer to the object that may be used to determine alignment. 
			// A value of 0 indicates typical alignment should be used.The compiler may also ignore this parameter.
			[[nodiscard]] bool always_lock_free(bool alignment = false) const noexcept {
				return __atomic_always_lock_free(sizeof(T), alignment ? ptr : nullptr);
			}

			// This function returns true if objects of size bytes always generate lock - free atomic instructions 
			// for the target architecture.If the built - in function is not known to be lock - free, 
			// a call is made to a runtime routine named __atomic_is_lock_free.
			// ptr is an optional pointer to the object that may be used to determine alignment.
			// A value of 0 indicates typical alignment should be used.The compiler may also ignore this parameter.
			[[nodiscard]] bool is_lock_free(bool alignment = false) const noexcept {
				return __atomic_is_lock_free(sizeof(T), alignment ? ptr : nullptr);
			}
		};
	}

#endif