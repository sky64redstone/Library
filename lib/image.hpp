//
// Created by sky on 13.06.24.
//

#ifndef IMAGE_HPP
    #define IMAGE_HPP

    #include "color.hpp"
    #include "memory.hpp"

    namespace lib {
        template <typename color>
        struct basic_image {
            static_assert(is_color<color>, "the template needs to be a color");

            color* data;
            uint64 width, height;

            constexpr basic_image() noexcept : data(nullptr), width(0), height(0) {}
            constexpr basic_image(color* data, const uint64 width, const uint64 height) noexcept : data(data), width(width), height(height) {}
            constexpr basic_image(const basic_image&) noexcept = default;
            constexpr basic_image(basic_image&& other) noexcept : data(other.data), width(other.width), height(other.height) {
                other.data = nullptr; other.width = 0; other.height = 0;
            }

            constexpr basic_image& operator=(const basic_image&) noexcept = default;
            constexpr basic_image& operator=(basic_image&& other) noexcept { // lookout: the data array doesn't get deleted!!!
                data = other.data; width = other.width; height = other.height;
                other.data = nullptr; other.width = 0; other.height = 0;
                return *this;
            }

            [[nodiscard]] constexpr basic_image<color> copy() const noexcept {
                const uint64 length = width * height;
                const basic_image<color> out(new color[length], width, height);
                lib::memcpy<color>(data, out.data, length);
                return out;
            }

            [[nodiscard]] constexpr basic_image<color> make_average() const noexcept {
                return copy().average();
            }

            constexpr basic_image<color>& average() noexcept {
                const uint64 length = width * height;
                for (uint64 i = 0; i < length; ++i) {
                    data[i].average();
                }
                return *this;
            }

            [[nodiscard]] constexpr basic_image<color> make_weighted() const noexcept {
                return copy().weighted();
            }

            constexpr basic_image<color>& weighted() noexcept {
                const uint64 length = width * height;
                for (uint64 i = 0; i < length; ++i) {
                    data[i].weighted();
                }
                return *this;
            }

            [[nodiscard]] constexpr basic_image<color> make_luminosity() const noexcept {
                return copy().luminosity();
            }

            constexpr basic_image<color>& luminosity() noexcept {
                const uint64 length = width * height;
                for (uint64 i = 0; i < length; ++i) {
                    data[i].luminosity();
                }
                return *this;
            }

            [[nodiscard]] constexpr basic_image<color> make_binary() const noexcept {
                return copy().binary();
            }

            constexpr basic_image<color>& binary() noexcept {
                const uint64 length = width * height;
                for (uint64 i = 0; i < length; ++i) {
                    data[i].binary();
                }
                return *this;
            }

            constexpr basic_image<color>& remove_red() noexcept {
                const uint64 length = width * height;
                for (uint64 i = 0; i < length; ++i) {
                    data[i].remove_red();
                }
                return *this;
            }

            constexpr basic_image<color>& remove_green() noexcept {
                const uint64 length = width * height;
                for (uint64 i = 0; i < length; ++i) {
                    data[i].remove_green();
                }
                return *this;
            }

            constexpr basic_image<color>& remove_blue() noexcept {
                const uint64 length = width * height;
                for (uint64 i = 0; i < length; ++i) {
                    data[i].remove_blue();
                }
                return *this;
            }

            constexpr basic_image<color>& remove_alpha() noexcept {
                static_assert(is_color4<color>, "this method needs the alpha channel");
                const uint64 length = width * height;
                for (uint64 i = 0; i < length; ++i) {
                    data[i].remove_alpha();
                }
                return *this;
            }

            constexpr basic_image<color>& clear() noexcept {
                const uint64 length = width * height;
                for (uint64 i = 0; i < length; ++i) {
                    data[i].clear();
                }
                return *this;
            }

            [[nodiscard]] constexpr basic_image<color> make_negative() const noexcept {
                return copy().negative();
            }

            constexpr basic_image<color>& negative() noexcept {
                const uint64 length = width * height;
                for (uint64 i = 0; i < length; ++i) {
                    data[i].negative();
                }
                return *this;
            }

            [[nodiscard]] constexpr basic_image<color> make_color_binary() const noexcept {
                return copy().color_binary();
            }

            constexpr basic_image<color>& color_binary() noexcept {
                const uint64 length = width * height;
                for (uint64 i = 0; i < length; ++i) {
                    data[i].color_binary();
                }
                return *this;
            }
        };

        using image3 = basic_image<color3>;
        using image4 = basic_image<color4>;
    }

#endif //IMAGE_HPP
