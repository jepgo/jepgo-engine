/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** BombGeneration
*/

#pragma once
#include "jepmaker/components/Position.hpp"

class BombGeneration {
    public:
        BombGeneration(float time, float reset, Position2D &&pos, float trac) : _time(time), _reset(reset), _pos(pos), _trac(trac) {};
        ~BombGeneration() {};
        Position2D &getPos() {return _pos;};
        float &getTime() {return _time;};
        float &getReset() {return _reset;};
        float &getTrac() {return _trac;};
    private:
        float _time;
        float _reset;
        Position2D _pos;
        float _trac;
};