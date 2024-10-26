/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Positions
*/

#pragma once

class Positions {
public:
    /**
     * @brief Construct a new Positions object
     *
     * @param x Position x of the object
     * @param y Position y of the Object
     */
    Positions(float x = 0, float y = 0) : x(x), y(y) {}
    ~Positions() {};
    Positions operator+(Positions const &pos) const
    {
        return Positions(this->x + pos.x, this->y + pos.y);
    }
    bool operator==(Positions const &pos) const
    {
        if (this->x == pos.x && this->y == pos.y)
            return true;
        return false;
    }
    float x;
    float y;
};