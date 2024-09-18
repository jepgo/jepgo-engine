/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Register
*/

#include "Register.hpp"

enum mat {
    POS,
    DRAW,
};

Register::Register()
{
    regist.insert({std::type_index(typeid(Positions)), SparseArray<Positions>()});
    regist.insert({std::type_index(typeid(Drawable)), SparseArray<Drawable>()});
    regist.insert({std::type_index(typeid(Sprite_Status)), SparseArray<Sprite_Status>()});
    regist.insert({std::type_index(typeid(Controllable)), SparseArray<Controllable>()});
    regist.insert({std::type_index(typeid(Velocity)), SparseArray<Velocity>()});
}

Register::~Register()
{
}

void Register::creatEntity()
{
    std::any_cast<SparseArray<Positions>&>(regist[std::type_index(typeid(Positions))]).add();
    std::any_cast<SparseArray<Drawable>&>(regist[std::type_index(typeid(Drawable))]).add();
    std::any_cast<SparseArray<Sprite_Status>&>(regist[std::type_index(typeid(Sprite_Status))]).add();
    std::any_cast<SparseArray<Velocity>&>(regist[std::type_index(typeid(Velocity))]).add();
    std::any_cast<SparseArray<Controllable>&>(regist[std::type_index(typeid(Controllable))]).add();
}

std::map<std::type_index, std::any> &Register::getRegister()
{
    return regist;
}

std::size_t Register::entityNbr()
{
    return std::any_cast<SparseArray<Positions>>(regist[std::type_index(typeid(Positions))]).size();
}
