/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Velocity
*/

#pragma once
#include <array>
#include "jepmaker/components/Position.hpp"

class Velocity {
public:
    Velocity(std::array<double, 2> const &s) : _speed(s) {}
    ~Velocity() = default;
    inline auto setVel(std::array<float, 2> const &v) -> void {
        _vel.x = v[0] * _speed[0];
        _vel.y = v[1] * _speed[1];
    }

    inline auto getVel() const noexcept -> Positions const &
    {
        return _vel;
    }
private:
    std::array<double, 2> _speed;
    Positions _vel{0, 0};
};