/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** BombGenerationTime
*/

#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"
#include "jepmaker/components/BombGeneration.hpp"
#include "jepmaker/components/BombGenerationTime.hpp"

/**
 * @brief CheckTimeSystem
 * 
 * @param bomb The Bomb
 * @param time current time
 * @return true 
 * @return false 
 */
static bool checkTime(BombGenerationTime &bomb, float time)
{
    if (time - bomb.getTime() < bomb.getDuring())
        return false;
    return true;
}

/**
 * @brief The system of the BombGenerationSystem
 * 
 */
exported(void) jepgoSystem(jgo::Game &game, float time)
{
    auto &bomb = game.ecs.getComp<BombGenerationTime>();

    for (std::size_t i = 0; i < bomb.size(); i++) {
        if (bomb[i].has_value() && checkTime(bomb[i].value(), game.getTime())) {
            game.ecs.removeComponent<BombGeneration>(i);
            game.ecs.removeComponent<BombGenerationTime>(i);
        }
    }
}