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
    auto &col = r.getComp<Colision>();
    auto &control = r.getComp<Controllable>();

    if (explosion[me].has_value() == false)
        return false;
    if (explosion[me].value().type == BOMB && explosion[him].has_value() && explosion[him].value().type != BOMB)
        explosion[me].value().explose(r, me, him);
    if (explosion[me].value().type == SHIPSHOOT && control[him].has_value() == false)
        explosion[me].value().explose(r, me, him);
    if (explosion[me].value().type == BOMB && control[him].has_value())
        explosion[me].value().explose(r, me, him);
    return true;
}

void ExplosionSystem::system(Register &r)
{
    auto &hit = r.getComp<Hit>();

    for (std::size_t i = 0; i < hit.size(); i++) {
        if (hit[i].has_value()) {
            (check(r, hit[i].value().GetEntity(), i));
            r.removeComponent<Hit>(i);
        }
    }
}