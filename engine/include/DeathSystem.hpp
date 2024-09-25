/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** DeathSystem
*/

#pragma once
#include "Components.hpp"
#include "Register.hpp"

class DeathSystem {
    public:
        static void death(Register &r, std::size_t entity) {
            r.removeComponent<Drawable>(entity);
            r.removeComponent<Positions>(entity);
            r.removeComponent<Explosion>(entity);
            r.removeComponent<Controllable>(entity);
        };
        static void system(Register &r) {
            auto &life = r.getComp<Life>();

            for (std::size_t i = 0; i < life.size(); i++) {
                if (life[i].has_value() && life[i].value()._life <= 0)
                    DeathSystem::death(r, i);
            }
        };
    private:
};
