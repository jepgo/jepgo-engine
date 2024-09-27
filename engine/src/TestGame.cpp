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

void TestGame::generateRandomsEntitys(Register &r, sf::Time &time, std::size_t entity, std::vector<sf::Sound> &sounds)
{
    auto &lvl = r.getComp<LvLUp>();
    if (time.asSeconds() - _time <= _reset)
        return;
    if (lvl[entity].has_value() && lvl[entity].value()._lvl == 2) {
        sounds[0].stop();
        sounds[1].setLoop(true);
        sounds[1].play();
    }
    if (lvl[entity].has_value() && lvl[entity].value()._lvl == 3) {
        Game::CreateMiniBoss1(r, Positions(660, 200));
    }
    Game::CreateAsteroid(r);
    r.removeComponent<LvLUp>(entity);
    _time = time.asSeconds();
}
