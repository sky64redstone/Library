# This is the documentation of the project: "[Library](../wiki.md)":

## Macros:
- [lib_debug_break()](#lib_debug_break)
- [lib_assert()](#lib_assert)
- [LIB_ASSERT_RELEASE](#LIB_ASSERT_RELEASE)

## Functions:
- [void lib_assert() noexcept](#libassert)

##
### <p id="lib_debug_break"> lib_debug_break()
    Causes the program to stop its execution in such a way that a debugger can catch it.
### <p id="lib_assert"> lib_assert(condition)
    If the condition evaluates to true, then "nothing" happens
    else (if avariable) the debugger pauses the program execution
    Only avariable when compiling in debug-mode or #define LIB_ASSERT_RELEASE 1
### LIB_ASSERT_RELEASE
    #define to 1 to make the macro lib_assert avariable in Release-compile-mode
### <p id="libassert"> void lib_assert(bool condition, const char* filename, int linenum) noexcept;
    If the condition evaluates to true, then "nothing" happens
    else (if avariable) the debugger pauses the program execution
    The parameter filename and linenum are unused an can be read with a debugger
