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
#include "jepengine/Client.hpp"

int main(int ac, char const *const av[])
{
    size_t screenWidth = 800, screenHeight = 600;

    // jgo::Client game(ac, av);
    // game.loadGraphic("Raylib");
    // game.getGraphicLib()->openWindow("R-Type", {0, 0, 800, 600});
    
    InitWindow(800, 600, "R-TYPE");
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    
    Menu::Menu m(screenWidth, screenHeight, ac, av);

    SetTargetFPS(200);
    // while (game.hasGraphicLib() && game.getGraphicLib()->isWindowOpen())
    while (not WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (m.drawMenu() == 1)
            break;
        EndDrawing();
    }
    return 0;
}