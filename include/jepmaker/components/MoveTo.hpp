/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** MoveTo
*/

#pragma once
#include "jepmaker/components/Position.hpp"

class MoveTo {
    public:
        MoveTo(Positions &&pos, int speed) : _pos(pos), _speed(speed) {};
        ~MoveTo() {};
        Positions &getPosition() {return _pos;};
        int &getSpeed() {return _speed;};
    private:
        Positions _pos;
        int _speed;
};