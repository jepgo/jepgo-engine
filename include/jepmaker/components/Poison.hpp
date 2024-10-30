/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Poison
*/

#pragma once

#include "jepmod/Clock++.hpp"
#include <algorithm>

class Poison {
    public:
        inline Poison(int dmg = 10, float freq = 1.0f)
        : _damage(dmg), _frequency(freq),
            _stamp(jmod::ClockPP().get()) {
            return;
        }
        inline auto getDamage() const noexcept -> int {
            return _damage;
        }
        inline auto update(float now) noexcept -> bool {
            if ((now - _stamp) < _frequency)
                return false;
            _stamp = now;
            return true;
        }
    private:
        int _damage;
        float _frequency;
        double _stamp;
};
