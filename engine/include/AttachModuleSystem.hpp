/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** AttachModule
*/

#pragma once
#include "Components.hpp"
#include "Module.hpp"
#include "Register.hpp"

class AttachModuleSystem
{
public:
    static void system(Register &r) {
        auto &hit = r.getComp<Hit>();
        auto &shoot = r.getComp<Shoot>();
        auto &moduleTir = r.getComp<ModuleShoot>();
        auto &moduleArm = r.getComp<ModuleArmor>();
        auto &control = r.getComp<Controllable>();

        for (std::size_t i = 0; i < moduleTir.size(); i++) {
            if (moduleTir[i].has_value() && hit[i].has_value() && control[hit[i].value().GetEntity()].has_value()) {
                r.emplace_comp(i, moduleTir[i].value().attach(hit[i].value().GetEntity()));
                moduleTir[i].value().changeShoot(shoot[hit[i].value().GetEntity()]);
                r.removeComponent<ModuleShoot>(i);
                r.removeComponent<Hit>(i);
                r.emplace_comp(i, Type(MODULE));
                r.removeComponent<Hitable>(i);
                r.removeComponent<Move>(i);
            }
            if (moduleArm[i].has_value() && hit[i].has_value() && control[hit[i].value().GetEntity()].has_value()) {
                r.emplace_comp(i, moduleArm[i].value().attach(hit[i].value().GetEntity()));
                r.emplace_comp(i, moduleArm[i].value().getLife());
                r.emplace_comp(i, Type(MODULE));
                r.removeComponent<ModuleArmor>(i);
                r.removeComponent<Hit>(i);
                r.removeComponent<Move>(i);
            }
        }
    };

private:
};
