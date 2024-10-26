//
// Created by sky 30.8.2024
//
// Contents:
//
// OS identification:
// - macros_os
// - macros_os_windows
// - macros_os_linux (non android)
// - macros_os_freebsd
// - macros_os_openbsd
// - macros_os_netbsd
// - macros_os_macos (also ios)
// - macros_os_android
//
// Compiler identification:
// - macros_compiler
// - macros_compiler_gcc
// - macros_compiler_clang
// - macros_compiler_msvc
//
// Misc:
// - __has_builtin(x)
// - macros_noexcept
// - macros_constexpr
// - macros_consteval
// - __COUNTER__
// - macros_random
//

#ifndef MACROS_HPP
  #define MACROS_HPP

  // OS identification
  
  #if defined(_WIN16) || defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(_TOS_WIN__) || defined(__WINDOWS__)
    #if defined(_WIN64)
      #define macros_os_windows 64
      #define macros_os "Windows 64-bit"
    #elif defined(_WIN16)
      #define macros_os_windows 16
      #define macros_os "Windows 16-bit"
    #else
      #define macros_os_windows 32
      #define macros_os "Windows 32-bit"
    #endif
  #endif // macros_os_windows

  #if (defined(linux) || defined(__linux) || defined(__linux__)) && !defined(__ANDROID__)
    #define macros_os_linux
    #define macros_os "Linux"
  #endif // macros_os_linux

  #if defined(__FreeBSD__)
    #define macros_os_freebsd
    #define macros_os "FreeBSD"
  #endif // macros_os_freebsd

  #if defined(__OpenBSD__)
    #define macros_os_openbsd
    #define macros_os "OpenBSD"
  #endif // macros_os_openbsd

  #if defined(__NetBSD__)
    #define macros_os_netbsd
    #define macros_os "NetBSD"
  #endif // macros_os_netbsd

  #if defined(macintosh) || defined(Macintosh) || (defined(__APPLE__) && defined(__MACH__))
    #if defined(__APPLE__) && defined(__MACH__) // Mac OS X
      #define macros_os_macos 10
      #define macros_os "Mac OS X"
    #else // Mac OS 9
      #define macros_os_macos 9
      #define macros_os "Mac OS 9"
    #endif // Mac OS version
  #endif // macros_os_macos

  #if defined(__ANDROID__)
    #define macros_os_android
    #define macros_os "Android"
  #endif // macros_os_android
  
  // Compiler identification
  
  #if defined(__GNUC__)
    #define macros_compiler_gcc
    #define macros_compiler "gcc"
  #endif // macros_compiler_gcc

  #if defined(__clang__)
    #define macros_compiler_clang
    #define macros_compiler "clang"
  #endif // macros_compiler_clang

  #if defined(_MSC_VER)
    #define macros_compiler_msvc
    #define macros_compiler "msvc"
  #endif // macros_compiler_msvc

  // Misc

  #if !defined(__has_builtin)
    #define __has_builtin(x) 0
  #endif // __has_builtin
  
  #if __cplusplus < 201112L // __cplusplus < c++11
    #define macros_noexcept throw()
    #define macros_constexpr
  #else // __cplusplus >= c++11
    #define macros_noexcept noexcept
    #define macros_constexpr constexpr
  #endif // c++11

  #if __cplusplus < 202002L // __cplusplus < c++20
    #define macros_consteval
  #else // __cplusplus > c++20
    #define macros_consteval
  #endif // c++20

  #if !defined(__COUNTER__)
    #define __COUNTER__ 0
  #endif // __COUNTER__

  #define macros_random(min, max) (min + (((__COUNTER__ + (__LINE__ * __LINE__)) * 2654435761L) % (max - min + 1)))

#endif // MACROS_HPP
