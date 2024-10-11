/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Position
*/

#include "Position.hpp"

Components::Positions::Positions(float x = 0, float y = 0) : x(x), y(y)
{
}

Components::Positions Components::Positions::operator+(Positions const &pos) const
{
    return Positions(this->x + pos.x, this->y + pos.y);
}

bool Components::Positions::operator==(Positions const &pos) const
{
    if (this->x == pos.x && this->y == pos.y)
        return true;
    return false;
}
