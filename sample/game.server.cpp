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
}

extern "C" void onClientMessage
(jgame::Server &server, std::string const &msg, jgo::Connection &client)
{
    jgo::Builder builder = jgo::Builder::fromString(msg);

    builder.popFront(1);
    switch (jgo::enums::FromClient(msg[0])) {

        case jgo::enums::Connect:
            /// FIXME: hardcoded
            Game::CreatPlayer(server.ecs, 600, 800);
            server.sendToAll("a new client connected !");
            break;

        case jgo::enums::Arrows:
            int nums[2];

            builder.restore<jgo::u8>(nums[0])
                .restore<jgo::u8>(nums[1]);
            std::cout << nums[0] << ", " << nums[1] << std::endl;
            break;

        default:
            return;
    }
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
        jgame::hardcodedSystems(server);
        for (auto &yap : server.getYapers()) {
            auto [msg, who] = yap.get().getMessage();
            onClientMessage(server, msg, yap.get());
        }
    }
    server.sendToAll("im dying");
    return 0;
}
