/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Builder
*/

#include <string>
#include <cstdint>
#include <variant>
#include <optional>

#include "OpCodes.hpp"
#include "Builder.hpp"

jgo::Builder::Builder(enums::FromAny op)
{
    this->reset(op);
}

jgo::Builder::Builder(jgo::u8 op)
{
    this->reset(op);
}

auto jgo::Builder::reset(enums::FromAny op) -> void
{
    enums::FromClient *clientOpPtr = std::get_if<enums::FromClient>(&op);
    jgo::u8 opNum = (clientOpPtr == nullptr) ?
        static_cast<jgo::u8>(std::get<enums::FromServer>(op)):
        static_cast<jgo::u8>(*clientOpPtr);

    this->reset(opNum);
}

auto jgo::Builder::reset(jgo::u8 n) -> void
{
    _vec = {n};
}

auto jgo::Builder::toString(void) const -> std::string
{
    return std::string(_vec.begin(), _vec.end());
}

auto jgo::Builder::toBytes(void) const -> std::vector<jgo::u8>
{
    return _vec;
}

auto jgo::Builder::fromString(std::string const &s) -> jgo::Builder
{
    if (s.empty())
        throw std::runtime_error("invalid use of empty string.");
    
    Builder foo = Builder(static_cast<jgo::u8>(s[0]));
    if (s.length() == 1)
        return foo;
    foo._vec = std::vector<jgo::u8>(s.begin() + 1, s.end());
    return foo;
}
