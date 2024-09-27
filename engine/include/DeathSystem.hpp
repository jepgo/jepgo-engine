/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** DeathSystem
*/

#pragma once
#include "Components.hpp"
#include "Register.hpp"
#include "Game.hpp"

class DeathSystem {
    public:
        static void death(Register &r, std::size_t entity) {
            auto &type = r.getComp<Type>();

            if (type[entity].has_value() && (type[entity].value().getType() == CONTRO || type[entity].value().getType() == MODULE)) {
                //r.removeComponent<Drawable>(entity);
                //r.removeComponent<Positions>(entity);
                //r.removeComponent<Explosion>(entity);
                r.removeComponent<Controllable>(entity);
                r.removeComponent<Hitable>(entity);
            }
        };
        /**
         * @brief The death System for all the Obj
         * 
         * @param r The Registry of all the Entity
         * @param player The data about a player
         */
        static void system(Register &r, Game &player) {
            auto &life = r.getComp<Life>();
            auto &enemy = r.getComp<Enemy>();
            auto &death = r.getComp<Death>();

            for (std::size_t i = 0; i < life.size(); i++) {
                if (life[i].has_value() && life[i].value()._life <= 0) {
                    DeathSystem::death(r, i);
                    if (enemy[i].has_value() && death[i].has_value()) {
                        player.getExp() += enemy[i].value()._exp;
                        player.getPoint() += enemy[i].value()._point;
                    }
                    r.removeComponent<Death>(i);
                }
            }
        };
    private:
};
