
/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** DrawLvl
*/

#pragma once
#include "jepengine/Client.hpp"
#include "jepmaker/components/Position.hpp"

class DrawLvl {
    public:
        DrawLvl(Position2D &&pos, std::size_t size, jgo::u32 color) : _pos(pos), _size(size), _color(color) {};
        ~DrawLvl() {};
        Position2D _pos;
        std::size_t _size;
        jgo::u32 _color;
};
