/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** game.client
*/

#include <iostream>
#include <chrono>
#include <thread>

#include "jepmaker/components/Position.hpp"
#include "jepengine/Server.hpp"
#include "jepmod/exported.hpp"
#include "Direction.hpp"

void useSystemsAndComponents(jgo::Server &game);

exported(void) onStart(jgo::Server &game)
{
    game.loadNetworkServer("Asio");
    
    useSystemsAndComponents(game);
}

exported(void) onUpdate(jgo::Server &game)
{
    game.sendComponents<Position2D, 0x42>();
    return;
}

exported(void) onMessage(jgo::Server &game, jgo::NetMessage const &msg)
{
    std::cout << "received "
        << std::string(msg.first.cbegin(), msg.first.cend())
        << " from "
        << msg.second->getIP() << ":" << msg.second->getPort()
        << std::endl;
}

int main(int ac, char const *const av[])
{
    jgo::Server game(ac, av);

    onStart(game);
    if (game.hasGraphicLib())
        game.getGraphicLib()->openWindow("my windows", {0, 0, 800, 600});
    if (game.hasNetwork()) game.host(4242);
    while (game.hasGraphicLib() ? game.getGraphicLib()->isWindowOpen() : true) {
        if (game.hasNetwork()) for (auto const &msg : game.getMessages())
                onMessage(game, msg);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        onUpdate(game);
        game.callSystems();
        if (game.hasGraphicLib()) game.getGraphicLib()->update();
        if (game.lua) game.lua->callAllSystems();
    }
    if (game.hasGraphicLib()) game.getGraphicLib()->closeWindow();
}
