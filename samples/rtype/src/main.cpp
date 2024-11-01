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

int main(void)
{
    size_t screenWidth = 800, screenHeight = 600;
    int ac = 0;
    const char *av[] = {};

    jgo::Client window(ac, av);

    window.loadGraphic("Raylib");
    window.getGraphicLib()->openWindow("R-Type", {0, 0, 800, 600});
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    
    Menu::Menu m(screenWidth, screenHeight, window);

    SetTargetFPS(200);
    while (window.hasGraphicLib() && window.getGraphicLib()->isWindowOpen())
    {
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();
        // m.updateSize(screenWidth, screenHeight);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (m.drawMenu() == 1)
            break;
        EndDrawing();
    }
    return 0;
}