/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** MoveTo
*/

#pragma once
#include "Register.hpp"

class MoveTo {
    public:
        MoveTo(Positions &&pos, int speed);
        ~MoveTo();
        Positions &getPosition() {return _pos;};
        int &getSpeed() {return _speed;};
    private:
        Positions _pos;
        int _speed;
};
