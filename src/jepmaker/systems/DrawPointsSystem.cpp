/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** DrawptsSystem
*/

#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"
#include "jepmaker/components/DrawPoints.hpp"
#include "jepmaker/components/Points.hpp"

exported(void) jepgoSystem(jgo::Game &game, float time)
{
    auto &draw = game.ecs.getComp<DrawPoints>();
    auto &pts = game.ecs.getComp<Points>();

    for (std::size_t i = 0; i < pts.size(); i++)
    {
        if (draw[i].has_value() && pts[i].has_value())
        {
            std::string a = "Points = ";
            std::string tmp = a + std::to_string(pts[i].value()._point);
            game.getGraphicLib()->drawText(tmp.c_str(), jgo::Rectangle{draw[i].value()._pos.x, draw[i].value()._pos.y, 0, 0}, draw[i].value()._color, "", draw[i].value()._size);
        }
    }
};