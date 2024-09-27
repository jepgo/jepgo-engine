/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** GameSystem
*/

#pragma once
#include "Register.hpp"
#include "Game.hpp"
#include "Components.hpp"

class GameSystem {
    public:
        static void system(Register &r, Game &player);
        GameSystem();
        ~GameSystem();

    private:
        float _time;
};
