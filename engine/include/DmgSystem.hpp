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
        static void system(Register &r) {
            auto &dmg = r.getComp<Dmg>();
            auto &life = r.getComp<Life>();

            for (std::size_t i = 0; i < dmg.size(); i++) {
                if (dmg[i].has_value() && life[i].has_value()) {
                    life[i].value()._life -= dmg[i].value()._dmg;
                    r.removeComponent<Dmg>(i);
                }
            }
        };
    private:
};
