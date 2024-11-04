/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** PersoSystem
*/

#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"
#include "components/PersoCompo.hpp"

exported(void) jepgoSystem(jgo::Game &game, float &t)
{
    auto &pc = game.ecs.getComp<PersoCompo>();

    for (std::size_t i = 0; i < pc.size(); i++) {
        if (pc[i].has_value()) {
            // Implement the behavior of the system
        }
    }
}
