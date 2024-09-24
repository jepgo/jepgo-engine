/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** MoveSystem
*/

#pragma once

#include "Register.hpp"
#include "Components.hpp"
#include <SFML/Graphics.hpp>

class MoveSystem
{
public:
    MoveSystem(float r);
    ~MoveSystem();
    static bool checkMovement(Register &r, std::size_t &entity, Positions const &Newpos);
    void system(Register &r, sf::Time &t);

    float time;
    float reset;
private:
};
