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
#include "jepmod/exported.hpp"

exported(void) onStart(jgame::Client &client)
{
    client.connect("localhost", 1234);
    client.sendToServer(jgo::Builder(jgo::enums::FromClient::Connect));

    /// FIXME: hardcoded
    // Game::CreateBackGround(client.ecs);
    // Game::CreatePlanet(client.ecs);
    // Game::CreatPlayer(client.ecs, client.window.width, client.window.heigth);

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

    // builder.display();
    for (std::size_t n = 0; not builder.empty(); ++n) {
        if (n >= client.ecs.entityNbr())
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
    jgo::Builder builder = jgo::Builder::fromString(msg);

    builder.display();

    return;

    switch (jgo::enums::FromServer(msg[0])) {

        case jgo::enums::Apply:
            /// FIXME: hardcoded
            jgo::enums::Components op;

            builder.restore<jgo::u8>(op);

            std::cout << client.ecs.entityNbr() << std::endl;

            if (op == jgo::enums::Components::Position)
                retrieveSomething<Positions>(client, builder);
            else if (op == jgo::enums::Components::Drawable)
                retrieveSomething<Drawable>(client, builder);
            break;
        
        case jgo::enums::ApplyExternal:
            std::cout << "receiving externals !" << std::endl;
            break;

        default:
            break;
    }
}

exported(void) onUpdate(jgame::Client &client)
{
    Vector2 vec = client.getDirection();

    // send the arrows positions
    client.sendToServer(jgo::Builder(jgo::enums::FromClient::Arrows)
        << static_cast<jgo::u8>(static_cast<int>(vec.x))
        << static_cast<jgo::u8>(static_cast<int>(vec.y))
    );

    // get positions and drawable
    // auto &a = client.ecs.getComp<Positions>();
    // auto &b = client.ecs.getComp<Drawable>();
    // for (size_t n = 0; n < a.size(); ++n) {
    //     std::cout << n << ": [" << a[n].has_value()
    //         << "] [" << b[n].has_value() << "]" << std::endl;
    // }
    // std::cout << std::endl;
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
