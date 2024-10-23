/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Health
*/

#pragma once

#include <algorithm>

class Health {
    public:
        inline Health(int n = 100): _health(n) {
            return;
        }
        constexpr inline void takeDamage(int n) {
            _health = std::max(_health - n, 0);
        }
        constexpr inline auto isDead() const noexcept -> bool {
            return _health == 0;
        }
        constexpr inline auto get() const noexcept -> int {
            return _health;
        }
    private:
        int _health = 100;
};
