/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Sprite2DMultiAnimSystem
*/

#include "jepengine/Game.hpp"
#include "jepmod/exported.hpp"
#include "jepmaker/components/Drawable2D.hpp"
#include "jepmaker/components/Sprite2DMultiAnim.hpp"

exported(void) jepgoSystem(jgo::Game &game, float &t)
{
    auto &draw = game.ecs.getComp<Drawable>();
    auto &multanim = game.ecs.getComp<Sprite2DMultiAnim>();

    for (std::size_t i = 0; i < multanim.size(); i++) {
        if (multanim[i].has_value() && draw[i].has_value() && game.getTime() >= multanim[i].value().getTime())
        {
            auto loc = multanim[i].value().updateSpriteLocation();

            draw[i].value().getRect().value().x = loc.x * multanim[i].value().getRecSize().x;
            draw[i].value().getRect().value().y = loc.y * multanim[i].value().getRecSize().y;

            multanim[i].value().setTime(game.getTime() + multanim[i].value().getSpeed());
        }
    }
}