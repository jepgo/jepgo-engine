/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Position2D
*/

#pragma once

class Position2D {
public:
    /**
     * @brief Construct a new Position2D object
     *
     * @param x Position x of the object
     * @param y Position y of the Object
     */
    Position2D(float x = 0, float y = 0) : x(x), y(y) {}
    ~Position2D() {};
    Position2D operator+(Position2D const &pos) const
    {
        return Position2D(this->x + pos.x, this->y + pos.y);
    }
    bool operator==(Position2D const &pos) const
    {
        if (this->x == pos.x && this->y == pos.y)
            return true;
        return false;
    }
    float x;
    float y;
};