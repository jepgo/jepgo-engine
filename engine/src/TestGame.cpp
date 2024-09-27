/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** TestGame
*/

#include "TestGame.hpp"
#include "Game.hpp"
#include <cstdlib>
#include <ctime> 

TestGame::TestGame(float reset) : _reset(reset)
{
    _time = 0;
}

TestGame::~TestGame()
{
}

void TestGame::generateRandomsEntitys(Register &r, sf::Time &time, Game &player)
{
    if (time.asSeconds() - _time <= _reset)
        return;
    if (player.getLvl() <= 2)
        Game::CreateAsteroid(r);
    else
        Game::CreateMiniBoss1(r, Positions(660, 200));
    _time = time.asSeconds();
}
