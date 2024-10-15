/*
** EPITECH PROJECT, 2024
** whack-a-mole
** File description:
** Sprite2DMultiAnimSystem
*/

#include "Sprite2DMultiAnimSystem.hpp"

#include "Drawable.hpp"
#include "Sprite2DMultiAnim.hpp"

Systems::Sprite2DMultiAnimSystem::Sprite2DMultiAnimSystem()
{
}

Systems::Sprite2DMultiAnimSystem::~Sprite2DMultiAnimSystem()
{
}

void Systems::Sprite2DMultiAnimSystem::system(Register &r, float time)
{
    auto &rec = r.getComp<Components::Sprite2DMultiAnim>();
    auto &draw = r.getComp<Components::Drawable>();

    for (std::size_t i = 0; i < rec.size(); i++) {
        if (rec[i].has_value() && draw[i].has_value() && time >= rec[i].value().getTime())
        {
            auto loc = rec[i].value().updateSpriteLocation();

            draw[i].value().getRect().value().x = loc.x * rec[i].value().getRecSize().x;
            draw[i].value().getRect().value().y = loc.y * rec[i].value().getRecSize().y;
            rec[i].value().setTime(time + rec[i].value().getSpeed());

        }
    }
}
