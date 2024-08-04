//
// Created by sky on 04.08.2024.
//

//
// 1.0: macro_os_windows -> value: 32 or 64 (depends on the version)
// 1.0: macro_os_linux
// 1.0: macro_os_unix    -> defined even if linux is defined
//

#pragma once

#if !defined(macros_os_windows) || !defined(macros_os_linux)
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
        #if defined(WIN64) || defined(_WIN64) || defined(__WIN64__)
            #define macros_os_windows 64
        #else
            #define macros_os_windows 32
        #endif
    #elif defined(__linux__)
        #define macros_os_linux
    #endif

    #if defined(unix) || defined(__unix) || defined(__unix__)
        #define macros_os_unix
    #endif
#endif
