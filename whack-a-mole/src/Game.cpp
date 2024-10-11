/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game
*/

#include "Game.hpp"
#include "Global.hpp"

#include "Position.hpp"
#include "Drawable.hpp"
#include "Sprite_Animation.hpp"

void WhackAMole::Game::createBackground(Register &r)
{
    r.creatEntity();
    r.emplace_comp(r.currentEntity, Components::Drawable(GAME_BACKGROUND, (Rectangle){0, 50, DEFFAULT_WIDTH, DEFFAULT_HEIGHT}, std::vector<float>{1, 1}));
    r.emplace_comp(r.currentEntity, Components::Positions(0, 0));
}

void WhackAMole::Game::createMole(Register &r, Components::Positions &&pos, float time, float reset)
{
    const float WIDTH_MOLE_SPRITE = 190;
    const float HEIGHT_MOLE_SPRITE = 144;

    r.creatEntity();
    r.emplace_comp(r.currentEntity, std::move(pos));
    r.emplace_comp(r.currentEntity, Components::Drawable(MOLE_SPRITE, (Rectangle){WIDTH_MOLE_SPRITE * 0, HEIGHT_MOLE_SPRITE * 0, WIDTH_MOLE_SPRITE, HEIGHT_MOLE_SPRITE}, std::vector<float>{0.5, 0.5}));
    r.emplace_comp(r.currentEntity, Components::Sprite_Animation(6, (int)WIDTH_MOLE_SPRITE, 0.1));
}