/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** MessageSystem
*/

#pragma once
#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"
#include "jepmaker/components/Message.hpp"

exported(void) jepgoSystem(jgo::Game &game, float time)
{
    auto &mess = game.ecs.getComp<Message>();

    for (std::size_t i = 0; i < mess.size(); i++) {
        if (mess[i].has_value()) {
            game.getGraphicLib()->drawText(mess[i].value()._mess.c_str(), jgo::Rectangle {(int)mess[i].value()._pos.x, (int)mess[i].value()._pos.y, 0, 0},  mess[i].value()._color, "", mess[i].value()._size);
        }
    }
};