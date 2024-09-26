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

void TestGame::generateRandomsEntitys(Register &r, sf::Time &time)
{
    if (time.asSeconds() - _time <= _reset)
        return;
    Game::CreateAsteroid(r);
    _time = time.asSeconds();
}
