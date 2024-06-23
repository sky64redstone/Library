//
// Created by sky on 22/06/24.
//

//
// 1.0: namespace lib::packets
// 1.0: class base_message<tag_>
// 1.0: namespace lib::http
// 1.0: class http_socket
//

#ifndef NETWORK_HPP
    #define NETWORK_HPP

    #include "types.hpp"
    #include "string.hpp"

    #if defined(unix) || defined(__unix) || defined(__unix__)

        #include <sys/types.h>
        #include <sys/socket.h>
        #include <netdb.h>
        #include <fcntl.h>
        #include <unistd.h>
        #include <cerrno>

        namespace lib::http {
            using native_http_socket = int;
            static constexpr native_http_socket invalid_http_socket = -1;
        }
    #elif defined(WIN32) || defined(__WIN32) || defined(__WIN32__)

        #include <winsock2.h>

        #pragma comment(lib, "ws2_32.lib")

        namespace lib::http {
            using native_http_socket = SOCKET;
            static constexpr native_http_socket invalid_http_socket = INVALID_SOCKET;
        }
    #else
        #error unsupported platform
    #endif

    namespace lib {
        namespace packets {
            template <uint32 tag_>
            class base_message {
                ubyte flags_ = 0x00;

            public:
                constexpr  base_message() noexcept = default;
                constexpr ~base_message() noexcept = default;

                virtual constexpr void serialize(ubyte* buffer, uint32 length) noexcept = 0;
                virtual constexpr void deserialize(ubyte* data, uint32 length) noexcept = 0;

                [[nodiscard]] constexpr ubyte flags() const noexcept { return flags_; }

                [[nodiscard]] static constexpr uint32 tag() noexcept { return tag_; }
            };
        }

        enum class internet_protocol : ubyte {
            ipv4,
            ipv6
        };

        constexpr int get_address_family(const internet_protocol protocol) noexcept {
            return protocol == internet_protocol::ipv4 ? AF_INET : AF_INET6;
        }

        struct http_version final {
            uint16 major;
            uint16 minor;
        };

        struct http_status final {
            enum class code : uint16 {
                continue_ = 100,
                switching_protocol = 101,
                processing = 102,
                early_hints = 103,

                ok = 200,
                created = 201,
                accepted = 202,
                non_authoritative_information = 203,
                no_content = 204,
                reset_content = 205,
                partial_content = 206,
                multi_status = 207,
                already_reported = 208,
                im_used = 226,

                multiple_choice = 300,
                moved_permanently = 301,
                found = 302,
                see_other = 303,
                not_modified = 304,
                use_proxy = 305,
                temporary_redirect = 307,
                permanent_redirect = 308,

                bad_request = 400,
                unauthorized = 401,
                payment_required = 402,
                forbidden = 403,
                not_found = 404,
                method_not_allowed = 405,
                not_acceptable = 406,
                proxy_authentication_required = 407,
                request_timout = 408,
                conflict = 409,
                gone = 410,
                length_required = 411,
                precondition_failed = 412,
                payload_too_large = 413,
                uri_too_long = 414,
                unsupported_media_type = 415,
                range_not_satisfiable = 416,
                expectation_failed = 417,
                misdirected_request = 421,
                unprocessable_entity = 422,
                locked = 423,
                failed_dependency = 424,
                too_early = 425,
                upgrade_required = 426,
                precondition_required = 428,
                too_many_requests = 429,
                request_header_fields_too_large = 431,
                unavailable_for_legal_reasons = 451,

                internal_server_error = 500,
                not_implemented = 501,
                bad_gateway = 502,
                service_unavailable = 503,
                gateway_timeout = 504,
                http_version_not_supported = 505,
                variant_also_negotiates = 506,
                insufficient_storage = 507,
                loop_detected = 508,
                not_extended = 510,
                network_authentication_required = 511
            };

            static constexpr const char* code_to_string(const code c) noexcept {
                #define code_case(c) case code::c: return #c
                switch (c) {
                    code_case(continue_);
                    code_case(switching_protocol);
                    code_case(processing);
                    code_case(early_hints);

                    code_case(ok);
                    code_case(created);
                    code_case(accepted);
                    code_case(non_authoritative_information);
                    code_case(no_content);
                    code_case(reset_content);
                    code_case(partial_content);
                    code_case(multi_status);
                    code_case(already_reported);
                    code_case(im_used);

                    code_case(multiple_choice);
                    code_case(moved_permanently);
                    code_case(found);
                    code_case(see_other);
                    code_case(not_modified);
                    code_case(use_proxy);
                    code_case(temporary_redirect);
                    code_case(permanent_redirect);

                    code_case(bad_request);
                    code_case(unauthorized);
                    code_case(payment_required);
                    code_case(forbidden);
                    code_case(not_found);
                    code_case(method_not_allowed);
                    code_case(not_acceptable);
                    code_case(proxy_authentication_required);
                    code_case(request_timout);
                    code_case(conflict);
                    code_case(gone);
                    code_case(length_required);
                    code_case(precondition_failed);
                    code_case(payload_too_large);
                    code_case(uri_too_long);
                    code_case(unsupported_media_type);
                    code_case(range_not_satisfiable);
                    code_case(expectation_failed);
                    code_case(misdirected_request);
                    code_case(unprocessable_entity);
                    code_case(locked);
                    code_case(failed_dependency);
                    code_case(too_early);
                    code_case(upgrade_required);
                    code_case(precondition_required);
                    code_case(too_many_requests);
                    code_case(request_header_fields_too_large);
                    code_case(unavailable_for_legal_reasons);

                    code_case(internal_server_error);
                    code_case(not_implemented);
                    code_case(bad_gateway);
                    code_case(service_unavailable);
                    code_case(gateway_timeout);
                    code_case(http_version_not_supported);
                    code_case(variant_also_negotiates);
                    code_case(insufficient_storage);
                    code_case(loop_detected);
                    code_case(not_extended);
                    code_case(network_authentication_required);
                }
                #undef code_case
                return "undefined";
            }

            http_version version;
            code http_code;
            string reason;
        };

        class http_socket : public nocopy {

        };

        namespace html {

        }
    }

#endif //NETWORK_HPP
