/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Draw3DSystem
*/

#pragma once
#include "Register.hpp"

class Draw3DSystem {
    public:
        Draw3DSystem(float time, float reset);
        ~Draw3DSystem();
        void system(Register &r, float &time, std::vector<Model> &mod);
    private:
        float _time;
        float _reset;
};
