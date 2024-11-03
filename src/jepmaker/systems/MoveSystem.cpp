/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** MoveSystem
*/

#include "jepmod/exported.hpp"
#include "jepengine/Game.hpp"
#include "jepmaker/components/Colision.hpp"
#include "jepmaker/components/Move.hpp"
#include "jepmaker/components/ScreenLimit.hpp"

/**
 * @brief The CheckMovement
 * 
 * @param game Game
 * @param entity The curr entity
 * @param Newpos The NewPos for the entity
 * @return true 
 * @return false 
 */
static bool checkMovement(jgo::Game &game, std::size_t &entity, Position2D const &Newpos) {
    auto &Col = game.ecs.getComp<Colision>();
    auto &pos = game.ecs.getComp<Position2D>();

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

/**
 * @brief The CheckScreenFunction
 * 
 * @param limit The ScreenLimit component
 * @param pos The Position of the entity
 * @return true 
 * @return false 
 */
static bool checkScreen(std::optional<ScreenLimit> &limit, Position2D pos)
{
    if (limit.has_value() == false)
        return true;
    if (pos.x >= limit.value()._height || pos.x <= 10)
        return false;
    if (pos.y >= limit.value()._width || pos.y <= 10)
        return false;
    return true;
}

/**
 * @brief The MoveSystem
 * 
 * The purpose of this system is to move entities in the form of a vector.
 * 
 */
exported(void) jepgoSystem(jgo::Game &game, float &time)
{
    float reset = 0.01;
    auto &move = game.ecs.getComp<Move>();
    auto &pos = game.ecs.getComp<Position2D>();
    auto &screen = game.ecs.getComp<ScreenLimit>();

    float t = game.getTime();

    if (t - time <= reset) {
        return;
    }
    for (std::size_t i = 0; i < move.size(); i++) {
        if (move[i].has_value() && pos[i].has_value() && checkMovement(game, i, move[i].value().getPos()) && checkScreen(screen[i],Position2D(move[i].value().getPos() + pos[i].value()))) {
                game.ecs.emplaceComp(i, Position2D(move[i].value().getPos() + pos[i].value()));
        }
    }
    time = t;
}