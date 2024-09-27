/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** GameSystem
*/

#include "GameSystem.hpp"

GameSystem::GameSystem(float reset) : _reset(reset)
{
    _time = 0;
}

GameSystem::~GameSystem()
{
}

void GameSystem::system(Register &r, Game &player, sf::Time &time) {
    std::size_t lvlup = 0;

    if (time.asSeconds() - _time < _reset)
        return;
    else
        _time = time.asSeconds();
    player.getKm() += 1;
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