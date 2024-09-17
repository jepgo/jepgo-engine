/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Register
*/

#pragma once
#include <map>
#include <string>
#include <any>
#include <typeindex>
#include "SparseArray.hpp"
#include "Components.hpp"

class Register
{
public:
    Register();
    ~Register();
    void creatEntity();
    std::map<std::type_index, std::any> &getRegister();
    template <typename Component, class ...Params>
    void emplace_comp(std::size_t id, Params &&... par)
    {
        std::any_cast<SparseArray<Component>&>(regist[std::type_index(typeid(Component))]).emplace_at(id, par...);
    }
    template <typename Component>
    void add_comp(std::size_t id, Component &&comp)
    {
        std::any_cast<SparseArray<Component>&>(regist[std::type_index(typeid(Component))]).add(comp);
    }
    template <typename Component>
    SparseArray<Component> &getComp()
    {
        return std::any_cast<SparseArray<Component>&>(regist[std::type_index(typeid(Component))]);
    }
    std::size_t entityNbr();

private:
    std::map<std::type_index, std::any> regist;
};
