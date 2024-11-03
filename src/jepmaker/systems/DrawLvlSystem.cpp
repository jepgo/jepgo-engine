/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** DrawlvlSystem
*/

#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"
#include "jepmaker/components/DrawLvl.hpp"
#include "jepmaker/components/Lvl.hpp"

exported(void) jepgoSystem(jgo::Game &game, float &time)
{
    auto &draw = game.ecs.getComp<DrawLvl>();
    auto &lvl = game.ecs.getComp<Lvl>();

    for (std::size_t i = 0; i < lvl.size(); i++)
    {
        if (draw[i].has_value() && lvl[i].has_value())
        {
            int x = int(draw[i].value()._pos.x);
            int y = int(draw[i].value()._pos.y);
            std::string a = "Lvl  ";
            std::string tmp = a + std::to_string(lvl[i].value()._lvl);
            game.getGraphicLib()->drawText(tmp.c_str(), jgo::Rectangle{draw[i].value()._pos.x, draw[i].value()._pos.y, 0, 0}, draw[i].value()._color, "", draw[i].value()._size);
        }
    }
};
