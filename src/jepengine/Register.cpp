/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Register
*/

#include "jepengine/Register.hpp"
#include "jepmaker/components/Free.hpp"


Register::Register()
{
    return;
}

Register::~Register()
{
    return;
}

void Register::createEntity()
{
    auto &free = getComp<Free>();

    for (std::size_t i = 0; i < free.size(); i++)
        if (free[i].has_value()) {
            currentEntity = i;
            removeComponent<Free>(i);
            return;
        }
    tmp++;
    currentEntity = tmp;
    for (auto const &cb : _rules)
        cb(_regist);
}

std::map<std::type_index, std::any> &Register::getRegister()
{
    return _regist;
}

std::size_t Register::entityNbr(void) const
{
    // return std::any_cast<SparseArray<Positions>>(regist[std::type_index(typeid(Positions))]).size();
    return tmp + 1;
}
