/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Client
*/

#include <iostream>

#include "Client.hpp"
#include "jepmod/external/external.hpp"

using namespace jgame;

auto Client::connect(std::string ip, asio::ip::port port) -> void
{
    if (ip == "localhost")
        ip = "127.0.0.1";
    _udp.emplace(ip, port, _service);
}

auto Client::getDirection(void) const -> Vector2
{
    return {
        static_cast<float>(
            static_cast<int>(IsKeyDown(KEY_RIGHT)) -
            static_cast<int>(IsKeyDown(KEY_LEFT))
        ),
        static_cast<float>(
            static_cast<int>(IsKeyDown(KEY_DOWN)) -
            static_cast<int>(IsKeyDown(KEY_UP))
        )
    };
}

auto Client::useExternal(std::string const &str) -> void
{
    std::string soPath = jgame::generateClientModule(argv[0], str);

    _loader.emplace(soPath);
    _loader->getFunc<void, jgame::Client *, void *>("builder")(
        this, &this->ecs
    );
}

auto Client::getExternalComponent(std::string const &msg) -> bool
{
    if (msg[0] != jgo::enums::FromServer::ApplyExternal)
        return false;

    jgo::Builder builder = jgo::Builder::fromString(msg);
    _loader->getFunc<void, jgame::Client *, jgo::Builder &>("receiver")(
        this, builder
    );
    return true;
}
