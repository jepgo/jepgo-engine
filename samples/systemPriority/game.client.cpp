/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** game.client
*/

#include <iostream>
#include <chrono>
#include <thread>

#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"

exported(void) onStart(jgo::Client &game)
{
    std::cout << "prio has started !" << std::endl;
    game.useSystem("systemA", 3);
    game.useSystem("systemB", 2);
    game.useSystem("systemC", 1);
}

exported(void) onBegin(jgo::Client &game)
{
    return;
}

exported(void) onUpdate(jgo::Client &game)
{
    return;
}

exported(void) onServerMessage(jgo::Client &game, std::vector<jgo::u8> const &msg)
{
    return;
}

int main(int ac, char const *const av[])
{
    jgo::Client game(ac, av);

    onStart(game);
    if (game.hasGraphicLib())
        game.getGraphicLib()->openWindow("my windows", {0, 0, 800, 600});
    if (game.hasNetwork()) game.connect("localhost", 4242);
    onBegin(game);
    while (game.hasGraphicLib() ? game.getGraphicLib()->isWindowOpen() : true) {
        if (game.hasNetwork()) {
            auto const msg = game.getServerMessage();
            if (not msg.empty()) onServerMessage(game, msg);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        onUpdate(game);
        if (game.hasGraphicLib()) game.getGraphicLib()->update();
        game.callSystems();
        if (game.lua) game.lua->callAllSystems();
    }
    if (game.hasGraphicLib()) game.getGraphicLib()->closeWindow();
}
