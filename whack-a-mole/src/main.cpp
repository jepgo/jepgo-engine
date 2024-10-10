/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <raylib.h>
#include "Global.hpp"
#include "WhackAMole.hpp"

int main(void)
{    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WhackAMole::DEFFAULT_WIDTH, WhackAMole::DEFFAULT_HEIGHT, "whack-a-mole");

    WhackAMole::WhackAMole w;

    SetTargetFPS(200);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        w.start();

        if (!WindowShouldClose())
            EndDrawing();
    }
    CloseWindow();
    return 0;
}