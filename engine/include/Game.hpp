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
        static void CreatPlayer(Register &r, int height, int width);
        static void CreateAsteroid(Register &r);
        static void CreateBoostModule(Register &r);
        static void CreateShipShoot(Register &r, Positions &&);
        static void CreateShootModule(Register &r, Positions &&);
        static void CreateArmorModule(Register &r, Positions &&);
        std::size_t &getExp() {return _exp;};
        std::size_t &getPoint() {return _point;};
        std::size_t &getLvl() {return _lvl;};
    private:
        std::size_t _exp;
        std::size_t _point;
        std::size_t _lvl;
};
