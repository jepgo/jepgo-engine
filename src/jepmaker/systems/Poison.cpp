/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Poison
*/

#include <iostream>
#include "jepmod/exported.hpp"
#include "jepengine/Game.hpp"
#include "jepmaker/components/Poison.hpp"
#include "jepmaker/components/Health.hpp"

exported(void) jepgoSystem(jgo::Game &game, float &t)
{
    auto &poisonComps = game.ecs.getComp<Poison>();
    auto &healthComps = game.ecs.getComp<Health>();
    float now = game.getTime();

    for (std::size_t n = 0; n < game.ecs.entityNbr(); ++n) {
        if (not poisonComps[n] or not healthComps[n])
            continue;
        if (not poisonComps[n]->update(now))
            continue;
        healthComps[n]->takeDamage(poisonComps[n]->getDamage());
    }
}
