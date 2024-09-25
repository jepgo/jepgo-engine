/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Module
*/

#pragma once
#include "Register.hpp"
#include "SparseArray.hpp"
#include "Components.hpp"

class Module {
    public:
        Module(std::map<Direction, int> space, int entity);
        ~Module();
        int getEntityToModule();
        void update(std::optional<Positions> &me, SparseArray<Positions> &pos);
        int _entity;
    private:
        std::map<Direction, int> _space;
};
