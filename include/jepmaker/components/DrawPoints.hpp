/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** DrawPoints
*/

#pragma once
#include "jepengine/Client.hpp"
#include "jepmaker/components/Position.hpp"

class DrawPoints {
    public:
        DrawPoints(Position2D &&pos, std::size_t size, jgo::u32 color) : _pos(pos), _size(size), _color(color) {};
        ~DrawPoints() {};
        Position2D _pos;
        std::size_t _size;
        jgo::u32 _color;
};