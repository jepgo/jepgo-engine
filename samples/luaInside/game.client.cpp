/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** a
*/

#include <iostream>
#include <chrono>
#include <thread>

#include "jepengine/Client.hpp"
#include "jepmaker/components/Health.hpp"
#include "jepmaker/components/Poison.hpp"
#include "jepmod/exported.hpp"
#include "Color.hpp"

exported(void) onStart(jgo::Client &game)
{
    game.loadLua();
    game.loadGraphic("Raylib");

    game.lua->dostring("print('hello, jepgo !')");
    game.lua->useSystem("coco");
    game.useComponent<Color>();
}

exported(void) onUpdate(jgo::Client &game)
{
    return;
}

int main(int ac, char const *const av[])
{
    jgo::Client game(ac, av);

    onStart(game);
    if (game.hasGraphicLib()) game.getGraphicLib()->openWindow(
        "my windows", {0, 0, 800, 600});
    while (game.hasGraphicLib() ? game.getGraphicLib()->isWindowOpen() : true) {
        onUpdate(game);
        if (game.hasGraphicLib()) game.getGraphicLib()->update();
        game.callSystems();
        if (game.lua) game.lua->callAllSystems();
    }
    if (game.hasGraphicLib()) game.getGraphicLib()->closeWindow();
}
