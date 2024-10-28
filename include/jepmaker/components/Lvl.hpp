/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Lvl
*/

#pragma once
#include <string>

class Lvl {
    public:
        Lvl(std::size_t lvl) : _lvl(lvl) {};
        ~Lvl() {};
        std::size_t _lvl;
};