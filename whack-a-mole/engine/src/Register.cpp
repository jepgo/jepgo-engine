/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Register
*/

#include "Register.hpp"

// Components
#include "Position.hpp"
#include "Drawable.hpp"
#include "Sprite_Animation.hpp"
//

Register::Register()
{
    regist.insert({std::type_index(typeid(Components::Positions)), SparseArray<Components::Positions>()});
    regist.insert({std::type_index(typeid(Components::Drawable)), SparseArray<Components::Drawable>()});
    regist.insert({std::type_index(typeid(Components::Sprite_Animation)), SparseArray<Components::Sprite_Animation>()});
}

Register::~Register()
{

}

void Register::creatEntity()
{
    currentEntity++;
    std::any_cast<SparseArray<Components::Positions>&>(regist[std::type_index(typeid(Components::Positions))]).add();
    std::any_cast<SparseArray<Components::Drawable>&>(regist[std::type_index(typeid(Components::Drawable))]).add();
    std::any_cast<SparseArray<Components::Sprite_Animation>&>(regist[std::type_index(typeid(Components::Sprite_Animation))]).add();
}

std::map<std::type_index, std::any> &Register::getRegister()
{
    return regist;
}

std::size_t Register::entityNbr()
{
    return std::any_cast<SparseArray<Components::Positions>>(regist[std::type_index(typeid(Components::Positions))]).size();
}
