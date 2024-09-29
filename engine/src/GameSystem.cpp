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

void GameSystem::system(Register &r, sf::Time &time, int entity, sf::Sound &sound) {
    auto &exp = r.getComp<Exp>();
    auto &lvl = r.getComp<Lvl>();
    auto &dist = r.getComp<DistanceKm>();

    std::size_t lvlup = 0;

    if (time.asSeconds() - _time < _reset)
        return;
    else
        _time = time.asSeconds();
    dist[entity].value()._dist += 1;
    while (exp[entity].value()._exp >= 100) {
        lvlup++;
        exp[entity].value()._exp -= 100;
        lvl[entity].value()._lvl += 1;
    }
    if (lvlup != 0)
        r.emplace_comp(entity, LvLUp(lvl[entity].value()._lvl));
    if (lvl[entity].value()._lvl == 2 && lvlup != 0)
        Game::CreateShootModule(r, Positions(1000, 300));
    if (lvl[entity].value()._lvl == 3 && lvlup != 0) {
        Game::CreateArmorModule(r, Positions(1000, 300));
    }
}