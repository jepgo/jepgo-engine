/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** GameSystem
*/

#pragma once
#include "Register.hpp"
#include <SFML/Audio.hpp>
#include "Game.hpp"
#include "Components.hpp"

class GameSystem {
    public:
        void system(Register &r, float time, int entity);
        GameSystem(float reset);
        ~GameSystem();

    private:
        float _time;
        float _reset;
};
