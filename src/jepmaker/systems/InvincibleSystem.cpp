/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Invincible
*/

#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"
#include "jepmaker/components/Invincible.hpp"
#include "jepmaker/components/InvincibleTime.hpp"

/**
 * @brief The CheckTime
 * 
 * @param inv The Invincible Component
 * @param time The current time
 * @return true 
 * @return false 
 */
static bool check_time(InvincibleTime &inv, float time)
{
    if (time - inv._time < inv._reset)
        return false;
    return true;
};

/**
 * @brief The InvincibleSystem
 * 
 * The purpose of this system is to make my entity invincible.
 * 
 */
exported(void) jepgoSystem(jgo::Game &game, float time)
{
    auto &inv = game.ecs.getComp<InvincibleTime>();

    for (std::size_t i = 0; i < inv.size(); i++) {
        if (inv[i].has_value() && check_time(inv[i].value(), time)) {
            game.ecs.removeComponent<Invincible>(i);
            game.ecs.removeComponent<InvincibleTime>(i);
        }
    }
};