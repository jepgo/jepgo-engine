/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Register
*/

#include "Register.hpp"

// Components
#include "Score.hpp"
#include "Points.hpp"
#include "Position.hpp"
#include "Drawable.hpp"
#include "Clickable2D.hpp"
#include "TextDrawable.hpp"
#include "Sprite2DMultiAnim.hpp"
//

Register::Register()
{
    regist.insert({std::type_index(typeid(Components::Score)), SparseArray<Components::Score>()});
    regist.insert({std::type_index(typeid(Components::Points)), SparseArray<Components::Points>()});
    regist.insert({std::type_index(typeid(Components::Drawable)), SparseArray<Components::Drawable>()});
    regist.insert({std::type_index(typeid(Components::Position2D)), SparseArray<Components::Position2D>()});
    regist.insert({std::type_index(typeid(Components::Clickable2D)), SparseArray<Components::Clickable2D>()});
    regist.insert({std::type_index(typeid(Components::TextDrawable)), SparseArray<Components::TextDrawable>()});
    regist.insert({std::type_index(typeid(Components::Sprite2DMultiAnim)), SparseArray<Components::Sprite2DMultiAnim>()});
}

Register::~Register()
{

}

void Register::creatEntity()
{
    currentEntity++;
    std::any_cast<SparseArray<Components::Score>&>(regist[std::type_index(typeid(Components::Score))]).add();
    std::any_cast<SparseArray<Components::Points>&>(regist[std::type_index(typeid(Components::Points))]).add();
    std::any_cast<SparseArray<Components::Drawable>&>(regist[std::type_index(typeid(Components::Drawable))]).add();
    std::any_cast<SparseArray<Components::Position2D>&>(regist[std::type_index(typeid(Components::Position2D))]).add();
    std::any_cast<SparseArray<Components::Clickable2D>&>(regist[std::type_index(typeid(Components::Clickable2D))]).add();
    std::any_cast<SparseArray<Components::TextDrawable>&>(regist[std::type_index(typeid(Components::TextDrawable))]).add();
    std::any_cast<SparseArray<Components::Sprite2DMultiAnim>&>(regist[std::type_index(typeid(Components::Sprite2DMultiAnim))]).add();
}

std::map<std::type_index, std::any> &Register::getRegister()
{
    return regist;
}

std::size_t Register::entityNbr()
{
    return std::any_cast<SparseArray<Components::Position2D>>(regist[std::type_index(typeid(Components::Position2D))]).size();
}
