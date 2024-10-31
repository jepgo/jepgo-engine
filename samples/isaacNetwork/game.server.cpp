/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** game.client
*/

#include <iostream>
#include <chrono>
#include <thread>

#include "jepengine/Server.hpp"
#include "jepmod/exported.hpp"

exported(void) onStart(jgo::Server &game)
{
    game.loadNetworkServer("Asio");
    std::cout << "server has started !" << std::endl;
}

exported(void) onUpdate(jgo::Server &game)
{
    std::cout << "send to them" << std::endl;
    game.sendToAll("howdy clients !");
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
        if (game.hasNetwork())
            for (auto const &msg : game.getMessages())
                onMessage(game, msg);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        onUpdate(game);
        if (game.hasGraphicLib()) game.getGraphicLib()->update();
        game.callSystems();
        if (game.lua) game.lua->callAllSystems();
    }
    if (game.hasGraphicLib()) game.getGraphicLib()->closeWindow();
}
