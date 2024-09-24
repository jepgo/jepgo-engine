/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** ExplosionSystem
*/

#include "ExplosionSystem.hpp"

static bool check(Register &r, std::size_t him, std::size_t me)
{
    auto &explosion = r.getComp<Explosion>();

    if (explosion[him].has_value() && explosion[me].has_value()) {
        explosion[me].value().explose(r, me);
        return true;
    }
    return false;
}

void ExplosionSystem::system(Register &r)
{
    auto &hit = r.getComp<Hit>();

    for (std::size_t i = 0; i < hit.size(); i++) {
        if (hit[i].has_value()) {
            check(r, hit[i].value().GetEntity(), i);
            r.removeComponent<Hit>(i);
        }
    }
}