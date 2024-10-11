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

#include "jepgame/toolbox/CBuf.hpp"
#include "OpCodes.hpp"

namespace jgo {
    using u8 = std::uint8_t;
    using s8 = std::int8_t;
    using u16 = std::uint16_t;
    using s16 = std::int16_t;
    using u32 = std::uint32_t;
    using s32 = std::int32_t;
    using u64 = std::uint64_t;
    using s64 = std::int64_t;

    class Builder {
        public:
            Builder(enums::FromAny op);
            Builder(jgo::u8 op);
            inline Builder &operator<<(u64 u) {
                _caster.int64 = u;
                for (u8 e : _caster.int8)
                    _vec.push_back(e);
                return *this;
            }
            inline Builder &operator<<(u32 u) {
                _caster.int32[0] = u;
                for (std::size_t n = 0; n < sizeof(u32); ++n)
                    _vec.push_back(_caster.int8[n]);
                return *this;
            }
            inline Builder &operator<<(u16 u) {
                _caster.int16[0] = u;
                for (std::size_t n = 0; n < sizeof(u16); ++n)
                    _vec.push_back(_caster.int8[n]);
                return *this;
            }
            inline Builder &operator<<(u8 u) {
                _vec.push_back(u);
                return *this;
            }
            inline Builder &operator<<(float f) {
                _caster.f32 = f;
                for (std::size_t n = 0; n < sizeof(float); ++n)
                    _vec.push_back(_caster.int8[n]);
                return *this;
            }
            inline auto display() -> void {
                std::cout << "data: " << std::hex;
                for (auto const &b : _vec)
                    std::cout << static_cast<int>(b) << " ";
                std::cout << std::dec << std::endl;
            }
            inline auto empty(void) const noexcept -> bool {
                return _vec.empty();
            }
            template <typename X, typename Y>
            inline auto restore(Y &e) -> Builder & {
                CBuffer<X> buf;

                buf.fill(_vec.data());
                e = Y(*buf);
                _vec.erase(
                    _vec.begin(),
                    _vec.begin() + std::min(sizeof(X), _vec.size())
                );
                return *this;
            }
            inline auto popFront(std::size_t n) -> Builder & {
                _vec.erase(
                    _vec.begin(),
                    _vec.begin() + std::min(n, _vec.size())
                );
                return *this;
            }
            static auto fromString(std::string const &s) -> Builder;
            auto toString(void) const -> std::string;
            auto toBytes(void) const -> std::vector<jgo::u8>;
            auto reset(enums::FromAny op) -> void;
            auto reset(jgo::u8 op) -> void;
        private:
            std::vector<jgo::u8> _vec;
            union {
                float f32;
                u8 int8[8];
                u16 int16[4];
                u32 int32[2];
                u64 int64;
            } _caster;
    };
}
