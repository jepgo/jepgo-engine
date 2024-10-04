/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** GameLvlSystem
*/

#pragma once
#include "Register.hpp"

class GameLvlSystem {
    public:
        GameLvlSystem(float time, float reset);
        ~GameLvlSystem();
        void system(Register &r, float time, std::vector<Sound> &sounds);
    private:    
        float _time;
        float _reset;
};
