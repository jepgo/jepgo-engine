/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Explosion
*/

#include "Components.hpp"
#include "Register.hpp"

void Explosion::explose(Register &r, std::size_t entity)
{
    auto &dmg = r.getComp<Dmg>();

    if (rect.has_value()) {
        r.emplace_comp(entity, Drawable(index, std::move(rect.value()), {scale[0], scale[1]}));
        r.emplace_comp(entity, Sprite_Animation(stat, value, time, true));
    } else if (rect.has_value()) {
        r.emplace_comp(entity, Drawable(index, std::move(rect)));
        r.emplace_comp(entity, Sprite_Animation(stat, value, time, true));
    } else
        r.emplace_comp(entity, Drawable(index));

    r.removeComponent<Hitable>(entity);
    r.removeComponent<Move>(entity);
}

void Hitable::Whenhit(std::size_t entity, Register &r)
{
    auto &explo = r.getComp<Explosion>();

    if (!explo[entity].has_value())
        return;
    explo[entity].value().explose(r, entity);
}
