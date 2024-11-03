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
        MoveTo(Position2D &&pos, int speed) : _pos(pos), _speed(speed) {};
        ~MoveTo() {};
        Position2D &getPosition() {return _pos;};
        int &getSpeed() {return _speed;};
    private:
        Position2D _pos;
        int _speed;
};