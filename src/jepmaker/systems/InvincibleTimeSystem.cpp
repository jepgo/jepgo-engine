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

/**
 * @brief The CheckTime
 * 
 * @param inv The InvincibleTime Component
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
 * @brief The InvincibleTimeSystem
 * 
 * The purpose of this system is to make an entity invincible for a limited period and only during that time.
 * Note that the entity must first be given the Invincible component.
 * 
 */
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