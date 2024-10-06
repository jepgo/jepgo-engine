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
    client.sendToServer(jgo::Builder(jgo::enums::FromClient::Connect));

    /// FIXME: hardcoded
    Game::CreateBackGround(client.ecs);
    Game::CreatePlanet(client.ecs);
    Game::CreatPlayer(client.ecs, client.window.width, client.window.heigth);
}

extern "C" void onServerMessage(jgame::Client &client, std::string const &msg)
{
    std::cout << "i received a message: " << msg << std::endl;
}

extern "C" void onUpdate(jgame::Client &client)
{
    Vector2 vec = client.getDirection();

    // send the arrows positions
    client.sendToServer(jgo::Builder(jgo::enums::FromClient::Arrows)
        << jgo::u8(int(vec.x)) << jgo::u8(int(vec.y))
    );
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
    client.getAllTextures({
        "sprites/r-typesheet3.gif",
        "sprites/r-typesheet1.gif",
        "sprites/r-typesheet2.gif",
        "sprites/parallax-space-backgound.png",
        "sprites/parallax-space-big-planet.png",
        "sprites/r-typesheet32.gif",
        "sprites/r-typesheet14.gif"
    });
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
