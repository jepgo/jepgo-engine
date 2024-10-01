/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** MoveToPlayerSystem
*/

#pragma once
#include "Register.hpp"

class MoveToPlayerSystem {
    public:
        MoveToPlayerSystem(float reset);
        ~MoveToPlayerSystem();
        void system(Register &r, float time);
    private:
        float _time;
        float _reset;
};
