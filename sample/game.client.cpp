/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** game.client
*/

#include <iostream>
#include "jepgame/gamemaker/Client.hpp"
#include "jepgame/gamemaker/hardcoded.hpp"

extern "C" void onStart(jgame::Client &client)
{
    client.connect("localhost", 1234);
    client.sendToServer("hello server");

    // ...
}

extern "C" void onServerMessage(jgame::Client &client, std::string const &msg)
{
    std::cout << "i received a message: " << msg << std::endl;

    // ...
}

extern "C" void onUpdate(jgame::Client &client)
{
    // ...
}

// this part will be hiden later
int main(int argc, char const *argv[])
{
    jgame::Client client(argc, argv);

    onStart(client);
    if (not client.compile())
        return 84;
    InitWindow(client.window.width, client.window.heigth,
        client.window.name.c_str());
    InitAudioDevice();
    while (not WindowShouldClose()) {
        client.updateTime();
        onUpdate(client);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        jgame::hardcodedSystems(client);
        for (auto &yap : client.getYapers()) {
            auto [msg, _] = yap.get().getMessage();
            onServerMessage(client, msg);
        }
        EndDrawing();
    }
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
