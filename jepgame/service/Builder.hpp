/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** TreatRequest
*/

#pragma once

#include <string>
#include <cstdint>
#include <vector>
#include <iostream>

#include "OpCodes.hpp"

namespace jgo {
    class Builder {
        public:
            Builder(enums::FromAny op);
            inline Builder &operator<<(uint64_t u) {
                _caster.u64 = u;
                for (std::uint8_t e : _caster.u8)
                    _vec.push_back(e);
                return *this;
            }
            inline Builder &operator<<(uint32_t u) {
                _caster.u32[0] = u;
                for (std::size_t n = 0; n < sizeof(std::uint32_t); ++n)
                    _vec.push_back(_caster.u8[n]);
                return *this;
            }
            inline Builder &operator<<(uint16_t u) {
                _caster.u16[0] = u;
                for (std::size_t n = 0; n < sizeof(std::uint16_t); ++n)
                    _vec.push_back(_caster.u8[n]);
                return *this;
            }
            inline Builder &operator<<(uint8_t u) {
                _vec.push_back(u);
                return *this;
            }
            inline Builder &operator<<(float f) {
                _caster.f32 = f;
                for (std::size_t n = 0; n < sizeof(float); ++n)
                    _vec.push_back(_caster.u8[n]);
                return *this;
            }
            auto toString(void) -> std::string;
            auto reset(enums::FromAny op) -> void;
            inline auto display() -> void {
                std::cout << "data: " << std::hex;
                for (auto const &b : _vec)
                    std::cout << int(b) << " ";
                std::cout << std::dec << std::endl;
            }
        private:
            std::vector<std::uint8_t> _vec;
            union {
                float f32;
                std::uint8_t u8[8];
                std::uint16_t u16[4];
                std::uint32_t u32[2];
                std::uint64_t u64;
            } _caster;
    };
}
