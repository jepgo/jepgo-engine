/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** MoveToPlayerTimeSystem
*/

#include "MoveToPlayerTimeSystem.hpp"

static bool checkTime(float time, MoveToPlayerTime &player)
{
    if (time - player._time < player._reset)
        return false;
    return true;
}

void MoveToPlayerTimeSystem::system(Register &r, float time)
{
    auto &t = r.getComp<MoveToPlayerTime>();

    for (std::size_t i = 0; i < t.size(); i++) {
        if (t[i].has_value() && checkTime(time, t[i].value())) {
            r.removeComponent<MoveToPlayer>(i);
            r.removeComponent<MoveToPlayerTime>(i);
        }
    }
}