/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** FreeSystem
*/

#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"

#include "jepmaker/components/Life.hpp"
#include "jepmaker/components/SpriteAnimation.hpp"
#include "jepmaker/components/Drawable2D.hpp"
#include "jepmaker/components/Controllable.hpp"
#include "jepmaker/components/Type.hpp"
#include "jepmaker/components/Free.hpp"
#include "jepmaker/components/ToFree.hpp"

static void removeAll(jgo::Game &game, std::size_t entity)
{
    game.ecs.removeEntity(entity);
    game.ecs.emplaceComp(entity, Free());
}

exported(void) jepgoSystem(jgo::Game &game, float time)
{
    std::size_t nbr = 0;
    auto &free = game.ecs.getComp<Free>();
    auto &life = game.ecs.getComp<Life>();
    auto &anim = game.ecs.getComp<Sprite_Animation>();
    auto &draw = game.ecs.getComp<Drawable>();
    auto &Control = game.ecs.getComp<Controllable>();
    auto &tofree = game.ecs.getComp<ToFree>();
    auto &type = game.ecs.getComp<Type>();

    for (std::size_t i = 0; i < life.size(); i++) {
        if (life[i].has_value() && life[i].value()._life <= 0 && type[i].has_value() && type[i].value().getType() != CONTRO && anim[i].has_value() == false)
            removeAll(game, i);
        if (tofree[i].has_value())
            removeAll(game, i);
    }
    // for (std::size_t i = 0; i < free.size(); i++)
    //     if (free[i].has_value())
    //         nbr++;
    // std::cout << "entity free = " << nbr << std::endl;
}

