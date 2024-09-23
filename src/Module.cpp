/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Module
*/

#include "Module.hpp"

Module::Module(std::map<Direction, int> space, int entity) : _space(space), _entity(entity)
{
}

Module::~Module()
{
}

int Module::getEntityToModule()
{
    return _entity;
}

void Module::update(std::optional<Positions> &me, SparseArray<Positions> &pos)
{
    if (!(me.has_value()))
        return;
    if (pos[_entity].has_value()) {
        me.value().x = pos[_entity].value().x + _space[LEFT] - _space[RIGHT];
        me.value().y = pos[_entity].value().y - _space[UP] + _space[DOWN];   
    }
}
