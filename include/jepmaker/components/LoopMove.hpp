/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** LoopMove
*/

#pragma once
#include "jepmaker/components/Position.hpp"

class LoopMove {
    public:
        LoopMove(Position2D &&pos) : _pos(pos) {};
        ~LoopMove() {};
        Position2D _pos;        
};