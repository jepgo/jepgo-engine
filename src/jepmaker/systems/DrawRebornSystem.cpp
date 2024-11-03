/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** DrawptsSystem
*/

#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"
#include "jepmaker/components/DrawReborn.hpp"
#include "jepmaker/components/Reborn.hpp"

exported(void) jepgoSystem(jgo::Game &game, float time)
{
    auto &draw = game.ecs.getComp<DrawReborn>();
    auto &pts = game.ecs.getComp<Reborn>();

    for (std::size_t i = 0; i < pts.size(); i++)
    {
        if (draw[i].has_value() && pts[i].has_value())
        {
            std::string a = "Reborn = ";
            std::string tmp = a + std::to_string(pts[i].value().getLive());
            game.getGraphicLib()->drawText(tmp.c_str(), jgo::Rectangle{draw[i].value()._pos.x, draw[i].value()._pos.y, -1, -1}, draw[i].value()._color, "", draw[i].value()._size);
        }
    }
};