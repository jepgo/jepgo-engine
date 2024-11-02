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
#include "jepmaker/components/Position.hpp"

exported(void) onStart(jgo::Client &game)
{
    // std::string caca = launchTCP();

    game.loadNetworkClient("Asio");
    // game.loadGraphic("Raylib");
    std::cout << "client has started !" << std::endl;
}

exported(void) onBegin(jgo::Client &game)
{
    game.sendToServer("hello");
}

exported(void) onUpdate(jgo::Client &game)
{
    return;
}

exported(void) onServerMessage(jgo::Client &game, std::vector<jgo::u8> const &msg)
{
    game.maybeTreatComponent<Positions, 0x42>(msg);
    std::cout << "received "
        << msg.size()
        << "bytes"
        << std::endl;
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
            onServerMessage(game, msg);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        onUpdate(game);
        if (game.hasGraphicLib()) game.getGraphicLib()->update();
        game.callSystems();
        if (game.lua) game.lua->callAllSystems();
    }
    if (game.hasGraphicLib()) game.getGraphicLib()->closeWindow();
}
