/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** WhackAMole
*/

#include "Game.hpp"
#include "Global.hpp"
#include "WhackAMole.hpp"

WhackAMole::WhackAMole::WhackAMole()
{
    _textures.reserve(TEXTURES_PATH.size());

    for (const auto &path : TEXTURES_PATH) {
        _textures.push_back(LoadTexture(path.second.c_str()));
    }
}

WhackAMole::WhackAMole::~WhackAMole()
{
}

void WhackAMole::WhackAMole::start()
{
    Game::createBackground(_r);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        _drawSys.system(_r, _textures);

        EndDrawing();
    }
}