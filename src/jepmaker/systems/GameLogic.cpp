/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** GameLogic
*/

#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"
#include "jepmaker/components/Game.hpp"
#include "jepmaker/components/Type.hpp"
#include "jepmaker/components/LvlUp.hpp"
#include "jepmaker/components/Position.hpp"
#include "jepmaker/components/SoundLoop.hpp"
#include "jepmaker/components/DistanceKm.hpp"

static void TableScore(jgo::Game &game)
{
    auto &pts = game.ecs.getComp<Points>();
    size_t entity = -1;

    for (std::size_t i = 0; i < pts.size(); i++)
        if (pts[i].has_value())
            entity = i;
    if (entity == -1)
        return;
    Game::CreateMessageTime(game, Position2D(200, 200), std::string("Score :"), game.getTime(), 5);
    Game::CreateMessageTime(game, Position2D(200, 300), std::string(std::to_string(pts[entity].value()._point)), game.getTime(), 5);
    return;
}

static void Stage1(jgo::Game &game, float &time)
{
    float reset = 2;

    if (game.getTime() - time < reset)
        return;
    Game::CreateEasyEnemies(game);
    time = game.getTime();
}

static void Stage2(jgo::Game &game, float &time)
{
    float reset = 2;

    if (game.getTime() - time < reset)
        return;
    Game::CreateEasyEnemies(game);
    Game::CreateSpaceShip(game, time);
    time = game.getTime();
}

static void Stage3(jgo::Game &game, float &time)
{
    float reset = 3;

    if (game.getTime() - time < reset)
        return;
    Game::CreateSpaceShip(game, time);
    Game::CreateObstacle(game);
    Game::CreateEasyEnemies(game);
    time = game.getTime();
}

static void Stage4(jgo::Game &game, float &time)
{
    auto &type = game.ecs.getComp<Type>();
    auto &life = game.ecs.getComp<Life>();

    for (std::size_t i = 0; i < type.size(); i++) {
        if ((type[i].has_value() && type[i].value().getType() == MINIBOSS) && (life[i].has_value() && life[i].value()._life <= 0))
            return;
        if (type[i].has_value() && type[i].value().getType() == MINIBOSS)
            return;
    }
    Game::CreateMiniBoss1(game, Position2D(1360, 300));
    return;
}

exported(void) jepgoSystem(jgo::Game &game, float &time)
{
    int entity = -1;
    auto &km = game.ecs.getComp<DistanceKm>();
    auto &sound = game.ecs.getComp<SoundLoop>();

    for (std::size_t i = 0; i < km.size(); i++)
        if (km[i].has_value())
            entity = i;
    if (entity == -1)
        return;
    if (km[entity].value()._dist >= 0 && km[entity].value()._dist <= 100)
        Stage1(game, time);
    else if (km[entity].value()._dist >= 100 && km[entity].value()._dist <= 350)
        Stage2(game, time);
    else if (km[entity].value()._dist >= 350 && km[entity].value()._dist <= 700) {
        Stage3(game, time);
    }
    else if (km[entity].value()._dist >= 700)
        Stage4(game, time);
    game.ecs.removeComponent<LvLUp>(entity);
    time = game.getTime();
}