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

static void Stage2(Register &r, SparseArray<SoundLoop> &sound, std::vector<Sound> &sounds)
{
    auto &type = r.getComp<Type>();

    for (std::size_t i = 0; i < type.size(); i++) {
        if (type[i].has_value() && type[i].value().getType() == MINIBOSS)
            return;
    }
    Game::CreateMiniBoss1(r, Positions(1360, 300));
    for (std::size_t i = 0; i < sound.size(); i++) {
        if (sound[i].has_value()) {
            sound[i].value().Stop(sounds[sound[i].value().getInd()]);
            sound[i].value().ChangeSong(0);
        }
    }
        // sound.stop();
        // sound.setBuffer(buff[0]);
        // sound.setLoop(true);
        // sound.play();
}

static void Stage1(Register &r)
{
    Game::CreateAsteroid(r);
}

void TestGame::Stages(Register &r, float time, std::size_t entity, std::vector<Sound> &sounds)
{
    auto &km = r.getComp<DistanceKm>();
    auto &sound = r.getComp<SoundLoop>();

    if (time - _time <= _reset)
        return;
    if (km[entity].value()._dist >= 50) {
        Stage2(r, sound, sounds);
    } 
    else
        Stage1(r);
    r.removeComponent<LvLUp>(entity);
    _time = time;
}
