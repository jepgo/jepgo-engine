/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Game
*/

#pragma once
#include "Register.hpp"

class Game {
    public:
        Game();
        ~Game();
        std::size_t &getExp() {return _exp;};
        std::size_t &getPoint() {return _point;};
        std::size_t &getLvl() {return _lvl;};
    private:
        std::size_t _exp;
        std::size_t _point;
        std::size_t _lvl;
};
