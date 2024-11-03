/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MoveToPlayerSystem
*/
#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"
#include "jepmaker/components/Position.hpp"
#include "jepmaker/components/Controllable.hpp"
#include "jepmaker/components/MoveToPlayer.hpp"
#include "jepmaker/components/Move.hpp"

static std::vector<float> getTheMove(Position2D &me, Position2D &where)
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

static float CloseValue(Position2D &pos1, Position2D &pos2)
{
    return (pos1.x - pos2.x + pos1.y - pos2.y);
}

static int FoundClosestPlayer(jgo::Game &game, Position2D &me)
{
    float res;
    int ind = 0;
    std::map<float, int> value;
    // std::vector<float> value;
    auto &control = game.ecs.getComp<Controllable>();
    auto &pos = game.ecs.getComp<Position2D>();
    
    for (std::size_t i = 0; i < control.size(); i++) {
        if (control[i].has_value() && pos[i].has_value()) {
            value[CloseValue(pos[i].value(), me)] = i;
            //value.push_back(CloseValue(pos[i].value(), me));
        }
    }
    if (value.size() == 0)
        return -1;
    ind = value.begin()->second;
    res = value.begin()->first;
    for (auto it = value.begin(); it != value.end(); it++) {
        if (it->first < res) {
            ind = it->second;
        }
    }
    return ind;
}

exported(void) jepgoSystem(jgo::Game &game, float &time)
{
    int ind;
    float _reset = 0.3;
    std::vector<float> tmp;
    auto &move = game.ecs.getComp<MoveToPlayer>();
    auto &pos = game.ecs.getComp<Position2D>();

    if (game.getTime() - time < _reset)
        return;
    for (std::size_t i = 0; i < move.size(); i++) {
        if (move[i].has_value() && pos[i].has_value()) {
            ind = FoundClosestPlayer(game, pos[i].value());
            if (ind != -1) {
                tmp = getTheMove(pos[i].value(), pos[ind].value());
                game.ecs.emplaceComp(i, Move(Position2D(tmp[0] * move[i].value()._speed, tmp[1] * move[i].value()._speed)));
            }
        }
    }
    time = game.getTime();
}