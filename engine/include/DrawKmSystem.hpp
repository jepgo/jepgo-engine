/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** DrawKmSystem
*/

#pragma once
#include "Register.hpp"

class DrawKmSystem {
    public:
        static void system(Register &r) {
            auto &draw = r.getComp<DrawKm>();
            auto &km = r.getComp<DistanceKm>();

            for (std::size_t i = 0; i < km.size(); i++) {
                if (draw[i].has_value() && km[i].has_value()) {
                    int x = int(draw[i].value()._pos.x);
                    int y = int(draw[i].value()._pos.y);
                    std::string a = "KM = ";
                    std::string tmp = a + std::to_string(km[i].value()._dist);
                    DrawText(tmp.c_str(), (int)draw[i].value()._pos.x, (int)draw[i].value()._pos.y, draw[i].value()._size, draw[i].value()._color);
                }
            }
        };
    private:
};
