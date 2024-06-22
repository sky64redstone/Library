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

        #include <sys/socket.h>

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

        namespace http {
            enum class http_status {
                pending,
                completed,
                failed
            };

            class http_socket {
            protected:
                http_status status;
                int32 status_code;
                string reason_phrase;
                string content_type;
                uint64 response_size;
                void* response_data;
                // internal
                native_http_socket socket;
                int32 connect_pending;
                int32 request_send;
                string address;
                string request_header;
                void* request_data;
                uint64 request_size;
                uint64 data_size;
                uint64 data_capacity;
                void* data;

            public:
                constexpr http_socket() noexcept :
                    status(http_status::pending), status_code(0), response_size(0),
                    response_data(nullptr), socket(0), connect_pending(1),
                    request_send(0), request_data(nullptr), request_size(0),
                    data_size(0), data_capacity(0), data(nullptr) {}

                http_status process() noexcept;
                void release() noexcept;

                static http_socket* get(string url) noexcept {
                    #ifdef _WIN32
                        WSADATA wsa_init;
                        if (WSAStartup(MAKEWORD(1, 0), &wsa_init) != 0)
                            return nullptr;
                    #endif

                    string address(256);
                    string port(16);

                    if (internal_parse_url(url, address, port) == 0)
                        return nullptr;

                    native_http_socket socket = internal_connect(address, port);

                    return nullptr;
                }

                static http_socket post(string url, const void* data, uint64 size) noexcept;

            protected:
                static constexpr int32 internal_parse_url(const string& url, string& address, string& port) noexcept {
                    if (char_traits<char>::compare(url.c_str(), "http://", 7) != 0)
                        return 0;

                    url.erase(0, 6);

                    // find end of address part of url
                    uint64 address_end = url.find(':');
                    if (address_end == url.max_size())
                        address_end = url.find('/');
                    if (address_end == url.max_size())
                        address_end = url.size();

                    // extract address
                    if (url.size() > address.size())
                        return 0;
                    address.assign(url);

                    // check if there is a port defined
                    if (address.at(address_end) == ':') {
                        uint64 port_end = address.find(address_end + 1, '/');
                        if (port_end == address.max_size())
                            port_end = url.size() - address_end;
                        if (port_end >= port.size())
                            return 0;
                        char_traits<char>::copy(port.data(), url.c_str() + address_end, port_end);
                    } else {
                        if (port.size() < 3)
                            return 0;
                        port.assign("80");
                    }

                    return 1;
                }

                static constexpr native_http_socket internal_connect(string& address, string& port) noexcept {
                    return invalid_http_socket;
                }

                static constexpr http_socket* internal_create(uint64 requested_data_size) noexcept {
                    return nullptr;
                }
            };
        }
    }

#endif //NETWORK_HPP
