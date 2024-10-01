/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** DmgSystem
*/

#pragma once
#include "Components.hpp"
#include "Register.hpp"

class DmgSystem {
    public:
        /**
         * @brief The System of all Dmg taken by the entities
         * 
         * @param r 
         */
        static void system(Register &r, float time) {
            auto &dmg = r.getComp<Dmg>();
            auto &life = r.getComp<Life>();
            auto &inv = r.getComp<Invincible>();

            for (std::size_t i = 0; i < dmg.size(); i++) {
                if (dmg[i].has_value() && inv[i].has_value())
                    r.removeComponent<Dmg>(i);
                if (dmg[i].has_value() && life[i].has_value()) {
                    life[i].value()._life -= dmg[i].value()._dmg;
                    r.emplace_comp<Invincible>(i, Invincible());
                    r.emplace_comp<InvincibleTime>(i, InvincibleTime(time, 0.1));
                    r.removeComponent<Dmg>(i);
                    if (life[i].value()._life <= 0) {
                        r.emplace_comp(i, Death());
                    }
                }
            }
        };
    private:
};
