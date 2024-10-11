/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** RebornSystem
*/

#pragma once
#include "Register.hpp"

class RebornSystem {
    public:
        static void system(Register &r, std::size_t playerEntity, float time, int key) {
            auto &reborn = r.getComp<Reborn>();
            auto &contro = r.getComp<Controllable>();
            auto &mess = r.getComp<Message>();

            if (contro[playerEntity].has_value())
                return;
            for (std::size_t i = 0; i < reborn.size(); i++) {
                if (key == KeyboardKey::KEY_SPACE && reborn[i].has_value() && reborn[i].value().getLive() > 0) {
                    reborn[i].value().getLive() -= 1;
                    r.removeComponent<Sprite_Animation>(i);
                    r.emplace_comp(playerEntity, Controllable());
                    r.emplace_comp(playerEntity, Positions(100, 100));
                    r.emplace_comp(playerEntity, Model3D(0, 70, 40, 10));
                    r.emplace_comp(playerEntity, Hitable(100, 40));
                    r.emplace_comp(playerEntity, Life(30));
                    r.emplace_comp(playerEntity, Type(CONTRO));
                    r.emplace_comp(playerEntity, Shoot(0.5, RIGHT, 20, 2));
                    r.emplace_comp(playerEntity, Invincible());
                    r.emplace_comp(playerEntity, InvincibleTime(time, 2));
                    r.emplace_comp(r.currentEntity, Explosion(1, 4, -37, 0.2, 10, CONTRO, Rectangle{180, 300, 40, 40}, std::vector<float>{1.5, 1.5}));
                    for (std::size_t a = 0; a < mess.size(); a++) {
                        if (mess[a].has_value())
                            r.removeComponent<Message>(a);
                    }
                }
            }
        };
    private:
};
