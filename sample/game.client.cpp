/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** game.client
*/

#include "jepgame/gamemaker/Client.hpp"
#include "jepgame/gamemaker/hardcoded.hpp"

extern "C" void start(jgame::Client &client)
{
    client.connect("127.0.0.1", 1234);
    client.window.name = "Hello !";

    // ...
}

extern "C" void update(jgame::Client &client)
{
    // ...
}

int main(int argc, char const *argv[])
{
    jgame::Client client(argc, argv);

    start(client);
    if (not client.compile())
        return 84;
    InitWindow(client.window.width, client.window.heigth,
        client.window.name.c_str());
    InitAudioDevice();
    while (not WindowShouldClose()) {
        update(client);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        jgame::hardcodedSystems(client);
        EndDrawing();
    }
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
