/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** FreeSystem
*/

#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"
#include "jepmaker/components/Life.hpp"
#include "jepmaker/components/SpriteAnimation.hpp"
#include "jepmaker/components/Drawable2D.hpp"
#include "jepmaker/components/Controllable.hpp"
#include "jepmaker/components/Type.hpp"
#include "jepmaker/components/Free.hpp"
#include "jepmaker/components/ToFree.hpp"

/**
 * @brief The remove Function
 * 
 * @param game 
 * @param entity 
 */
static void removeAll(jgo::Game &game, std::size_t entity)
{
    game.ecs.removeEntity(entity);
    game.ecs.emplaceComp(entity, Free());
}

/**
 * @brief The FreeSystem
 * 
 */
exported(void) jepgoSystem(jgo::Game &game, float &time)
{
    std::size_t nbr = 0;
    auto &free = game.ecs.getComp<ToFree>();

    for (std::size_t i = 0; i < free.size(); i++) {
        if (free[i].has_value())
            removeAll(game, i);
    }
    // for (std::size_t i = 0; i < free.size(); i++)
    //     if (free[i].has_value())
    //         nbr++;
    // std::cout << "entity free = " << nbr << std::endl;
}