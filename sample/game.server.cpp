/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** game.client
*/

#include <iostream>
#include <chrono>
#include <thread>

#include "jepgame/gamemaker/Server.hpp"
#include "jepgame/gamemaker/hardcoded.hpp"
#include "jepgame/service/Components.hpp"

extern "C" void onStart(jgame::Server &server)
{
    server.host(1234);
    // server.settings.frequency = 10;
}

static void updatePosition
(jgame::Server &server, Vector2 const &dir, std::size_t id)
{
    auto &control = server.ecs.getComp<Controllable>();
    auto &vel = server.ecs.getComp<Velocity>();
    auto &pos = server.ecs.getComp<Positions>();

    // check if he can move his ship
    if (not vel[id] or not control[id] or not pos[id])
        return;
    
    // set the velocity and move
    // std::cout << "set move to " << id << std::endl;
    vel[id].value().setVel(dir);
    server.ecs.emplace_comp(id, Move(vel[id].value().getVel()));
}

extern "C" void onClientMessage
(jgame::Server &server, std::string const &msg, jgo::Connection &client)
{
    jgo::Builder builder = jgo::Builder::fromString(msg);

    switch (jgo::enums::FromClient(msg[0])) {

        case jgo::enums::Connect:
            /// FIXME: hardcoded
            Game::CreatPlayer(server.ecs, 800, 600);
            client.storage["id"] = server.ecs.currentEntity;
            break;

        case jgo::enums::Arrows:
            Vector2 direction;

            builder.restore<jgo::s8>(direction.x)
                .restore<jgo::s8>(direction.y);
            // std::cout << direction.x << ", " << direction.y << std::endl;
            updatePosition(server, direction,
                std::any_cast<int>(client.storage["id"]));
            break;

        default:
            return;
    }
    // ...
}

template <typename T>
static jgo::Builder generateTypeToSend
(jgame::Server &server, jgo::enums::Components c)
{
    jgo::Builder build(jgo::enums::FromServer::Apply);
    auto &elements = server.ecs.getComp<T>();
    CBuffer<jgo::u8> buf(sizeof(T));

    build << static_cast<jgo::u8>(c);
    for (std::size_t n = 0; n < elements.size(); ++n) {
        if (not elements[n]) {
            build << static_cast<jgo::u8>(-1);
            continue;
        }
        build << static_cast<jgo::u8>(0);
        buf.fill(&elements[n].value());
        for (jgo::u8 byte : buf.toBytes()) {
            build << byte;
        }
    }
    return build;
}

extern "C" void onUpdate(jgame::Server &server)
{
    /// FIXME: hardcoded
    jgo::Builder build(0);

    if (float(ClockPP()) - server.getTime() < .01)
        return;
    server.updateTime();


    build = generateTypeToSend<Positions>(
        server,
        jgo::enums::Components::Position
    );
    std::cout << std::hex;
    for (jgo::u8 b : build.toBytes())
        std::cout << int(b) << " ";
    std::cout << std::dec << std::endl;
    server.sendToAll(build);


    build = generateTypeToSend<Drawable>(
        server,
        jgo::enums::Components::Drawable
    );
    std::cout << std::hex;
    for (jgo::u8 b : build.toBytes())
        std::cout << int(b) << " ";
    std::cout << std::dec << std::endl;
    server.sendToAll(build);
}

// this part will be hiden later
int main(int argc, char const *argv[])
{
    jgame::Server server(argc, argv);

    onStart(server);
    if (not server.compile())
        return 84;
    while (true) {
        // server.updateTime();
        std::this_thread::sleep_for(
            std::chrono::milliseconds(server.settings.frequency)
        );
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
