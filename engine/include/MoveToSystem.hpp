/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** MoveToSystem
*/

#pragma once
#include "Register.hpp"

class MoveToSystem {
    public:
        MoveToSystem(float time, float reset);
        ~MoveToSystem();
        void system(Register &r, float time);
    private:
        float _time;
        float _reset;
};
