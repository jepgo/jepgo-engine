/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Builder
*/

#include <string>
#include <cstdint>
#include <variant>
#include "OpCodes.hpp"
#include "Builder.hpp"

jgo::Builder::Builder(enums::FromAny op)
{
    this->reset(op);
}

auto jgo::Builder::reset(enums::FromAny op) -> void
{
    enums::FromClient *clientOpPtr = std::get_if<enums::FromClient>(&op);
    std::uint8_t opNum = (clientOpPtr == nullptr) ?
        std::uint8_t{ std::get<enums::FromServer>(op) } :
        std::uint8_t{ *clientOpPtr };

    _vec.push_back(opNum);
}

auto jgo::Builder::toString(void) const -> std::string
{
    return std::string(_vec.begin(), _vec.end());
}
