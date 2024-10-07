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
    size_t screenWidth = 1200, screenHeight = 800;
    
    InitWindow(screenWidth, screenHeight, "rtype");
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
    CloseWindow();
    return 0;
}
