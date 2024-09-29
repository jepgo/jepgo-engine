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

static void Stage2(Register &r, sf::Sound &sound, std::vector<sf::SoundBuffer> &buff)
{
    auto &type = r.getComp<Type>();

    for (std::size_t i = 0; i < type.size(); i++) {
        if (type[i].has_value() && type[i].value().getType() == MINIBOSS)
            return;
    }
    Game::CreateMiniBoss1(r, Positions(660, 200));
        sound.stop();
        sound.setBuffer(buff[0]);
        sound.setLoop(true);
        sound.play();
}

static void Stage1(Register &r)
{
    Game::CreateAsteroid(r);
}

void TestGame::Stages(Register &r, sf::Time &time, std::size_t entity, sf::Sound &sound, std::vector<sf::SoundBuffer> &buff)
{
    auto &km = r.getComp<DistanceKm>();
    // auto &lvl = r.getComp<Lvl>();
    // auto &lvlup = r.getComp<LvLUp>();

    if (time.asSeconds() - _time <= _reset)
        return;
    if (km[entity].value()._dist >= 10) {
        Stage2(r, sound, buff);
    } 
    else
        Stage1(r);
    r.removeComponent<LvLUp>(entity);
    _time = time.asSeconds();
}
