/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** SoloMoveSystem
*/

#include "SoloMoveSystem.hpp"

SoloMoveSystem::SoloMoveSystem(float re) : _reset(re)
{
    _time = 0;
}

SoloMoveSystem::~SoloMoveSystem()
{

}

void SoloMoveSystem::system(Register &r, sf::Time &time)
{
    auto &solomove = r.getComp<SoloMove>();
    auto &pos = r.getComp<Positions>();
    auto &vel = r.getComp<Velocity>();

    if (time.asMilliseconds() - _time <= _reset)
        return;
    for (std::size_t i = 0; i < solomove.size(); i++)
    {
        if (solomove[i].has_value() && pos[i].has_value() && vel[i].has_value())
            r.emplace_comp(i, Move(Positions(2, 2)));
        else
            r.removeComponent<Move>(i);
    }
}
