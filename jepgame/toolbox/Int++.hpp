/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Int++
*/

#pragma once

#include <cstdint>

template <typename T>
class IntPP {
    public:
        IntPP(T n): _n(n) {}
        T swapEndian(void) const {
            union {
                T u;
                std::uint8_t u8[sizeof(T)];
            } src = { .u = _n }, dst;

            for (std::size_t n = 0; n < sizeof(T); ++n)
                dst.u8[n] = src.u8[sizeof(T) - n - 1];
            return dst.u;
        }
    private:
        T _n;
};
