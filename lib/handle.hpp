//
// Created by sky on 09.06.24.
//

#ifndef HANDLE_HPP
    #define HANDLE_HPP

#include "array.hpp"
    #include "memory.hpp"
    #include "types.hpp"

    namespace lib {
        struct native_handle {
            enum flags : uint32 {
                invalid = 0,

                readable = 1 << 0,
                writeable = 1 << 1,
                append_only = 1 << 2,

                non_blocking = 1 << 3,
                seekable = 1 << 4,
                aligned_io = 1 << 5,
                kernel_handle = 1 << 6,

                file = 1 << 7,
                directory = 1 << 8,
                symlink = 1 << 9,
                pipe = 1 << 10,
                socket = 1 << 11,
                multiplexer = 1 << 12,
                process = 1 << 13,
                section = 1 << 14,
                allocation = 1 << 15,
                path = 1 << 16,
                tls_socket = 1 << 17,
                http_socket = 1 << 18,

                pointer = 1 << 19,
                extra = 1 << 20, // e.g. ipv6 instead of ipv4

                connected = 1 << 21,

                safety_barriers = 1 << 22,
                cache_metadata = 1 << 23,
                cache_reads = 1 << 24,
                cache_writes = 1 << 25,
                cache_temporary = 1 << 26
            };

            union {
                intptr data;    // easy to set to -1 (default)
                int fd;         // posix file descriptor
                int pid;        // posix process identifier
                void* handle;   // win32 handle (equivalent to HANDLE)
                uintptr sock;   // win32 socket (equivalent to SOCKET)
            };
            flags flag; // can be more than one flag

            constexpr native_handle() noexcept : data(-1), flag(invalid) {}
            constexpr native_handle(const flags flag, const int posix_handle) noexcept : fd(posix_handle), flag(flag) {}
            constexpr native_handle(const flags flag, void* win32_handle) noexcept : handle(win32_handle), flag(flag) {}
            constexpr native_handle(const flags flag, const uintptr win32_socket) noexcept : sock(win32_socket), flag(flag) {}

            constexpr native_handle(const native_handle&) noexcept = default;
            constexpr native_handle(native_handle&& other) noexcept : data(other.data), flag(other.flag) {
                other.data = -1; other.flag = invalid;
            }

            constexpr native_handle& operator=(const native_handle&) noexcept = default;
            constexpr native_handle& operator=(native_handle&& other) noexcept {
                data = other.data; flag = other.flag;
                other.data = -1; other.flag = invalid;
                return *this;
            }

            constexpr bool operator==(const native_handle& other) const noexcept {
                return other.data == data && other.flag == flag;
            }

            constexpr bool operator!=(const native_handle& other) const noexcept {
                return other.data != data || other.flag != flag;
            }

            [[nodiscard]] constexpr bool is_valid() const noexcept {
                return data != -1 && flag != invalid;
            }

            [[nodiscard]] constexpr bool is_readable() const noexcept { return flag & readable; }
            [[nodiscard]] constexpr bool is_writeable() const noexcept { return flag & writeable; }
            [[nodiscard]] constexpr bool is_append_only() const noexcept { return flag & append_only; }
            [[nodiscard]] constexpr bool is_non_blocking() const noexcept { return flag & non_blocking; }
            [[nodiscard]] constexpr bool is_seekable() const noexcept { return flag & seekable; }
            [[nodiscard]] constexpr bool requires_aligned_io() const noexcept { return flag & aligned_io; }
            [[nodiscard]] constexpr bool is_kernel_handle() const noexcept { return flag & kernel_handle; }
            [[nodiscard]] constexpr bool is_file() const noexcept { return flag & file; }
            [[nodiscard]] constexpr bool is_directory() const noexcept { return flag & directory; }
            [[nodiscard]] constexpr bool is_symlink() const noexcept { return flag & symlink; }
            [[nodiscard]] constexpr bool is_pipe() const noexcept { return flag & pipe; }
            [[nodiscard]] constexpr bool is_socket() const noexcept { return flag & socket; }
            [[nodiscard]] constexpr bool is_multiplexer() const noexcept { return flag & multiplexer; }
            [[nodiscard]] constexpr bool is_process() const noexcept { return flag & process; }
            [[nodiscard]] constexpr bool is_section() const noexcept { return flag & section; }
            [[nodiscard]] constexpr bool is_allocation() const noexcept { return flag & allocation; }
            [[nodiscard]] constexpr bool is_path() const noexcept { return flag & path; }
            [[nodiscard]] constexpr bool is_tls_socket() const noexcept { return flag & tls_socket; }
            [[nodiscard]] constexpr bool is_http_socket() const noexcept { return flag & http_socket; }
            [[nodiscard]] constexpr bool is_pointer() const noexcept { return flag & pointer; }
            [[nodiscard]] constexpr bool is_extra() const noexcept { return flag & extra; }
            [[nodiscard]] constexpr bool is_connected() const noexcept { return flag & connected; }
            [[nodiscard]] constexpr bool has_safety_barriers() const noexcept { return flag & safety_barriers; }
            [[nodiscard]] constexpr bool is_caching_metadata() const noexcept { return flag & cache_metadata; }
            [[nodiscard]] constexpr bool is_caching_reads() const noexcept { return flag & cache_reads; }
            [[nodiscard]] constexpr bool is_caching_writes() const noexcept { return flag & cache_writes;}
            [[nodiscard]] constexpr bool is_caching_temporary() const noexcept { return flag & cache_temporary; }
        };

        enum class handle_creation : lib::ubyte {
            open_existing,      // only create the handle when the file exists
            only_if_not_exist,  // only create the handle when the file doesn't exist
            if_needed,          // create the file if it doesn't exist and create the handle
            truncate_existing,  // only create the handle and truncates the file when it exists
            always_new          // if the file exists, then truncate_existing, else create the file
        };

        struct handle : nocopy {
            enum flags : uint16 {
                none = 0,
                unlink_on_close = 1 << 0,
                disable_safety_barriers = 1 << 1,
                disable_safety_unlinks = 1 << 2,
                disable_prefetching = 1 << 3,
                maximum_prefetching = 1 << 4,
                win32_disable_unlink_emulation = 1 << 5,
                win32_disable_sparse_file_creation = 1 << 6, // Windows NTFS https://learn.microsoft.com/en-us/windows/win32/fileio/sparse-file-operations
                disable_parallelism = 1 << 7,
                win32_create_sensitive_directory = 1 << 8,
                multiplexable = 1 << 9,
                byte_lock_insanity = 1 << 10,
                anonymous_inode = 1 << 11
            };

            enum caching : ubyte {
                unchanged = 0x0,
                no_caching = 0x1,
                only_metadata = 0x2,
                reads = 0x3,
                reads_and_metadata = 0x5,
                all = 0x6,
                safety_barriers = 0x7,
                temporary = 0x8
            };

        protected:
            native_handle data{};
            flags flag;

        public:
            constexpr handle() noexcept : flag(none) {}
            constexpr handle(const native_handle& native, const flags flag) noexcept : data(native), flag(flag) {}
            virtual ~handle() noexcept;
            constexpr handle(handle&& other) noexcept : data(move(other.data)), flag(other.flag) {
                other.flag = none; other.data = native_handle{};
            }

        private:
            constexpr void* operator new(const uint64 size, handle* ptr) noexcept {
               (void)size;
                return ptr;
            }

        public:
            handle& operator=(handle&& other) noexcept {
                if (this == &other) return *this;
                this->~handle();
                new(this) handle(move(other));
                return *this;
            }

            // returns true on success
            virtual bool close() noexcept;

            [[nodiscard]] handle clone() const noexcept;

            virtual native_handle release() noexcept {
                native_handle out{ move(data) };
                return out;
            }

            virtual void set_append_only(bool value) noexcept;
            
            [[nodiscard]] constexpr caching kernel_caching() const noexcept {
                const bool safety_barriers_ = has_safety_barriers();
                const bool caching_metadata = is_caching_metadata();
                const bool caching_reads = is_caching_reads();
                const bool caching_writes = is_caching_writes();

                if (is_caching_temporary())
                    return temporary;
                if (caching_metadata && caching_reads && caching_writes)
                    return safety_barriers_ ? safety_barriers : all;
                if (caching_metadata && caching_reads)
                    return reads_and_metadata;
                if (caching_reads)
                    return reads;
                if (caching_metadata)
                    return only_metadata;
                
                return no_caching;
            }
            
            [[nodiscard]] constexpr flags get_flags() const noexcept { return flag; }
            [[nodiscard]] constexpr native_handle native() const noexcept { return data; }
            [[nodiscard]] constexpr bool is_valid() const noexcept { return data.is_valid(); }

            [[nodiscard]] constexpr bool is_readable() const noexcept { return data.is_readable(); }
            [[nodiscard]] constexpr bool is_writeable() const noexcept { return data.is_writeable(); }
            [[nodiscard]] constexpr bool is_append_only() const noexcept { return data.is_append_only(); }
            [[nodiscard]] constexpr bool is_non_blocking() const noexcept { return data.is_non_blocking(); }
            [[nodiscard]] constexpr bool is_seekable() const noexcept { return data.is_seekable(); }
            [[nodiscard]] constexpr bool requires_aligned_io() const noexcept { return data.requires_aligned_io(); }
            [[nodiscard]] constexpr bool is_kernel_handle() const noexcept { return data.is_kernel_handle(); }
            [[nodiscard]] constexpr bool is_file() const noexcept { return data.is_file(); }
            [[nodiscard]] constexpr bool is_directory() const noexcept { return data.is_directory(); }
            [[nodiscard]] constexpr bool is_symlink() const noexcept { return data.is_symlink(); }
            [[nodiscard]] constexpr bool is_pipe() const noexcept { return data.is_pipe(); }
            [[nodiscard]] constexpr bool is_socket() const noexcept { return data.is_socket(); }
            [[nodiscard]] constexpr bool is_multiplexer() const noexcept { return data.is_multiplexer(); }
            [[nodiscard]] constexpr bool is_process() const noexcept { return data.is_process(); }
            [[nodiscard]] constexpr bool is_section() const noexcept { return data.is_section(); }
            [[nodiscard]] constexpr bool is_allocation() const noexcept { return data.is_allocation(); }
            [[nodiscard]] constexpr bool is_path() const noexcept { return data.is_path(); }
            [[nodiscard]] constexpr bool is_tls_socket() const noexcept { return data.is_tls_socket(); }
            [[nodiscard]] constexpr bool is_http_socket() const noexcept { return data.is_http_socket(); }
            [[nodiscard]] constexpr bool is_pointer() const noexcept { return data.is_pointer(); }
            [[nodiscard]] constexpr bool is_extra() const noexcept { return data.is_extra(); }
            [[nodiscard]] constexpr bool is_connected() const noexcept { return data.is_connected(); }
            [[nodiscard]] constexpr bool has_safety_barriers() const noexcept { return data.has_safety_barriers(); }
            [[nodiscard]] constexpr bool is_caching_metadata() const noexcept { return data.is_caching_metadata(); }
            [[nodiscard]] constexpr bool is_caching_reads() const noexcept { return data.is_caching_reads(); }
            [[nodiscard]] constexpr bool is_caching_writes() const noexcept { return data.is_caching_writes(); }
            [[nodiscard]] constexpr bool is_caching_temporary() const noexcept { return data.is_caching_temporary(); }
        };

        // Platform-dependent implementation
	    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
            inline handle::~handle() noexcept {
                if (data.is_valid()) {
                    if (!handle::close()) {
                        #ifndef NDEBUG
                            //log_debug();
                        #endif
                        //log_fatal();
                        //abort();
                    }
                }
            }

            inline bool handle::close() noexcept {
                if (data.is_valid()) {
                    if (has_safety_barriers() && is_writeable()) {
                        if (FlushFileBuffers(data.handle) == 0) [[unlikely]] {
                            return false; // error
                        }
                    }
                    if (CloseHandle(data.handle) == 0) [[unlikely]] {
                        return false; // error
                    }
                }
                return true; // success
            }

            inline handle handle::clone() const noexcept {
                handle out(native_handle{}, flag);
                out.data.handle = INVALID_HANDLE_VALUE;
                if (DuplicateHandle(GetCurrentProcess(), data.handle, GetCurrentProcess(), &out.data.handle, 0, 0, DUPLICATE_SAME_ACCESS) == 0) {
                    out.data.data = -1;
                    return out;
                }
                return out;
            }

            inline void handle::set_append_only(const bool value) noexcept {
                if (value) {
                    data.flag |= native_handle::flags::append_only;
                } else {
                    constexpr uint32 no_append_only = ~native_handle::flags::append_only;
                    data.flag &= no_append_only;
                }
            }
        #elif defined(posix) || defined(__posix) || defined(__posix__)
            inline handle::~handle() {
                if (data.is_valid()) {
                    if (!handle::close()) {
                        //log_fatal();
                        //abort();
                    }
                }
            }
        #endif

    }

#endif //HANDLE_HPP
