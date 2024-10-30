/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** LvlUp
*/

#pragma once
#include <string>

class LvLUp {
    public:
        LvLUp(std::size_t lvl) : _lvl(lvl) {};
        ~LvLUp() {};
        std::size_t _lvl;
};