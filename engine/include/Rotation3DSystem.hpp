/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Rotation3DSystem
*/

#pragma once
#include "Register.hpp"

class Rotation3DSystem {
    public:
        static void system(Register &r, float time, std::vector<Model> &);
};
