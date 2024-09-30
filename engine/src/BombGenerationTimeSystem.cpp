/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** BombGenerationTime
*/

#include "BombGenerationTimeSystem.hpp"

static bool checkTime(BombGenerationTime &bomb, float time)
{
    if (time - bomb.getTime() < bomb.getDuring())
        return false;
    return true;
}

void BombGenerationTimeSystem::system(Register &r, sf::Time &time)
{
    auto &bomb = r.getComp<BombGenerationTime>();

    for (std::size_t i = 0; i < bomb.size(); i++) {
        if (bomb[i].has_value() && checkTime(bomb[i].value(), time.asSeconds())) {
            r.removeComponent<BombGeneration>(i);
            r.removeComponent<BombGenerationTime>(i);
        }
    }
}