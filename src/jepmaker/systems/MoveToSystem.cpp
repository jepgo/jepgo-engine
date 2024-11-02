/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** MoveToSystem
*/

#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"
#include "jepmaker/components/MoveTo.hpp"
#include "jepmaker/components/Move.hpp"

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

exported(void) jepgoSystem(jgo::Game &game, float &time)
{
    float _reset = 0.1;
    std::vector<float> tmp;
    auto &move = game.ecs.getComp<MoveTo>();
    auto &pos = game.ecs.getComp<Positions>();

    if (game.getTime() - time < _reset)
        return;
    for (std::size_t i = 0; i < move.size(); i++) {
        if (move[i].has_value() && pos[i].has_value()) {
            tmp = getTheMove(pos[i].value(), move[i].value().getPosition());
            game.ecs.emplaceComp(i, Move(Positions(tmp[0] * move[i].value().getSpeed(), tmp[1] * move[i].value().getSpeed())));
        }
        if (move[i].has_value() && pos[i].has_value()) {
            if (AproximateDestination(pos[i].value(), move[i].value().getPosition(), 7)) {
                game.ecs.removeComponent<MoveTo>(i);
                game.ecs.removeComponent<Move>(i);
            }
        }
    }
    time = game.getTime();
}