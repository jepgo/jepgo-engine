/*
** EPITECH PROJECT, 2024
** whack-a-mole
** File description:
** Sprite_Animation
*/

#include "Sprite_Animation.hpp"

Components::Sprite_Animation::Sprite_Animation(int sta, int value, double res, std::optional<bool> dead)
{
    status = sta;
    if (value < 0)
        isneg = true;
    else
        isneg = false;
    val = value;
    reset = res;
    t = 0;
    if (dead.has_value())
        deadAnimation = true;
    else
        deadAnimation = false;
}
