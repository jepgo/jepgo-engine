/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** GameSystem
*/

#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"
#include "jepmaker/components/Exp.hpp"
#include "jepmaker/components/Lvl.hpp"
#include "jepmaker/components/LvlUp.hpp"
#include "jepmaker/components/DistanceKm.hpp"
#include "jepmaker/components/Position.hpp"
#include "jepmaker/components/Game.hpp"

exported(void) jepgoSystem(jgo::Game &game, float &time)
{
    float _reset = 0.1;
    int entity = -1;
    auto &exp = game.ecs.getComp<Exp>();
    auto &lvl = game.ecs.getComp<Lvl>();
    auto &dist = game.ecs.getComp<DistanceKm>();

    std::size_t lvlup = 0;

    for (std::size_t i = 0; i < dist.size(); i++)
        if (dist[i].has_value())
            entity = i;
    if (entity == -1)
        return;
    if (game.getTime() - time < _reset)
        return;
    else
        time = game.getTime();
    dist[entity].value()._dist += 1;
    while (exp[entity].value()._exp >= 100)
    {
        lvlup++;
        exp[entity].value()._exp -= 100;
        lvl[entity].value()._lvl += 1;
    }
    if (lvlup != 0)
        game.ecs.emplaceComp(entity, LvLUp(lvl[entity].value()._lvl));
    if (lvl[entity].value()._lvl == 2 && lvlup != 0)
        Game::CreateShootModule(game, Position2D(-10, 300));
    if (lvl[entity].value()._lvl == 3 && lvlup != 0)
    {
        Game::CreateArmorModule(game, Position2D(-10, 300), time);
    }
}