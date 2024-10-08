/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Buf
*/

#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <memory>
#include <stdexcept>

template <typename T>
class CBuffer {
    public:
        inline CBuffer
        (std::size_t count) : _ptr(new T[count]), _size(count * sizeof(T)) {
            return;
        }

        inline CBuffer(void): _ptr(new T), _size(sizeof(T)) {
            return;
        }

        inline ~CBuffer() {
            delete _ptr;
        }

        inline auto fill
        (void const *src, std::size_t size) -> CBuffer & {
            if (size > _size)
                throw std::runtime_error("invalid size");
            std::memcpy(_ptr, src, size);
            return *this;
        }

        inline auto fill(void const *src) -> CBuffer & {
            std::memcpy(_ptr, src, _size);
            return *this;
        }

        inline auto operator[](std::size_t index) -> T & {
            if (index >= _size)
                throw std::runtime_error("index too big");
            return _ptr[index];
        }

        inline auto operator*(void) -> T & {
            return *_ptr;
        }

        inline auto size(void) const -> std::size_t {
            return _size;
        }

        inline auto toBytes(void) const -> std::vector<std::uint8_t> {
            std::uint8_t *bytes = reinterpret_cast<std::uint8_t *>(_ptr);

            return std::vector<std::uint8_t>(bytes, bytes + _size);
        }

    protected:
    private:
        T *_ptr;
        std::size_t _size;
};
