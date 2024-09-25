/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** ModuleSystem
*/

#pragma once
#include "Register.hpp"
#include "Components.hpp"

class ModuleSystem
{
public:
    static void system(Register &r)
    {
        auto &modules = r.getComp<Module>();
        auto &pos = r.getComp<Positions>();
        auto &life = r.getComp<Life>();

        for (std::size_t i = 0; i < modules.size(); i++)
        {
            if (modules[i].has_value() && pos[i].has_value()) {
                modules[i].value().update(pos[i], pos);
            }
            if (modules[i].has_value() && life[modules[i].value()._entity].has_value() && life[modules[i].value()._entity].value()._life <= 0) {
                r.removeComponent<Drawable>(i);
                r.removeComponent<Module>(i);
            }
        }
    };

protected:
private:
};
