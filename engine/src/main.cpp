/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <vector>
#include <stddef.h>
#include <raylib.h>
#include <iostream>
#include "Menu.hpp"

int main(void)
{
    size_t screenWidth = 800, screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "rtype");
    InitAudioDevice();
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    Menu::Menu m(screenWidth, screenHeight);

    SetTargetFPS(200);
    while (!WindowShouldClose())
    {
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();
        m.updateSize(screenWidth, screenHeight);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        m.drawMenu();
        EndDrawing();
    }
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
