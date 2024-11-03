/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** AttachModule
*/

#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"
#include "jepmaker/components/Controllable.hpp"
#include "jepmaker/components/Hit.hpp"
#include "jepmaker/components/Shoot.hpp"
#include "jepmaker/components/Modules.hpp"
#include "jepmaker/components/Hitable2D.hpp"
#include "jepmaker/components/Type.hpp"
#include "jepmaker/components/Move.hpp"
#include "jepmaker/components/AutoShoot.hpp"

exported(void) jepgoSystem(jgo::Game &game, float &time)
{
    auto &hit = game.ecs.getComp<Hit>();
    auto &shoot = game.ecs.getComp<Shoot>();
    auto &moduleTir = game.ecs.getComp<ModuleShoot>();
    auto &moduleArm = game.ecs.getComp<ModuleArmor>();
    auto &control = game.ecs.getComp<Controllable>();

    for (std::size_t i = 0; i < moduleTir.size(); i++) {
        if (moduleTir[i].has_value() && hit[i].has_value() && control[hit[i].value().GetEntity()].has_value()) {
            game.ecs.emplaceComp(i, std::move(moduleTir[i].value().attach(hit[i].value().GetEntity())));
            moduleTir[i].value().changeShoot(shoot[hit[i].value().GetEntity()]);
            game.ecs.removeComponent<ModuleShoot>(i);
            game.ecs.removeComponent<Hit>(i);
            game.ecs.emplaceComp(i, Type(MODULE));
            game.ecs.removeComponent<Hitable>(i);
            game.ecs.removeComponent<Move>(i);
        }
        if (moduleArm[i].has_value() && hit[i].has_value() && control[hit[i].value().GetEntity()].has_value()) {
            game.ecs.emplaceComp(i, std::move(moduleArm[i].value().attach(hit[i].value().GetEntity())));
            game.ecs.emplaceComp(i, std::move(moduleArm[i].value().getLife()));
            game.ecs.emplaceComp(i, Type(MODULE_ARM));
            game.ecs.removeComponent<ModuleArmor>(i);
            game.ecs.removeComponent<Hit>(i);
            game.ecs.removeComponent<Move>(i);
            game.ecs.removeComponent<AutoShoot>(i);
        }
    }
};
