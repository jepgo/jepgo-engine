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
    regist.insert({std::type_index(typeid(Sprite_Animation)), SparseArray<Sprite_Animation>()});
    regist.insert({std::type_index(typeid(Controllable)), SparseArray<Controllable>()});
    regist.insert({std::type_index(typeid(Velocity)), SparseArray<Velocity>()});
    regist.insert({std::type_index(typeid(Sprite_Status)), SparseArray<Sprite_Status>()});
    regist.insert({std::type_index(typeid(Hitable)), SparseArray<Hitable>()});
    regist.insert({std::type_index(typeid(Explosion)), SparseArray<Explosion>()});
    regist.insert({std::type_index(typeid(Colision)), SparseArray<Colision>()});
    regist.insert({std::type_index(typeid(Move)), SparseArray<Move>()});
    regist.insert({std::type_index(typeid(SoloMove)), SparseArray<SoloMove>()});
}

Register::~Register()
{
}

void Register::creatEntity()
{
    std::any_cast<SparseArray<Positions>&>(regist[std::type_index(typeid(Positions))]).add();
    std::any_cast<SparseArray<Drawable>&>(regist[std::type_index(typeid(Drawable))]).add();
    std::any_cast<SparseArray<Sprite_Animation>&>(regist[std::type_index(typeid(Sprite_Animation))]).add();
    std::any_cast<SparseArray<Velocity>&>(regist[std::type_index(typeid(Velocity))]).add();
    std::any_cast<SparseArray<Controllable>&>(regist[std::type_index(typeid(Controllable))]).add();
    std::any_cast<SparseArray<Sprite_Status>&>(regist[std::type_index(typeid(Sprite_Status))]).add();
    std::any_cast<SparseArray<Hitable>&>(regist[std::type_index(typeid(Hitable))]).add();
    std::any_cast<SparseArray<Explosion>&>(regist[std::type_index(typeid(Explosion))]).add();
    std::any_cast<SparseArray<Colision>&>(regist[std::type_index(typeid(Colision))]).add();
    std::any_cast<SparseArray<Move>&>(regist[std::type_index(typeid(Move))]).add();
    std::any_cast<SparseArray<SoloMove>&>(regist[std::type_index(typeid(SoloMove))]).add();
}

std::map<std::type_index, std::any> &Register::getRegister()
{
    return regist;
}

std::size_t Register::entityNbr()
{
    return std::any_cast<SparseArray<Positions>>(regist[std::type_index(typeid(Positions))]).size();
}
