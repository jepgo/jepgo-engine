/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Shoot
*/

#include "Components.hpp"
#include "Register.hpp"

Shoot::Shoot(float fireRate, Direction dir, int decal) : _fireRate(fireRate), _direction(dir), _decal(decal)
{
    _time = 0;
}

Shoot::~Shoot()
{
    
}

bool Shoot::verif(sf::Time &time)
{
    if (time.asSeconds() - _time >= _fireRate)
    {
        _time = time.asSeconds();
        return true;
    }
    else
        return false;
};

void Shoot::shoot(Register &r, Positions &pos)
{
    r.creatEntity();
    r.emplace_comp(r.entity_nbr, Drawable(1, sf::IntRect(229, 100, 20, 20), std::vector<float>{1.5, 1.5}));
    if (_direction == LEFT)
        r.emplace_comp(r.entity_nbr, pos + Positions(0 - _decal, 0));
    else if (_direction == RIGHT)
        r.emplace_comp(r.entity_nbr, pos + Positions(0 + _decal, 0));
    else if (_direction == UP)
        r.emplace_comp(r.entity_nbr, pos + Positions(0, 0 - _decal));
    else if (_direction == DOWN)
        r.emplace_comp(r.entity_nbr, pos + Positions(0, 0 + _decal));
    r.emplace_comp(r.entity_nbr, Move(Positions(4, 0)));
    r.emplace_comp(r.entity_nbr, Hitable(10, 10));
    r.emplace_comp(r.entity_nbr, Life(1));
    r.emplace_comp(r.entity_nbr, DoDmg(10));
    r.emplace_comp(r.entity_nbr, Type(SHIPSHOOT));
    r.emplace_comp(r.entity_nbr, Explosion(1, 4, -37, 0.2, 10, SHIPSHOOT, sf::IntRect(180, 300, 40, 40), std::vector<float>{1.5, 1.5}));
}
