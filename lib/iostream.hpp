#ifndef IOSTREAM_HPP
	#define IOSTREAM_HPP

	#include "types.hpp"
	#include "string.hpp"

	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
		#define NOMINMAX
		#include <windows.h>

		namespace lib {
			namespace io {
				using iostream_handle = HANDLE;
				using iostream_length = DWORD;
				using iostream_pos = LONG;

				constexpr inline iostream_handle invalid_iostream_handle = nullptr;

				inline iostream_handle get_cout_handle() noexcept {
					return GetStdHandle(STD_OUTPUT_HANDLE);
				}

				inline iostream_handle get_cerr_handle() noexcept {
					return GetStdHandle(STD_ERROR_HANDLE);
				}

				inline iostream_handle get_cin_handle() noexcept {
					return GetStdHandle(STD_INPUT_HANDLE);
				}

				inline void write_iostream_handle(iostream_handle h, const void* const d, iostream_length l) noexcept {
					iostream_length bytes = 0;
					WriteFile(h, d, l, &bytes, nullptr);
				}

				inline void read_iostream_handle(iostream_handle h, void* const b, iostream_length l) noexcept {
					iostream_length bytes = 0;
					ReadFile(h, b, l, &bytes, nullptr);
				}

				inline void seek_set_iostream_handle(iostream_handle h, iostream_pos p) noexcept {
					SetFilePointer(h, p, nullptr, FILE_BEGIN);
				}

				inline void seek_cur_iostream_handle(iostream_handle h, iostream_pos o) noexcept {
					SetFilePointer(h, o, nullptr, FILE_CURRENT);
				}

				inline void seek_end_iostream_handle(iostream_handle h, iostream_pos o) noexcept {
					SetFilePointer(h, o, nullptr, FILE_END);
				}

				inline iostream_length tell_iostream_handle(iostream_handle h) noexcept {
					return SetFilePointer(h, 0, nullptr, FILE_CURRENT);
				}

				inline void close_iostream_handle(iostream_handle h) noexcept {
					CloseHandle(h);
				}
			}
		}

	#elif defined(unix) ||	defined(__unix) || defined(__unix__)
		#include <unistd.h>

		namespace lib {
			namespace io {
				using iostream_handle = int; // technically it is named: file descriptor
				using iostream_length = size_t;
				using iostream_pos = off_t;

				constexpr inline iostream_handle invalid_iostream_handle = 0;

				inline iostream_handle get_cout_handle() noexcept {
					return STDOUT_FILENO;
				}

				inline iostream_handle get_cerr_handle() noexcept {
					return STDERR_FILENO;
				}

				inline iostream_handle get_cin_handle() noexcept {
					return STDIN_FILENO;
				}

				inline void write_iostream_handle(const iostream_handle h, const void* const d, const iostream_length l) noexcept {
					write(h, d, l);
				}

				inline void read_iostream_handle(const iostream_handle h, void* const b, const iostream_length l) noexcept {
					read(h, b, l);
				}

				inline void seek_set_iostream_handle(const iostream_handle h, const iostream_pos p) noexcept {
					lseek(h, p, SEEK_SET);
				}

				inline void seek_cur_iostream_handle(const iostream_handle h, const iostream_pos o) noexcept {
					lseek(h, o, SEEK_CUR);
				}

				inline void seek_end_iostream_handle(const iostream_handle h, const iostream_pos o) noexcept {
					lseek(h, o, SEEK_END);
				}

				inline iostream_length tell_iostream_handle(const iostream_handle h) noexcept {
					return lseek(h, 0, SEEK_CUR);
				}

				inline void close_iostream_handle(const iostream_handle h) noexcept {
					close(h);
				}
			}
		}

	#else
		#error unsupported platform
	#endif

	namespace lib {
		inline constexpr char endl = '\n';

		class basic_iostream {
		protected:
			io::iostream_handle handle;

			constexpr basic_iostream() noexcept {
				this->handle = io::invalid_iostream_handle;
			}

			constexpr explicit basic_iostream(const io::iostream_handle h) noexcept {
				this->handle = h;
			}

		public:
			void seek_set(const io::iostream_pos position) const noexcept {
				io::seek_set_iostream_handle(handle, position);
			}

			void seek_current(const io::iostream_pos offset) const noexcept {
				io::seek_cur_iostream_handle(handle, offset);
			}

			void seek_end(const io::iostream_pos offset) const noexcept {
				io::seek_end_iostream_handle(handle, offset);
			}

			[[nodiscard]] io::iostream_length tell() const noexcept {
				return io::tell_iostream_handle(handle);
			}

			[[nodiscard]] const io::iostream_handle& native() const noexcept {
				return handle;
			}

			void close() noexcept {
				if (!handle)
					return;

				io::close_iostream_handle(handle);
				handle = io::invalid_iostream_handle;
			}
		};

		class ostream : public basic_iostream {
		public:
			explicit ostream(const io::iostream_handle h) noexcept : basic_iostream(h) {}

			void write(const void* const data, const io::iostream_length length) const noexcept {
				io::write_iostream_handle(handle, data, length);
			}

			void put(const ubyte data) const noexcept {
				io::write_iostream_handle(handle, &data, 1);
			}
		};

		class istream : public basic_iostream {
		public:
			explicit istream(const io::iostream_handle h) noexcept : basic_iostream(h) {}

			void read(void* buffer, const io::iostream_length length) const noexcept {
				io::read_iostream_handle(handle, buffer, length);
			}

			[[nodiscard]] char get() const noexcept {
				char out = '\0';
				io::read_iostream_handle(handle, &out, 1);
				return out;
			}

			[[nodiscard]] lib::string get_string(const io::iostream_length length) const noexcept {
				lib::string out(length);
				io::read_iostream_handle(handle, out.data(), length);
				return out;
			}
		};

		inline const ostream cout(io::get_cout_handle());
		inline const ostream cerr(io::get_cerr_handle());
		inline const istream cin (io::get_cin_handle ());

		namespace io {
			enum class console_color : ubyte {
				BLACK,
				BLUE,
				GREEN,
				CYAN,
				RED,
				MAGENTA,
				BROWN,
				GREY,
				DARK_GREY,
				LIGHT_BLUE,
				LIGHT_GREEN,
				LIGHT_CYAN,
				LIGHT_RED,
				LIGHT_MAGENTA,
				YELLOW,
				WHITE
			};

			#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
				inline void set_console_color(const ostream& console_stream, console_color fore, console_color back) noexcept {
					iostream_handle handle = console_stream.native();
					SetConsoleTextAttribute(handle, (static_cast<WORD>(fore) & 0xF) + ((static_cast<WORD>(back) & 0xF) << 4));
				}
			#elif defined(unix) ||	defined(__unix) || defined(__unix__)
				inline void set_console_color(const ostream& console_stream, console_color fore, console_color back) noexcept {
					const char* colors[] = {
						"\033[22;30m",  // Black color
						"\033[22;34m",  // Blue color
						"\033[22;32m",  // Green color
						"\033[22;36m",  // Cyan color
						"\033[22;31m",  // Red color
						"\033[22;35m",  // Magenta color
						"\033[22;33m",  // Brown color
						"\033[22;37m",  // Grey color
						"\033[01;30m",  // Dark grey color
						"\033[01;34m",  // Light blue color
						"\033[01;32m",  // Light green color
						"\033[01;36m",  // Light cyan color
						"\033[01;31m",  // Light red color
						"\033[01;35m",  // Light magenta color
						"\033[01;33m",  // Yellow color
						"\033[01;37m"   // White color
					};
					const char* backgrounds[] = {
						"\033[00000m",  // Black color
						"\033[02;44m",  // Blue color
						"\033[02;42m",  // Green color
						"\033[02;46m",  // Cyan color
						"\033[02;41m",  // Red color
						"\033[02;45m",  // Magenta color
						"\033[02;43m",  // Brown color
						"\033[02;47m",  // Grey color
						"\033[00;40m",  // Dark grey color
						"\033[00;44m",  // Light blue color
						"\033[00;42m",  // Light green color
						"\033[00;46m",  // Light cyan color
						"\033[00;41m",  // Light red color
						"\033[00;45m",  // Light magenta color
						"\033[00;43m",  // Yellow color
						"\033[00;47m"   // White color
					};
					console_stream.write(backgrounds[static_cast<int>(back) - static_cast<int>(console_color::BLACK)], 8);
					console_stream.write(colors[static_cast<int>(fore) - static_cast<int>(console_color::BLACK)], 8);
				}
			#else
				#error unsupported plattform
			#endif
		}

		// overloading operators

		inline const ostream& operator<<(const ostream& out, const char ch) noexcept {
			out.put(ch);
			return out;
		}

		inline const ostream& operator<<(const ostream& out, const char* const str) noexcept {
			const uint64 length = lib::char_traits<char>::length(str);
			out.write(str, length);
			return out;
		}

		template <typename STR_T, uint64 SIZE> requires is_char_type<STR_T>
		const ostream& operator<<(const ostream& out, const lib::basic_const_string<STR_T, SIZE>& str) noexcept {
			out.write(str.c_str(), SIZE * sizeof(STR_T));
			return out;
		}

		template <typename STR_T> requires is_char_type<STR_T>
		const ostream& operator<<(const ostream& out, const lib::basic_string<STR_T>& str) noexcept {
			out.write(str.c_str(), str.size() * sizeof(STR_T));
			return out;
		}

		template <typename STR_T, uint64 SIZE> requires is_char_type<STR_T>
		const ostream& operator<<(const ostream& out, const lib::basic_const_string<STR_T, SIZE>&& str) noexcept {
			out.write(str.c_str(), SIZE * sizeof(STR_T));
			return out;
		}

		template <typename STR_T> requires is_char_type<STR_T>
		const ostream& operator<<(const ostream& out, const lib::basic_string<STR_T>&& str) noexcept {
			out.write(str.c_str(), str.size() * sizeof(STR_T));
			return out;
		}

		template <typename T> requires lib::is_int_type<T>
		const ostream& operator<<(const ostream& out, const T& value) noexcept {
			const lib::string str = lib::int_to_string<T>(value);
			out.write(str.c_str(), str.size());
			return out;
		}

		template <typename T> requires lib::is_floating_type<T>
		const ostream& operator<<(const ostream& out, const T& value) noexcept {
			const lib::string str = lib::float_to_string<T>(value);
			out.write(str.c_str(), str.size());
			return out;
		}

		template <typename T> requires lib::is_int_type<T>
			const ostream& operator<<(const ostream& out, const T&& value) noexcept {
				const lib::string str = lib::int_to_string<T>(value);
			out.write(str.c_str(), str.size());
			return out;
		}

		template <typename T> requires lib::is_floating_type<T>
			const ostream& operator<<(const ostream& out, const T&& value) noexcept {
				const lib::string str = lib::float_to_string<T>(value);
			out.write(str.c_str(), str.size());
			return out;
		}

		template <typename T> requires (!lib::is_char_type<T>)
		const ostream& operator<<(const ostream& out, const T* const ptr) noexcept {
			const lib::string str = lib::hex_to_string(reinterpret_cast<uint64>(ptr));
			out.write(str.c_str(), str.size());
			return out;
		}

		inline const ostream& operator<<(const ostream& out, const io::console_color& color) noexcept {
			io::set_console_color(out, color, io::console_color::BLACK);
			return out;
		}

		inline const ostream& operator<<(const ostream& out, const io::console_color&& color) noexcept {
			io::set_console_color(out, color, io::console_color::BLACK);
			return out;
		}
	}

#endif