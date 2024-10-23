/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Poison
*/

#pragma once

#include <algorithm>

class Poison {
    public:
        inline Poison(int dmg = 10): _damage(dmg) {
            return;
        }
        inline auto getDamage() const noexcept -> int {
            return _damage;
        }
    private:
        int _damage = 10;
};
