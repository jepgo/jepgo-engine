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
    r.emplace_comp(r.currentEntity, Drawable(GAME_BACKGROUND, (Rectangle){0, 50, DEFFAULT_WIDTH, DEFFAULT_HEIGHT}, std::vector<float>{1, 1}));
    r.emplace_comp(r.currentEntity, Positions(0, 0));
}

void WhackAMole::Game::createMole(Register &r, Positions &&pos, float time, float reset)
{
    const float WIDTH_MOLE_SPRITE = 190;
    const float HEIGHT_MOLE_SPRITE = 144;

    r.creatEntity();
    r.emplace_comp(r.currentEntity, MoveToPlayer(2));
    r.emplace_comp(r.currentEntity, std::move(pos));
    r.emplace_comp(r.currentEntity, Drawable(MOLE_SPRITE, (Rectangle){WIDTH_MOLE_SPRITE * 0, HEIGHT_MOLE_SPRITE * 0, WIDTH_MOLE_SPRITE, HEIGHT_MOLE_SPRITE}, std::vector<float>{0.5, 0.5}));
    r.emplace_comp(r.currentEntity, MoveToPlayerTime(time, reset));
    r.emplace_comp(r.currentEntity, Short_Animation(4, 16, 1, 0));
    r.emplace_comp(r.currentEntity, Velocity({1, 1, 1, 1}));
    r.emplace_comp(r.currentEntity, Hitable(15, 15, Positions(1, -1)));
    r.emplace_comp(r.currentEntity, Enemy(100, 10));
    r.emplace_comp(r.currentEntity, DoDmg(10));
    r.emplace_comp(r.currentEntity, Sprite_Animation(6, WIDTH_MOLE_SPRITE, 0.1));
}