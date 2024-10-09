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

extern "C" void onStart(jgame::Client &client)
{
    client.connect("localhost", 1234);
    client.sendToServer(jgo::Builder(jgo::enums::FromClient::Connect));

    /// FIXME: hardcoded
    // Game::CreateBackGround(client.ecs);
    // Game::CreatePlanet(client.ecs);
    Game::CreatPlayer(client.ecs, client.window.width, client.window.heigth);

    // test
    // auto &drawables = client.ecs.getComp<Controllable>();
    // for (int n = 0; n < drawables.size(); ++n) {
    //     if (drawables[n].has_value())
    //         std::cout << n << std::endl;
    // }
    // int n = 0;
    // for (auto const &e : drawables) {
    //     std::cout << n << std::endl;
    //     n++;
    //     std::cout << "hell" << std::endl;
    // }
}

template <typename T>
static void retrieveSomething(jgame::Client &client, jgo::Builder &builder)
{
    CBuffer<jgo::u8> buf(sizeof(T));
    jgo::s8 num;

    for (std::size_t n = 0; not builder.empty(); ++n) {
        std::cout << "zizi" << std::endl;
        if (n >= client.ecs.entityNbr())
            client.ecs.creatEntity();
        std::cout << "zozo" << std::endl;
        builder.restore<jgo::s8>(num);
        if (num == -1)
            continue;
        std::cout << "bachibouzouk" << std::endl;
        buf.fill(builder.toBytes().data());
        builder.popFront(sizeof(T));
        std::cout << "foo" << std::endl;
        client.ecs.emplace_comp(n, buf.cast<T>());
        std::cout << "ban" << std::endl;
    }
}

extern "C" void onServerMessage(jgame::Client &client, std::string const &msg)
{
    jgo::Builder builder = jgo::Builder::fromString(msg);

    switch (jgo::enums::FromServer(msg[0])) {

        case jgo::enums::Apply:
            /// FIXME: hardcoded
            jgo::enums::Components op;

            builder.restore<jgo::u8>(op);

            std::cout << std::hex;
            for (auto const &e : builder.toBytes())
                std::cout << int(e) << " ";
            std::cout << std::dec << std::endl;

            if (op == jgo::enums::Components::Position)
                retrieveSomething<Positions>(client, builder);
            else if (op == jgo::enums::Components::Drawable) {
                retrieveSomething<Drawable>(client, builder);
            }
            break;

        default:
            return;
    }
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
