/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Position
*/

#include "Position.hpp"

Components::Position2D::Position2D(float x = 0, float y = 0) : x(x), y(y)
{
}

Components::Position2D Components::Position2D::operator+(Position2D const &pos) const
{
    return Position2D(this->x + pos.x, this->y + pos.y);
}

bool Components::Position2D::operator==(Position2D const &pos) const
{
    if (this->x == pos.x && this->y == pos.y)
        return true;
    return false;
}
