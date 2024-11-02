/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** InvinsibleSystem
*/

#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"
#include "jepmaker/components/Invincible.hpp"
#include "jepmaker/components/InvincibleTime.hpp"

static bool check_time(InvincibleTime &inv, float time)
{
    if (time - inv._time < inv._reset)
        return false;
    return true;
};

exported(void) jepgoSystem(jgo::Game &game, float &time)
{
    auto &inv = game.ecs.getComp<InvincibleTime>();

    for (std::size_t i = 0; i < inv.size(); i++) {
        if (inv[i].has_value() && check_time(inv[i].value(), game.getTime())) {
            game.ecs.removeComponent<Invincible>(i);
            game.ecs.removeComponent<InvincibleTime>(i);
        }
    }
};