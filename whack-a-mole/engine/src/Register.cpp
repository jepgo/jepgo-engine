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
#include "Sprite2DMultiAnim.hpp"
//

Register::Register()
{
    regist.insert({std::type_index(typeid(Components::Positions)), SparseArray<Components::Positions>()});
    regist.insert({std::type_index(typeid(Components::Drawable)), SparseArray<Components::Drawable>()});
    regist.insert({std::type_index(typeid(Components::Sprite2DMultiAnim)), SparseArray<Components::Sprite2DMultiAnim>()});
}

Register::~Register()
{

}

void Register::creatEntity()
{
    currentEntity++;
    std::any_cast<SparseArray<Components::Positions>&>(regist[std::type_index(typeid(Components::Positions))]).add();
    std::any_cast<SparseArray<Components::Drawable>&>(regist[std::type_index(typeid(Components::Drawable))]).add();
    std::any_cast<SparseArray<Components::Sprite2DMultiAnim>&>(regist[std::type_index(typeid(Components::Sprite2DMultiAnim))]).add();
}

std::map<std::type_index, std::any> &Register::getRegister()
{
    return regist;
}

std::size_t Register::entityNbr()
{
    return std::any_cast<SparseArray<Components::Positions>>(regist[std::type_index(typeid(Components::Positions))]).size();
}
