/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** MoveSystem
*/

#include "MoveSystem.hpp"

MoveSystem::MoveSystem(float r) : reset(r)
{
    time = 0;
};

MoveSystem::~MoveSystem()
{
}

bool MoveSystem::checkMovement(Register &r, std::size_t &entity, Positions const &Newpos) {
    auto &Col = r.getComp<Colision>();
    auto &pos = r.getComp<Positions>();

    std::cout << "check" << std::endl;
    std::map<std::size_t, Colision *> list;

    if (Col[entity].has_value() == false)
        return true;
    for (std::size_t i = 0; i < Col.size(); i++) {
        if (Col[i].has_value() && pos[i].has_value() && i != entity)
            list.insert(std::make_pair(i, &Col[i].value()));
    }
    if (list.size() == 0) {
        return true;
    }
    if (list.size() == 1) {
        return (Col[entity].value().isCol(*(list.begin()->second), pos[list.begin()->first].value(), Newpos + pos[entity].value()));
    }
    for (auto it = list.begin(); std::next(it) != list.end(); it++) {
        if (Col[entity].value().isCol(*(it->second), pos[it->first].value(), Newpos + pos[entity].value())) {
            return false;
        }
    }
    return true;
}

static bool checkScreen(std::optional<ScreenLimit> &limit, Positions pos)
{
    if (limit.has_value() == false)
        return true;
    if (pos.x >= limit.value()._height || pos.x <= 10)
        return false;
    if (pos.y >= limit.value()._width || pos.y <= 10)
        return false;
    return true;
}

void MoveSystem::system(Register &r, sf::Time &t) {
    auto &move = r.getComp<Move>();
    auto &pos = r.getComp<Positions>();
    auto &screen = r.getComp<ScreenLimit>();

    if (t.asMilliseconds() - time <= reset)
        return;
    for (std::size_t i = 0; i < move.size(); i++) {
        if (move[i].has_value() && pos[i].has_value() && MoveSystem::checkMovement(r, i, move[i].value().getPos()) && checkScreen(screen[i],Positions(move[i].value().getPos() + pos[i].value()))) {
                r.emplace_comp(i, Positions(move[i].value().getPos() + pos[i].value()));
        }
    }
    time = t.asMilliseconds();
}