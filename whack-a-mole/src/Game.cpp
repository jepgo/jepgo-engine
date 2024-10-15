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
#include "Sprite2DMultiAnim.hpp"

const Vector2 WhackAMole::Game::RECSIZE = {WIDTH_MOLE_SPRITE, HEIGHT_MOLE_SPRITE};

const std::map<int, std::vector<Vector2>> WhackAMole::Game::MOLES_ANIM = {
    {(int)MoleStates::SLEEP, {{0, 0}}},
    {(int)MoleStates::WAKE_UP, {{1, 0}, {2, 0}, {3, 0}, {4, 0}}},
    {(int)MoleStates::ATTACK, {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {1, 1}, {0, 1}}}
};

const float WhackAMole::Game::WIDTH_MOLE_SPRITE = 190;
const float WhackAMole::Game::HEIGHT_MOLE_SPRITE = 144;

void WhackAMole::Game::createBackground(Register &r)
{
    Rectangle REC = {0, 50, DEFFAULT_WIDTH, DEFFAULT_HEIGHT};

    r.creatEntity();
    r.emplace_comp(r.currentEntity, Components::Drawable(GAME_BACKGROUND, REC, std::vector<float>{1, 1}));
    r.emplace_comp(r.currentEntity, Components::Positions(0, 0));
}

void WhackAMole::Game::createMole(Register &r, Components::Positions &&pos)
{
    const Rectangle REC = {WIDTH_MOLE_SPRITE * 0, HEIGHT_MOLE_SPRITE * 0, WIDTH_MOLE_SPRITE, HEIGHT_MOLE_SPRITE};

    r.creatEntity();
    r.emplace_comp(r.currentEntity, std::move(pos));
    r.emplace_comp(r.currentEntity, Components::Drawable(MOLE_SPRITE, REC, std::vector<float>{0.5, 0.5}));
    r.emplace_comp(r.currentEntity, Components::Sprite2DMultiAnim(RECSIZE, MOLES_ANIM, MoleStates::SLEEP, 0.2f, 11));
}
