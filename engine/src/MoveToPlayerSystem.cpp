/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** MoveToPlayerSystem
*/

#include "MoveToPlayerSystem.hpp"

MoveToPlayerSystem::MoveToPlayerSystem(float reset) : _reset(reset)
{
    _time = 0;
}

MoveToPlayerSystem::~MoveToPlayerSystem()
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

static float CloseValue(Positions &pos1, Positions &pos2)
{
    return (pos1.x - pos2.x + pos1.y - pos2.y);
}

static int FoundClosestPlayer(Register &r, Positions &me)
{
    float res;
    int ind = 0;
    std::map<float, int> value;
    // std::vector<float> value;
    auto &control = r.getComp<Controllable>();
    auto &pos = r.getComp<Positions>();
    
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

void MoveToPlayerSystem::system(Register &r, float time)
{
    int ind;
    std::vector<float> tmp;
    auto &move = r.getComp<MoveToPlayer>();
    auto &pos = r.getComp<Positions>();

    if (time - _time < _reset)
        return;
    for (std::size_t i = 0; i < move.size(); i++) {
        if (move[i].has_value() && pos[i].has_value()) {
            ind = FoundClosestPlayer(r, pos[i].value());
            if (ind != -1) {
                tmp = getTheMove(pos[i].value(), pos[ind].value());
                r.emplace_comp(i, Move(Positions(tmp[0], tmp[1])));
            }
        }
    }
    _time = time;
}
