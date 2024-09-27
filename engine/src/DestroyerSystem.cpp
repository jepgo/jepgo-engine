/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** DestroyerSystem
*/

#include "DestroyerSystem.hpp"

static bool checkPosition(Positions &pos)
{
    if (pos.x < 0)
        return true;
    if (pos.y < 0)
        return true;
    return false;
}

void DestoyersSystem::system(Register &r)
{
    auto &pos = r.getComp<Positions>();

    for (std::size_t i = 0; i < pos.size(); i++) {
        if (pos[i].has_value() && checkPosition(pos[i].value())) {
            r.removeComponent<Hitable>(i);
            r.removeComponent<Drawable>(i);
            r.removeComponent<Life>(i);
            r.removeComponent<Colision>(i);
        }
    }
}
