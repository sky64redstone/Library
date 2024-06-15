//
// Created by sky on 13.06.24.
//

//
// 1.0 exit(exit_code)
// todo 1.0 log_fatal()
// todo 1.0 log_error()
// todo 1.0 log_warning()
// todo 1.0 log_normal()
// todo 1.0 log_debug()
//

#ifndef PROCESS_HPP
    #define PROCESS_HPP
    #if defined(unix) || defined(__unix__) || defined(__unix)
        #include <unistd.h>
    #elif defined(_WIN32) || defined(_WIN64)
        #include <windows.h>
    #endif

    namespace lib {
        inline void exit(const int exit_code) noexcept {
            #if defined(unix) || defined(__unix__) || defined(__unix)
                ::_exit(exit_code);
            #elif defined(_WIN32) || defined(_WIN64)
                // TODO windows program exit
            #endif
        }
    }

#endif //PROCESS_HPP
