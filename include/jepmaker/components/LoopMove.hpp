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
        LoopMove(Positions &&pos) : _pos(pos) {};
        ~LoopMove() {};
        Positions _pos;        
};