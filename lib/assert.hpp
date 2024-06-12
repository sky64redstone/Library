#ifndef ASSERT_HPP
	#define ASSERT_HPP

	// define LIB_ASSERT_RELEASE to 1 -> lib_assert when release
	#ifndef LIB_ASSERT_RELEASE
		#define LIB_ASSERT_RELEASE 0
	#endif

	// __builtin_debugtrap for some versions of clang
	// On MSVC and Intel C / C++ Compiler: __debugbreak
	// For ARM C / C++ Compiler : __breakpoint(42)
	// For x86 / x86_64, assembly : int3
	// For ARM Thumb, assembly : .inst 0xde01
	// For ARM AArch64, assembly : .inst 0xd4200000
	// For other ARM, assembly : .inst 0xe7f001f0
	// For Alpha, assembly : bpt
	// For non - hosted C with GCC(or something which masquerades as it), __builtin_trap
	// Otherwise, include signal.h and
	// If defined(SIGTRAP) (i.e., POSIX), raise(SIGTRAP)
	// Otherwise, raise(SIGABRT)
	#ifdef __has_builtin
		#if __has_builtin(__builtin_debugtrap)
			#define lib_debug_break() __builtin_debugtrap()
		#elif __has_builtin(builtin_trap)
			#define lib_debug_break() __builtin_trap()
		#endif
	#endif

	#ifndef lib_debug_break
		#ifdef _MSC_VER
			#define lib_debug_break() __debugbreak()
		#elif defined(__CC_ARM)
			#define lib_debug_break() __breakpoint(42)
		#else
			#include <signal.h>

			#ifdef SIGTRAP
				#define lib_debug_break() raise(SIGTRAP)
			#else
				#define lib_debug_break() raise(SIGABRT)
			#endif
		#endif
	#endif

	#ifndef NDEBUG
		#define DEBUG_LIKELY [[likely]]
	#else
		#define DEBUG_LIKELY
	#endif

	void lib_assert(auto condition, const char* filename, int linenum) noexcept {
		if (condition) DEBUG_LIKELY // likely because when the condition fails, there is anyway a break
			return;

		lib_debug_break();
	}

	#undef DEBUG_LIKELY

	#if !defined(NDEBUG) || LIB_ASSERT_RELEASE
		#define lib_assert(condition) lib_assert(condition, __FILE__, __LINE__)
	#else
		#define lib_assert(condition)
	#endif
#endif