/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** AutoShootSystem
*/

#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"
#include "jepmaker/components/AutoShoot.hpp"
#include "jepmaker/components/Position.hpp"
#include "jepmaker/components/Game.hpp"
#include "jepmaker/components/Type.hpp"

/**
 * @brief Check Time system
 * 
 * @param time 
 * @param _time 
 * @param reset 
 * @return true 
 * @return false 
 */
static bool checkTime(float time, float _time, float reset)
{
    if (time - _time < reset)
        return false;
    return true;
}

/**
 * @brief Create a Shoot object
 * 
 * @param game Game
 * @param time current time
 * @param entity th entity player
 * @param shoot shoot component
 */
static void CreateShoot(jgo::Game &game, float time, std::size_t entity, AutoShoot &shoot)
{
    auto &type = game.ecs.getComp<Type>();
    auto &pos = game.ecs.getComp<Position2D>();

    if (type[entity].has_value() && type[entity].value().getType() == MODULE_ARM && pos[entity].has_value()) {
        Game::CreateShipShoot(game, Position2D(pos[entity].value().x + 10, pos[entity].value().y));   
        shoot.getTime() = time;
    }
}

/**
 * @brief The System for the AutoShootSystem
 * 
 * 
 */
exported(void) jepgoSystem(jgo::Game &game, float time)
{
    auto &autoshoot = game.ecs.getComp<AutoShoot>();

    for (std::size_t i = 0; i < autoshoot.size(); i++) {
        if (autoshoot[i].has_value() && checkTime(game.getTime(), autoshoot[i].value().getTime(), autoshoot[i].value().getReset())) {
            CreateShoot(game, game.getTime(), i, autoshoot[i].value());
        }
    }
}