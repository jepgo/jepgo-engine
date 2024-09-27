/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** GameSystem
*/

#include "GameSystem.hpp"

GameSystem::GameSystem()
{
    _time = 0;
}

GameSystem::~GameSystem()
{
}

void GameSystem::system(Register &r, Game &player) {
    std::size_t lvlup = 0;

    while (player.getExp() >= 100) {
        lvlup++;
        player.getExp() -= 100;
        player.getLvl() += 1;
    }
    if (player.getLvl() == 2 && lvlup != 0)
        Game::CreateShootModule(r, Positions(1000, 300));
    if (player.getLvl() == 3 && lvlup != 0)
        Game::CreateArmorModule(r, Positions(1000, 500));
}