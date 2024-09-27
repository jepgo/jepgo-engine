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
        static void system(Register &r) {
            auto &dmg = r.getComp<Dmg>();
            auto &life = r.getComp<Life>();
            auto &inv = r.getComp<Invincible>();
            auto &type = r.getComp<Type>();

            for (std::size_t i = 0; i < dmg.size(); i++) {
                if (dmg[i].has_value() && inv[i].has_value())
                    r.removeComponent<Dmg>(i);
                if (dmg[i].has_value() && life[i].has_value()) {
                    if (type[i].has_value() && type[i].value().getType() == MINIBOSS)
                        std::cout << "dmg" << std::endl;
                    life[i].value()._life -= dmg[i].value()._dmg;
                    r.removeComponent<Dmg>(i);
                    if (life[i].value()._life <= 0) {
                        //std::cout << "dead" << std::endl;
                        r.emplace_comp(i, Death());
                    }
                }
            }
        };
    private:
};
