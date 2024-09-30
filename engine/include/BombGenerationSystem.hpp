/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** BombGenerationSystem
*/

#pragma once
#include "Register.hpp"
#include "Game.hpp"

class BombGenerationSystem {
    public:
        static void system(Register &r, sf::Time &time);
};
