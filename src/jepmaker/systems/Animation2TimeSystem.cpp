/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Animation2TimeSystem
*/

#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"
#include "jepmaker/components/Animation2Time.hpp"
#include "jepmaker/components/Invincible.hpp"
#include "jepmaker/components/InvincibleTime.hpp"
#include "jepmaker/components/BombGeneration.hpp"
#include "jepmaker/components/BombGenerationTime.hpp"

/**
 * @brief Checkrule for Animation2TimeSystem
 * 
 * @param anim Animation2Time component
 * @param inv optional invincibletime components
 * @param time the current time
 * @param i 
 * @param game The Game
 */
static void checkRules(std::optional<Animation2Time> &anim, std::optional<InvincibleTime> &inv, float time, std::size_t i, jgo::Game &game)
{
    if ((anim.has_value() == false) || inv.has_value()) {
            return;
    }
    if (time - anim.value()._lastTime < anim.value()._reset)
        return;
    if (anim.value().getstatus() == true) {
        game.ecs.emplaceComp(i, std::move(anim.value().getAnim2()));
        game.ecs.emplaceComp(i, Invincible());
        game.ecs.emplaceComp(i, InvincibleTime(time, anim.value().getAnimation1Time()));
        anim.value().getstatus() = false;
        anim.value()._lastTime = time;
        anim.value()._reset = anim.value().getAnimationTime();
    } else {
        game.ecs.createEntity();
        game.ecs.emplaceComp(game.ecs.currentEntity, BombGeneration(time, 0.4, Position2D(800, 300), 8));
        game.ecs.emplaceComp(game.ecs.currentEntity, BombGenerationTime(time, 1.5));
        game.ecs.createEntity();
        game.ecs.emplaceComp(game.ecs.currentEntity, BombGeneration(time, 0.4, Position2D(800, 100), 8));
        game.ecs.emplaceComp(game.ecs.currentEntity, BombGenerationTime(time, 1.5));
        game.ecs.createEntity();
        game.ecs.emplaceComp(game.ecs.currentEntity, BombGeneration(time, 0.4, Position2D(10, 200), 6));
        game.ecs.emplaceComp(game.ecs.currentEntity, BombGenerationTime(time, 1.5));
        game.ecs.emplaceComp(i, std::move(anim.value().getAnim1()));
        game.ecs.emplaceComp(i, Invincible());
        game.ecs.emplaceComp(i, InvincibleTime(time, anim.value().getAnimation2Time() + anim.value().getAnimationTime()));
        anim.value().getstatus() = true;
        anim.value()._lastTime = 0;
        anim.value()._reset = 0;
    }
}

/**
 * @brief The Animation2Time system, used for the mini boss
 * 
 */
exported(void) jepgoSystem(jgo::Game &game, float time)
{
    auto &inv = game.ecs.getComp<InvincibleTime>();
    auto &animation = game.ecs.getComp<Animation2Time>();

    for (std::size_t i = 0; i < animation.size(); i++) {
        checkRules(animation[i], inv[i], game.getTime(), i, game);
    }
}