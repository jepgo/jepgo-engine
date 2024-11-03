/*
** EPITECH PROJECT, 2024
** R-Type [WSL : Fedora]
** File description:
** Level1
*/

// #include "jepmaker/levels/ILevels.hpp"
#include "jepmaker/levels/Level1.hpp"
#include "jepmod/exported.hpp"
#include "jepmaker/components/Game.hpp"
#include "jepmaker/components/Type.hpp"
#include "jepmaker/components/LvlUp.hpp"
#include "jepmaker/components/Position.hpp"
#include "jepmaker/components/SoundLoop.hpp"
#include "jepmaker/components/DistanceKm.hpp"
#include <memory>

static void Stage1(jgo::Game &game)
{
    Game::CreateEasyEnemies(game);
}

static void Stage2(jgo::Game &game, float time)
{
    Game::CreateSpaceShip(game, time);
}

static void Stage3(jgo::Game &game, float time)
{
    Game::CreateSpaceShip(game, time);
    Game::CreateObstacle(game);
    Game::CreateEasyEnemies(game);
}

static void Stage4(jgo::Game &game)
{
    auto &type = game.ecs.getComp<Type>();

    for (std::size_t i = 0; i < type.size(); i++) {
        if (type[i].has_value() && type[i].value().getType() == MINIBOSS)
            return;
    }
    Game::CreateMiniBoss1(game, Positions(1360, 300));
    return;
}

void Level1::launch(jgo::Game &game, float &time)
{
    std::size_t entity = 0;
    float reset = 3.0;
    auto &km = game.ecs.getComp<DistanceKm>();
    auto &sound = game.ecs.getComp<SoundLoop>();

    if (game.getTime() - time < reset) {
        std::cout << "Return !" << std::endl;
        std::cout << "Time: " << game.getTime() << std::endl;
        std::cout << "Time - time: " << game.getTime() - time << std::endl;
        return;
    }
    for (std::size_t i = 0; i < km.size(); i++)
        if (km[i].has_value())
            entity = i;
    if (km[entity].value()._dist >= 0 && km[entity].value()._dist <= 100)
        Stage1(game);
    else if (km[entity].value()._dist >= 100 && km[entity].value()._dist <= 350)
        Stage2(game, game.getTime());
    else if (km[entity].value()._dist >= 350 && km[entity].value()._dist <= 700) {
        reset = 1.5;
        Stage3(game, game.getTime());
    }
    else if (km[entity].value()._dist >= 700)
        Stage4(game);
    game.ecs.removeComponent<LvLUp>(entity);
    time = game.getTime();
}

// exported(std::unique_ptr<jgo::ILevels>) createLevel(void) {
//     return std::make_unique<Level1>();
// }
