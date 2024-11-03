/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** DmgSystem
*/

#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"
#include "jepmaker/components/Dmg.hpp"
#include "jepmaker/components/Life.hpp"
#include "jepmaker/components/Invincible.hpp"
#include "jepmaker/components/InvincibleTime.hpp"
#include "jepmaker/components/Death.hpp"

/**
 * @brief The DmgSystem
 * 
 */
exported(void) jepgoSystem(jgo::Game &game, float &t)
{
    auto &dmg = game.ecs.getComp<Dmg>();
    auto &life = game.ecs.getComp<Life>();
    auto &inv = game.ecs.getComp<Invincible>();

    for (std::size_t i = 0; i < dmg.size(); i++) {
        if (dmg[i].has_value() && inv[i].has_value()) {
            game.ecs.removeComponent<Dmg>(i);
        }
        if (dmg[i].has_value() && life[i].has_value()) {
            life[i].value()._life -= dmg[i].value()._dmg;
            game.ecs.emplaceComp<Invincible>(i, Invincible());
            game.ecs.emplaceComp<InvincibleTime>(i, InvincibleTime(game.getTime(), 0.1));
            game.ecs.removeComponent<Dmg>(i);
            if (life[i].value()._life <= 0) {
                game.ecs.emplaceComp(i, Death());
            }
        }
    }
}