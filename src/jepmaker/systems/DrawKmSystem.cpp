/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** DrawKmSystem
*/

#pragma once

#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"
#include "jepmaker/components/DrawDistanceKm.hpp"
#include "jepmaker/components/DistanceKm.hpp"

exported(void) jepgoSystem(jgo::Game &game, float &time)
{
    auto &draw = game.ecs.getComp<DrawKm>();
    auto &km = game.ecs.getComp<DistanceKm>();

    for (std::size_t i = 0; i < km.size(); i++) {
        if (draw[i].has_value() && km[i].has_value()) {
            int x = int(draw[i].value()._pos.x);
            int y = int(draw[i].value()._pos.y);
            std::string a = "KM = ";
            std::string tmp = a + std::to_string(km[i].value()._dist);
            game.getGraphicLib()->drawText(tmp.c_str(), jgo::Rectangle{draw[i].value()._pos.x, (int)draw[i].value()._pos.y, 0, 0}, draw[i].value()._color, "", draw[i].value()._size);
        }
    }
};
