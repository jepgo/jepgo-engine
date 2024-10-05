/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** game.client
*/

#include <iostream>
#include "jepgame/gamemaker/Server.hpp"
#include "jepgame/gamemaker/hardcoded.hpp"

extern "C" void onStart(jgame::Server &server)
{
    server.host(1234);

    // ...
}

extern "C" void onClientMessage(jgame::Server &server, std::string const &msg)
{
    std::cout << "i received a message: " << msg << std::endl;
    if (msg == "hello server")
        server.sendToAll("a new client connected !");

    // ...
}

extern "C" void onUpdate(jgame::Server &server)
{
    // ...
}

// this part will be hiden later
int main(int argc, char const *argv[])
{
    jgame::Server server(argc, argv);

    onStart(server);
    if (not server.compile())
        return 84;
    while (true) {
        server.updateTime();
        onUpdate(server);
        // jgame::hardcodedSystems(server);
        for (auto &yap : server.getYapers()) {
            auto [msg, _] = yap.get().getMessage();
            onClientMessage(server, msg);
        }
    }
    server.sendToAll("im dying");
    return 0;
}
