/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Poison
*/

#include "jepmod/exported.hpp"
#include "jepengine/Game.hpp"
#include "jepmaker/components/Poison.hpp"
#include "jepmaker/components/Health.hpp"

exported(void) jepgoSystem(jgo::Game &game)
{
    auto &poisonComps = game.ecs.getComp<Poison>();
    auto &healthComps = game.ecs.getComp<Health>();

    for (std::size_t n = 0; n < game.ecs.entityNbr(); ++n) {
        if (poisonComps[n] and healthComps[n])
            healthComps[n]->takeDamage(poisonComps[n]->getDamage());
    }
}
