/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** DrawRebornSystem
*/

#pragma once
#include "Register.hpp"

class DrawRebornSystem {
    public:
        static void system(Register &r) {
            auto &draw = r.getComp<DrawReborn>();
            auto &reborn = r.getComp<Reborn>();

            for (std::size_t i = 0; i < reborn.size(); i++) {
                if (draw[i].has_value() && reborn[i].has_value()) {
                    int x = int(draw[i].value()._pos.x);
                    int y = int(draw[i].value()._pos.y);
                    std::string a = "Live = ";
                    std::string tmp = a + std::to_string(reborn[i].value().getLive());
                    DrawText(tmp.c_str(), (int)draw[i].value()._pos.x, (int)draw[i].value()._pos.y, draw[i].value()._size, draw[i].value()._color);
                }
            }
        };
    private:
};
