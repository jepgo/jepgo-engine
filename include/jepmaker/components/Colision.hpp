
/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Colision
*/

#pragma once
#include "jepmaker/components/Position.hpp"

class Colision
{
public:
    /**
     * @brief Construct a new Colision object
     *
     * @param w the width of the object
     * @param h the hight of the object
     */
    Colision(int w, int h) : width(w), height(h) {};
    ~Colision() {};

    /**
     * @brief Methode to know if 2 colision object touch each others
     *
     * @param hit the other Controllable object
     * @param him The position of the second Hitable
     * @param me The Position of this Hitable
     * @return true
     * @return false
     */
    bool isCol(Colision &col, Positions const &him, Positions const &me)
    {
        return (me.x + width < him.x || me.x > him.x + col.width || me.y + height < him.y || me.y > him.y + col.height);
    }

private:
    int width;
    int height;
};
