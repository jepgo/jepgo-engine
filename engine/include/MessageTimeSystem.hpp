/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** MessageTimeSystem
*/

#pragma once
#include "Register.hpp"

class MessageTimeSystem {
    public:
        static void system(Register &r, float time) {
            auto &messageTime = r.getComp<MessageTime>();
            auto &message = r.getComp<Message>();

            for (std::size_t i = 0; i < messageTime.size(); i++) {
                if (messageTime[i].has_value() && message[i].has_value()) {
                    if (time - messageTime[i].value().getTime() >= messageTime[i].value().getReset()) {
                        r.removeComponent<Message>(i);
                        r.removeComponent<MessageTime>(i);
                    }
                }
            }
        };
};
