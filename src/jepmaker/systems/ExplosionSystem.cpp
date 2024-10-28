/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** ExplosionSystem
*/

#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"
#include "jepmaker/components/Drawable2D.hpp"
#include "jepmaker/components/SpriteAnimation.hpp"
#include "jepmaker/components/Hitable2D.hpp"
#include "jepmaker/components/Move.hpp"
#include "jepmaker/components/Death.hpp"
#include "jepmaker/components/Explosion.hpp"

static void ToExplose(jgo::Game &game, std::size_t entity, std::optional<jgo::Rectangle> &rect, std::string &index, int stat, int value, double time, std::array<float, 2> scale)
{
    if (rect.has_value()) {
        game.ecs.emplaceComp(entity, Drawable(index, std::move(rect.value()), std::vector<float>{scale[0], scale[1]}));
        game.ecs.emplaceComp(entity, Sprite_Animation(stat, value, time, true));
    }
    else if (rect.has_value()) {
        game.ecs.emplaceComp(entity, Drawable(index, std::move(rect)));
        game.ecs.emplaceComp(entity, Sprite_Animation(stat, value, time, true));
    } else
        game.ecs.emplaceComp(entity, Drawable(index));

    game.ecs.removeComponent<Hitable>(entity);
    game.ecs.removeComponent<Move>(entity);
}

exported(void) jepgoSystem(jgo::Game &game, float &t)
{
    auto &death = game.ecs.getComp<Death>();
    auto &explosion = game.ecs.getComp<Explosion>();

    for (std::size_t i = 0; i < death.size(); i++) {
        if (death[i].has_value() && explosion[i].has_value()) {
            Explosion& tmp = explosion[i].value();
            ToExplose(game, i, tmp.rect, tmp.index, tmp.stat, tmp.value, tmp.time, std::array<float, 2>{tmp.scale[0], tmp.scale[1]});
            //explosion[i].value().explose(r, i);
            // PlaySound(sounds[ind]);
        }
    }
}