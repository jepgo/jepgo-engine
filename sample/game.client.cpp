/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** game.client
*/

#include <iostream>
#include "jepgame/gamemaker/Client.hpp"
#include "jepgame/gamemaker/hardcoded.hpp"
#include "jepgame/service/Components.hpp"
#include "jepmod/external/external.hpp"
#include "jepmod/exported.hpp"

exported(void) onStart(jgame::Client &client)
{
    client.connect("localhost", 1234);
    client.sendToServer(jgo::Builder(jgo::enums::FromClient::Connect));
    client.useExternal("components/Components.hpp");
    client.settings.use3D = true;
}

template <typename T>
static void retrieveSomething(jgame::Client &client, jgo::Builder &builder)
{
    CBuffer<jgo::u8> buf(sizeof(T));
    jgo::s8 num;

    for (std::size_t n = 0; not builder.empty(); ++n) {
        if (n > client.ecs.entityNbr())
            client.ecs.creatEntity();
        builder.restore<jgo::s8>(num);
        if (num == -1)
            continue;
        buf.fill(builder.toBytes().data());
        client.ecs.emplace_comp(n, buf.cast<T>());
        builder.popFront(sizeof(T));
    }
}

exported(void) onServerMessage(jgame::Client &client, std::string const &msg)
{
    if (client.getExternalComponent(msg))
        return;
}

exported(void) onUpdate(jgame::Client &client)
{
    Vector2 vec = client.getDirection();

    // send the arrows positions
    client.sendToServer(jgo::Builder(jgo::enums::FromClient::Arrows)
        << static_cast<jgo::u8>(static_cast<int>(vec.x))
        << static_cast<jgo::u8>(static_cast<int>(vec.y))
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

    // get the models and stuff
    client.getAllTextures({
        "sprites/r-typesheet3.gif",
        "sprites/r-typesheet1.gif",
        "sprites/r-typesheet2.gif",
        "sprites/parallax-space-backgound.png",
        "sprites/parallax-space-big-planet.png",
        "sprites/r-typesheet32.gif",
        "sprites/r-typesheet14.gif"
    });
    client.getAllModels({
        {"models/model/ship.obj", "models/texture/texture_ship.png"},
        {"models/model/modul_armor.obj", "models/model/modul_armor.png"}
    });

    // initialize 3D
    client.models[0].transform =
        MatrixMultiply(client.models[0].transform, MatrixRotateY(90));
    if (client.settings.use3D)
        client.tools3D.init(client.window.heigth, client.window.width);

    // main loop
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
