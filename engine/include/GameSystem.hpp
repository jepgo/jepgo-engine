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
        void system(Register &r, Game &player, sf::Time &time, int entity, std::vector<sf::Sound> &sounds);
        GameSystem(float reset);
        ~GameSystem();

    private:
        float _time;
        float _reset;
};
