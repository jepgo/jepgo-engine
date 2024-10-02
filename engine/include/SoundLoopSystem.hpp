/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** SoundLoopSystem
*/

#pragma once
#include "Register.hpp"

class SoundLoopSystem {
    public:
        static void system(Register &r, std::vector<Sound> &buff, float time) {
            auto& sound = r.getComp<SoundLoop>();

            for (std::size_t i = 0; i < sound.size(); i++) {
                if (sound[i].has_value() && sound[i].value()._play == false) {
                    sound[i].value().Play(buff);
                }
            }
        };
    protected:
    private:
};
