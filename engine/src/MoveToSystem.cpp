/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** MoveToSystem
*/

#include "MoveToSystem.hpp"

MoveToSystem::MoveToSystem(float time, float reset) : _time(time), _reset(reset)
{
}

MoveToSystem::~MoveToSystem()
{
}

static std::vector<float> getTheMove(Positions &me, Positions &where)
{
    float x = where.x - me.x;
    float y = where.y - me.y;

    if (x < 0)
        x = -1;
    else if (x > 0)
        x = 1;
    if (y < 0)
        y = -1;
    else if (y > 0)
        y = 1;
    return std::vector<float>{x, y};
}

static bool AproximateDestination(Positions &me, Positions &to, float aprox)
{
    if ((to.x > me.x && to.x - me.x <= aprox) || (to.x < me.x && me.x - to.x <= aprox)) {
        if ((to.y > me.y && to.y - me.y <= aprox) || (to.y < me.y && me.y - to.y <= aprox)) {
            return true;
        }
    }
    return false;
}

void MoveToSystem::system(Register &r, float time)
{
    std::vector<float> tmp;
    auto &move = r.getComp<MoveTo>();
    auto &pos = r.getComp<Positions>();

    if (time - _time < _reset)
        return;

    for (std::size_t i = 0; i < move.size(); i++) {
        if (move[i].has_value() && pos[i].has_value()) {
            tmp = getTheMove(pos[i].value(), move[i].value().getPosition());
            r.emplace_comp(i, Move(Positions(tmp[0] * move[i].value().getSpeed(), tmp[1] * move[i].value().getSpeed())));
        }
        if (move[i].has_value() && pos[i].has_value()) {
            if (AproximateDestination(pos[i].value(), move[i].value().getPosition(), 7)) {
                r.removeComponent<MoveTo>(i);
                r.removeComponent<Move>(i);
            }
        }
    }
    _time = time;
}