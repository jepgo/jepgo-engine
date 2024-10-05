/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** AutoShoot
*/

#include "AutoShoot.hpp"

AutoShoot::AutoShoot(Shoot && shoot, Type &&type, float time, float reset) : _shoot(shoot), _type(type), _time(time), _reset(reset)
{
}

AutoShoot::~AutoShoot()
{
}
