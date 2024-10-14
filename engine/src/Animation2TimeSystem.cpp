/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Animation2TimeSystem
*/

#include "Animation2TimeSystem.hpp"

static void checkRules(std::optional<Animation2Time> &anim, std::optional<InvincibleTime> &inv, float time, std::size_t i, Register &r)
{
    if ((anim.has_value() == false) || inv.has_value()) {
        //std::cout << "yep yes" << std::endl;
            return;
    }
    if (time - anim.value()._lastTime < anim.value()._reset)
        return;
    std::cout << "after time" << std::endl;
    if (anim.value().getstatus() == true) {
        //std::cout << "open" << std::endl;
        std::cout << "in if" << std::endl;
        r.emplace_comp(i, std::move(anim.value().getAnim2()));
        r.emplace_comp(i, Invincible());
        r.emplace_comp(i, InvincibleTime(time, anim.value().getAnimation1Time()));
        anim.value().getstatus() = false;
        anim.value()._lastTime = time;
        anim.value()._reset = anim.value().getAnimationTime();
        std::cout << "after if" << std::endl;
    } else {
        //std::cout << "close" << std::endl;
        std::cout << "in else" << std::endl;
        r.creatEntity();
        r.emplace_comp(r.currentEntity, BombGeneration(time, 0.4, Positions(800, 300), 8));
        r.emplace_comp(r.currentEntity, BombGenerationTime(time, 1.5));
        r.creatEntity();
        r.emplace_comp(r.currentEntity, BombGeneration(time, 0.4, Positions(800, 100), 8));
        r.emplace_comp(r.currentEntity, BombGenerationTime(time, 1.5));
        r.creatEntity();
        r.emplace_comp(r.currentEntity, BombGeneration(time, 0.4, Positions(10, 200), 6));
        r.emplace_comp(r.currentEntity, BombGenerationTime(time, 1.5));
        std::cout << "before" << std::endl;
        r.emplace_comp(i, std::move(anim.value().getAnim1()));
        std::cout << "after" << std::endl;
        r.emplace_comp(i, Invincible());
        r.emplace_comp(i, InvincibleTime(time, anim.value().getAnimation2Time() + anim.value().getAnimationTime()));
        anim.value().getstatus() = true;
        anim.value()._lastTime = 0;
        anim.value()._reset = 0;
        std::cout << "after else" << std::endl;
    }
}

void Animation2TimeSystem::system(Register &r, float time)
{
    auto &inv = r.getComp<InvincibleTime>();
    auto &animation = r.getComp<Animation2Time>();

    for (std::size_t i = 0; i < animation.size(); i++) {
        checkRules(animation[i], inv[i], time, i, r);
    }
}
