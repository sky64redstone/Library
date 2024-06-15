//
// Created by sky on 15.06.24.
//

//
// error_codes:
// 1.0 error_none
// 1.0 error_handle_close
//

#ifndef GLOBAL_ERROR_HPP
    #define GLOBAL_ERROR_HPP

    namespace lib {
        enum error_codes {
            error_none = 0,
            error_handle_close = 1
        };
    }

#endif //GLOBAL_ERROR_HPP
