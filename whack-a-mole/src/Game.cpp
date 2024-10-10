/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game
*/

#include "Global.hpp"
#include "Game.hpp"

void WhackAMole::Game::createBackground(Register &r)
{
    r.creatEntity();
    r.emplace_comp(r.currentEntity, Drawable(0, (Rectangle){0, 0, DEFFAULT_WIDTH, DEFFAULT_HEIGHT}, std::vector<float>{1, 1}));
    r.emplace_comp(r.currentEntity, Positions(0, 0));
}