/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** ExplosionSystem
*/

#include "ExplosionSystem.hpp"

void ExplosionSystem::system(Register &r)
{
    auto &death = r.getComp<Death>();
    auto &explosion = r.getComp<Explosion>();

    for (std::size_t i = 0; i < death.size(); i++) {
        if (death[i].has_value() && explosion[i].has_value()) {
            explosion[i].value().explose(r, i);
        }
    }
}