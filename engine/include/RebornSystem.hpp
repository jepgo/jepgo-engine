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
        static void system(Register &r, std::size_t playerEntity) {
            auto &reborn = r.getComp<Reborn>();
            auto &contro = r.getComp<Controllable>();
            auto &mess = r.getComp<Message>();

            if (contro[playerEntity].has_value())
                return;
            int key = GetKeyPressed();
            for (std::size_t i = 0; i < reborn.size(); i++) {
                if (key == KeyboardKey::KEY_A && reborn[i].has_value() && reborn[i].value().getLive() > 0) {
                    std::cout << "reborn" << std::endl;
                    reborn[i].value().getLive() -= 1;
                    r.emplace_comp(playerEntity, Controllable());
                    r.emplace_comp(playerEntity, Positions(100, 100));
                    r.emplace_comp(playerEntity, Drawable(1, Rectangle{202, 0, 30, 18}, std::vector<float>{1.5, 1.5}));
                    r.emplace_comp(playerEntity, Hitable(100, 40));
                    r.emplace_comp(playerEntity, Life(30));
                    r.emplace_comp(playerEntity, Type(CONTRO));
                    r.emplace_comp(playerEntity, Shoot(0.5, RIGHT, 20, 2));
                    r.emplace_comp(r.entity_nbr, Explosion(1, 4, -37, 0.2, 10, CONTRO, Rectangle{180, 300, 40, 40}, std::vector<float>{1.5, 1.5}));
                    for (std::size_t a = 0; a < mess.size(); a++) {
                        if (mess[a].has_value())
                            r.removeComponent<Message>(a);
                    }
                }
            }
        };
    private:
};
