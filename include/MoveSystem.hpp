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
    MoveSystem(float r) : reset(r){
        time = 0;
    };
    ~MoveSystem(){};
    static bool checkMovement(Register &r, std::size_t &entity, Positions const &Newpos) {
        auto &Col = r.getComp<Colision>();
        auto &pos = r.getComp<Positions>();

        std::map<std::size_t, Colision *> list;

        for (std::size_t i = 0; i < Col.size(); i++) {
            if (Col[i].has_value() && i != entity)
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
    void system(Register &r, sf::Time &t) {
        auto &move = r.getComp<Move>();
        auto &pos = r.getComp<Positions>();

        if (t.asMilliseconds() - time <= reset)
            return;
        for (std::size_t i = 0; i < move.size(); i++) {
            if (move[i].has_value() && checkMovement(r, i, move[i].value().getPos()))
                r.emplace_comp(i, Positions(move[i].value().getPos() + pos[i].value()));
            else
                r.removeComponent<Move>(i);
        }
        time = t.asMilliseconds();
    }

    float time;
    float reset;
private:
};
