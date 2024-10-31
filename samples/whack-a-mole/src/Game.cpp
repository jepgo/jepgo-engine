/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game
*/

#include "Game.hpp"
#include "Global.hpp"

#include "jepmaker/components/Position.hpp"
#include "jepmaker/components/Drawable2D.hpp"
#include "jepmaker/components/Clickable2D.hpp"

const float WhackAMole::Game::WIDTH_MOLE_SPRITE = 190.0f;
const float WhackAMole::Game::HEIGHT_MOLE_SPRITE = 144.0f;

void WhackAMole::Game::createBackground(jgo::Client &game)
{
    game.ecs.createEntity();
    game.ecs.emplaceComp<Positions>(game.ecs.currentEntity, Positions(0, 0));
    game.ecs.emplaceComp<Drawable>(game.ecs.currentEntity, Drawable(TEXTURES_PATH.at(Textures::GAME_BACKGROUND), jgo::Rectangle(0, 50, 800, 600)));
}

void WhackAMole::Game::createMole(jgo::Client &game, Positions &&pos)
{
    const Rectangle REC = {WIDTH_MOLE_SPRITE * 0, HEIGHT_MOLE_SPRITE * 0, WIDTH_MOLE_SPRITE, HEIGHT_MOLE_SPRITE};

    game.ecs.createEntity();
    game.ecs.emplaceComp(game.ecs.currentEntity, std::move(pos));
    game.ecs.emplaceComp(game.ecs.currentEntity, Clickable2D());
    game.ecs.emplaceComp(game.ecs.currentEntity, Drawable(TEXTURES_PATH.at(Textures::MOLE_SPRITE), jgo::Rectangle(WIDTH_MOLE_SPRITE * 0, HEIGHT_MOLE_SPRITE * 0, WIDTH_MOLE_SPRITE, HEIGHT_MOLE_SPRITE), std::vector<float>{0.5, 0.5}));
    // r.emplace_comp(r.currentEntity, Components::Sprite2DMultiAnim(RECSIZE, MOLES_ANIM, MoleStates::SLEEP, 0.2f, 11));
    // r.emplace_comp(r.currentEntity, Components::TextDrawable("", Components::Positions(pos.x * 0.5, pos.y * 0.5), 20, BLUE));
}