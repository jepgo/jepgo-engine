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
        static void CreateBackGround(Register &r);
        static void CreateAsteroid(Register &r);
        static void CreateBomb(Register &r, Positions &&pos, float time, float reset);
        static void CreatePlanet(Register &r);
        static void CreateShipShoot(Register &r, Positions &&);
        static void CreateMiniBoss1(Register &r, Positions &&);
        static void CreateShootModule(Register &r, Positions &&);
        static void CreateArmorModule(Register &r, Positions &&);
        static void CreatPlayer(Register &r, int height, int width);
        static void CreateBoostModule(Register &r, std::size_t PlayerEntity);
        static void CreatText(Register &r, Positions &&, std::string text);
        static void CreateMessageTime(Register &r, Positions &&, std::string text, float time);
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
