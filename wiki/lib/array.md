# This is the documentation of the project: "[Library](../wiki.md)":

## Classes:
- [lib::array<T, SIZE>](#libarrayt-size)

## lib::array<T, SIZE>
- [[[nodiscard]] constexpr T* begin() noexcept;](#array_begin)
- [[[nodiscard]] constexpr const T* begin() const noexcept;](#array_const_begin)
- [[[nodiscard]] constexpr T* end() noexcept;](#array_end)
- [[[nodiscard]] constexpr const T* end() const noexcept;](#array_const_end)
- [[[nodiscard]] consteval uint64 size() const noexcept;](#array_size)
- [[[nodiscard]] constexpr T& at(uint64 position) noexcept;](#array_at)
- [[[nodiscard]] constexpr const T& at(uint64 position) const noexcept;](#array_const_at)
- [constexpr void set(uint64 position, const T& value) noexcept;](#array_set)
- [constexpr void fill(const uint64 from, const uint64 to, const T& value) noexcept;](#array_fill)
- [constexpr void clear(const T& value) noexcept;](#array_clear)
- [[[nodiscard]] constexpr T& operator[](uint64 position) noexcept;](#array_idx)
- [[[nodiscard]] constexpr const T& operator[](uint64 position) const noexcept;](#array_const_idx)
- [[[nodiscard]] constexpr T& front() noexcept;](#array_front)
- [[[nodiscard]] constexpr const T& front() const noexcept;](#array_const_front)
- [[[nodiscard]] constexpr T& back() noexcept;](#array_back)
- [[[nodiscard]] constexpr const T& back() const noexcept;](#array_const_back)
- [friend const lib::ostream& operator<<(const lib::ostream& out, const lib::array<> arr) noexcept;](#array_lshift)

##
### <p id="array_begin"> [[nodiscard]] constexpr T* begin() noexcept;
    Returns a pointer to the first element of the array.
### <p id="array_const_begin"> [[nodiscard]] constexpr T* begin() noexcept;
    Returns a const pointer to the first element of the array
### <p id="array_end"> [[nodiscard]] constexpr T* end() noexcept;
    Returns a pointer to the last element of the array
### <p id="array_const_end"> [[nodiscard]] constexpr const T* end() const noexcept;
    Returns a const pointer to the last element of the array
### <p id="array_size"> [[nodiscard]] consteval uint64 size() const noexcept;
    Returns the size of the array
### <p id="array_at"> [[nodiscard]] constexpr T& at(uint64 position) noexcept;
    Returns a reference to the element at the given position of the the array
### <p id="array_const_at"> [[nodiscard]] constexpr const T& at(uint64 position) const noexcept;
    Returns a const reference to the element at the given position of the the array
### <p id="array_set"> constexpr void set(uint64 position, const T& value) noexcept;
    Sets the element of the array at the given position to the given value
### <p id="array_fill"> constexpr void fill(const uint64 from, const uint64 to, const T& value) noexcept;
    Sets all the elements from the indexs 'from' to 'to' including to the given value
### <p id="array_clear"> constexpr void clear(const T& value) noexcept;
    Sets all the elements of the array to the given value
### <p id="array_idx"> [[nodiscard]] constexpr T& operator[](uint64 position) noexcept;
    Returns a reference to the element at the given position of the array
### <p id="array_const_idx"> [[nodiscard]] constexpr const T& operator[](uint64 position) const noexcept;
    Returns a const reference to the element at the given position of the array
### <p id="array_front"> [[nodiscard]] constexpr T& front() noexcept;
    Returns a reference to the first element of the array
### <p id="array_const_front"> [[nodiscard]] constexpr const T& front() const noexcept;
    Returns a const reference to the first element of the array
### <p id="array_back"> [[nodiscard]] constexpr T& back() noexcept;
    Returns a reference to the last element of the array
### <p id="array_const_back"> [[nodiscard]] constexpr const T& back() const noexcept;
    Returns a const reference to the last element of the array
### <p id="array_lshift"> friend const lib::ostream& operator<<(const lib::ostream& out, const lib::array<> arr) noexcept;
    Writes the array formated to the given ostream
    E.g. writes: "{ first, second, third }"