/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** ModuleSystem
*/

#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"
#include "jepmaker/components/Position.hpp"
#include "jepmaker/components/Modules.hpp"
#include "jepmaker/components/Life.hpp"
#include "jepmaker/components/Drawable2D.hpp"
#include "jepmaker/components/Hitable2D.hpp"

static void Myupdate(std::optional<Position2D> &me, std::optional<Position2D> &pos, std::size_t entity, std::map<Direction, int> _space) {
            if (!(me.has_value()))
                return;
            if (pos.has_value()) {
                me.value().x = pos.value().x + _space[LEFT] - _space[RIGHT];
                me.value().y = pos.value().y - _space[UP] + _space[DOWN];   
            }
        };

exported(void) jepgoSystem(jgo::Game &game, float &t)
{
    auto &modules = game.ecs.getComp<Module>();
    auto &pos = game.ecs.getComp<Position2D>();
    auto &life = game.ecs.getComp<Life>();

    for (std::size_t i = 0; i < modules.size(); i++) {
        if (modules[i].has_value() && pos[i].has_value()) {
            Myupdate(pos[i], pos[modules[i].value()._entity], modules[i].value()._entity, modules[i].value()._space);
            //modules[i].value().update(pos[i], pos);
        }
        if (modules[i].has_value() && life[modules[i].value()._entity].has_value() && life[modules[i].value()._entity].value()._life <= 0) {
            game.ecs.removeComponent<Drawable>(i);
            game.ecs.removeComponent<Module>(i);
            game.ecs.removeComponent<Hitable>(i);
        }
    }
};