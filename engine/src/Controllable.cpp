/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Controllable
*/

#include "Components.hpp"
#include "Register.hpp"

// void Controllable::onKeyDown(int key, Velocity &vel)
// {
//     try {
//     vel.press(ASSOCIATIVE_KEYS.at(key));
//     } catch(std::exception const &) {

//     }
// }

// void Controllable::onKeyUp(int key, Velocity &vel)
// {
//     try {
//     vel.unpress(ASSOCIATIVE_KEYS.at(key));
//     } catch(std::exception const &) {

//     }
// }

// void Controllable::updateDirection(Vector2 const &v)
// {
    
// }

void Controllable::Tir(Register &r, Positions &pos, int left)
{
    r.creatEntity();
    r.emplace_comp(r.entity_nbr, Drawable(1, Rectangle{229, 100, 20, 20}, std::vector<float>{1.5, 1.5}));
    r.emplace_comp(r.entity_nbr, pos + Positions(10 + left, 0));
    r.emplace_comp(r.entity_nbr, Move(Positions(4, 0)));
    r.emplace_comp(r.entity_nbr, Hitable(10, 10));
    r.emplace_comp(r.entity_nbr, Explosion(1, 4, -37, 0.2, 10, SHIPSHOOT, Rectangle{180, 300, 40, 40}, std::vector<float>{1.5, 1.5}));
}

void Controllable::moveStatus(std::optional<Sprite_Status> &stat, std::optional<Drawable> &draw, int key)
{
    if (key != KeyboardKey::KEY_DOWN && key != KeyboardKey::KEY_UP && key != KeyboardKey::KEY_LEFT && key != KeyboardKey::KEY_RIGHT)
        return;
    if (stat.has_value() && draw.has_value() && draw.value().getRect().has_value())
        draw.value().getRect().value().x = stat.value().status(ASSOCIATIVE_KEYS.at(key));
};
