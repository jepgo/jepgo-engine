/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Enemy
*/

#pragma once
#include <string>

class Enemy {
    public:
        /**
         * @brief Construct a new Enemy object
         * 
         * @param point The number of point this enemy death give to the player
         * @param exp The number of exp point the enemy death give to the player
         */
        Enemy(std::size_t point, std::size_t exp) {};
        ~Enemy() {};
    std::size_t _point;
    std::size_t _exp;
};