/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MoveToPlayerTimeSystem
*/

#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"
#include "jepmaker/components/MoveToPlayerTime.hpp"
#include "jepmaker/components/MoveToPlayer.hpp"

static bool checkTime(float time, MoveToPlayerTime &player)
{
    if (time - player._time < player._reset)
        return false;
    return true;
}

exported(void) jepgoSystem(jgo::Game &game, float &time)
{
    auto &t = game.ecs.getComp<MoveToPlayerTime>();

    for (std::size_t i = 0; i < t.size(); i++) {
        if (t[i].has_value() && checkTime(game.getTime(), t[i].value())) {
            game.ecs.removeComponent<MoveToPlayer>(i);
            game.ecs.removeComponent<MoveToPlayerTime>(i);
        }
    }
}
