/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** MessageSystem
*/

#pragma once
#include "Register.hpp"

class MessageSystem {
    public:
        static void system(Register &r) {
            auto &mess = r.getComp<Message>();

            for (std::size_t i = 0; i < mess.size(); i++) {
                if (mess[i].has_value()) {
                    DrawText(mess[i].value()._mess.c_str(), (int)mess[i].value()._pos.x, (int)mess[i].value()._pos.y, mess[i].value()._size, mess[i].value()._color);
                }
            }
        };
};
