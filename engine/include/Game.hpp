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
        static void CreateMainThem(Register &r);
        static void CreatPlayer(Register &r, int height, int width);
        static void CreateAsteroid(Register &r);
        static void CreateBoostModule(Register &r);
        static void CreateShipShoot(Register &r, Positions &&);
        static void CreateShootModule(Register &r, Positions &&);
        static void CreateArmorModule(Register &r, Positions &&);
        static void CreatText(Register &r, Positions &&, std::string text, sf::Font &font);
        static void CreateMiniBoss1(Register &r, Positions &&);
        std::size_t &getExp() {return _exp;};
        std::size_t &getPoint() {return _point;};
        std::size_t &getLvl() {return _lvl;};
        std::size_t &getKm() {return _km;};
    private:
        std::size_t _exp;
        std::size_t _point;
        std::size_t _lvl;
        std::size_t _km;
};
