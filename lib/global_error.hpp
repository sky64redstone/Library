//
// Created by sky on 15.06.24.
//

//
// error_codes:
// 1.0 error_none
// 1.0 error_handle_close
//
// 1.0 error_code_name(code)
//

#ifndef GLOBAL_ERROR_HPP
    #define GLOBAL_ERROR_HPP

    #include "types.hpp"

    namespace lib {
        enum error_codes : ubyte {
            error_none = 0,
            error_handle_close = 1
        };

        constexpr const char* error_code_name(const error_codes code) {
            #define error_case(x) case x: return #x
            switch (code) {
                error_case(error_none);
                error_case(error_handle_close);

                default: return "not defined";
            }
            #undef error_case
        }
    }

#endif //GLOBAL_ERROR_HPP
