/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** DrawReborn
*/

#pragma once
#include <string>
#include "jepengine/Client.hpp"
#include "jepmaker/components/Position.hpp"

class DrawReborn {
    public:
        DrawReborn(Positions &&pos, std::size_t size, jgo::u32 color) : _pos(pos), _size(size), _color(color) {};
        ~DrawReborn() {};
        Positions _pos;
        std::size_t _size;
        jgo::u32 _color;
};