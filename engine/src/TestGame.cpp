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

static void Stage2(Register &r)
{
    auto &type = r.getComp<Type>();

    for (std::size_t i = 0; i < type.size(); i++) {
        if (type[i].has_value() && type[i].value().getType() == MINIBOSS)
            return;
    }
    Game::CreateMiniBoss1(r, Positions(1360, 300));
        // sound.stop();
        // sound.setBuffer(buff[0]);
        // sound.setLoop(true);
        // sound.play();
}

static void Stage1(Register &r)
{
    Game::CreateAsteroid(r);
}

void TestGame::Stages(Register &r, float time, std::size_t entity)
{
    auto &km = r.getComp<DistanceKm>();
    // auto &lvl = r.getComp<Lvl>();
    // auto &lvlup = r.getComp<LvLUp>();

    if (time - _time <= _reset)
        return;
    if (km[entity].value()._dist >= 700) {
        Stage2(r);
    } 
    else
        Stage1(r);
    r.removeComponent<LvLUp>(entity);
    _time = time;
}
