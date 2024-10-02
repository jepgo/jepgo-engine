/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Shoot
*/

#include "Components.hpp"
#include "Register.hpp"
#include "Game.hpp"

Shoot::Shoot(float fireRate, Direction dir, int decal) : _fireRate(fireRate), _direction(dir), _decal(decal)
{
    _time = 0;
}

Shoot::~Shoot()
{
    
}

bool Shoot::verif(float time)
{
    if (time - _time >= _fireRate)
    {
        _time = time;
        return true;
    }
    else
        return false;
};

void Shoot::shoot(Register &r, Positions &pos)
{
    if (_direction == LEFT)
        Game::CreateShipShoot(r, pos + Positions(0 - _decal, 0));
    else if (_direction == RIGHT)
        Game::CreateShipShoot(r, pos + Positions(0 + _decal, 0));
    else if (_direction == UP)
        Game::CreateShipShoot(r, pos + Positions(0, 0 - _decal));
    else if (_direction == DOWN)
        Game::CreateShipShoot(r, pos + Positions(0, 0 + _decal));
}
