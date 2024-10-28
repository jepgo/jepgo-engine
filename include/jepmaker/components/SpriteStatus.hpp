/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** SpriteStatus
*/

#pragma once
#include "jepmaker/components/EnumDirection.hpp"

class Sprite_Status {
public:
    /**
     * @brief Construct a new Sprite_Status object
     *
     * @param s The directions of the Sprite
     */
    Sprite_Status(std::map<Direction, int> s) : stat(s) {};
    ~Sprite_Status() {};
    int status(Direction s)
    {
        return stat.at(s);
    };
    int mid() { return stat.at(MID); };

private:
    std::map<Direction, int> stat;
};