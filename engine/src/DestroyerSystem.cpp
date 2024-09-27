/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** DestroyerSystem
*/

#include "DestroyerSystem.hpp"

static bool checkPosition(Positions &pos, int height, int width)
{
    if (pos.x < -width)
        return true;
    if (pos.y < -height)
        return true;
    return false;
}

void DestoyersSystem::system(Register &r, int height, int width)
{
    auto &pos = r.getComp<Positions>();

    for (std::size_t i = 0; i < pos.size(); i++) {
        if (pos[i].has_value() && checkPosition(pos[i].value(), height, width)) {
            r.removeComponent<Hitable>(i);
            r.removeComponent<Drawable>(i);
            r.removeComponent<Life>(i);
            r.removeComponent<Colision>(i);
        }
    }
}
