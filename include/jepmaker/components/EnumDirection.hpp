/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** EnumDirection
*/

#pragma once
#include "jepengine/Client.hpp"
#include <map>

enum Direction
{
    DOWN,
    UP,
    RIGHT,
    LEFT,
    MID,
    TIR,
};

static std::map<int, Direction> const ASSOCIATIVE_KEYS = {
    {265, DOWN},
    {264, UP},
    {263, RIGHT},
    {262, LEFT},
    {65, TIR},
};