/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** WhackAMole
*/


#include "Game.hpp"
#include "Global.hpp"
#include "WhackAMole.hpp"
#include "Sprite2DMultiAnim.hpp"

WhackAMole::WhackAMole::WhackAMole()
{
    _textures.reserve(TEXTURES_PATH.size());

    for (const auto &path : TEXTURES_PATH) {
        _textures.push_back(LoadTexture(path.second.c_str()));
    }
}

void WhackAMole::WhackAMole::start()
{
    Game::createBackground(_r);
    float startTime = GetTime();

    for (std::size_t y = 0; y < 4; y++) {
        for (std::size_t x = 0; x < 7; x++) {
            Game::createMole(_r, Components::Positions(110 + (200) * x, 400 + (200) * y));
        }
    }

    while (!WindowShouldClose()) {
        float time = GetTime() - startTime;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        Game::setWhack(_r);
        Game::setStateMole(_r);
        _animSys.system(_r, time);
        _drawSys.system(_r, _textures);
        
        EndDrawing();
    }
}