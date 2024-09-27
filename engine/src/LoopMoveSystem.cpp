/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** LoopMoveSystem
*/

#include "LoopMoveSystem.hpp"

static bool checkPosition(Positions &pos, int height, int width)
{
    if (pos.x <= (-1 * width) + 10 || pos.y <= (-1 * height) + 10)
        return true;
    return false;
}

void LoopMoveSystem::system(Register &r, int height, int width)
{
    auto &loopmove = r.getComp<LoopMove>();
    auto &pos = r.getComp<Positions>();

    for (std::size_t i = 0; i < loopmove.size(); i++) {
        if (loopmove[i].has_value() && pos[i].has_value() && checkPosition(pos[i].value(), height, width))
            pos[i].value() = loopmove[i].value()._pos;
    }
}