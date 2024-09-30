/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** MoveToPlayerTimeSystem
*/

#include "MoveToPlayerTimeSystem.hpp"

static bool checkTime(sf::Time &time, MoveToPlayerTime &player)
{
    if (time.asSeconds() - player._time < player._reset)
        return false;
    return true;
}

void MoveToPlayerTimeSystem::system(Register &r, sf::Time &time)
{
    auto &t = r.getComp<MoveToPlayerTime>();

    for (std::size_t i = 0; i < t.size(); i++) {
        if (t[i].has_value() && checkTime(time, t[i].value())) {
            r.removeComponent<MoveToPlayer>(i);
            r.removeComponent<MoveToPlayerTime>(i);
        }
    }
}