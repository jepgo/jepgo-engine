/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Client
*/

#include "Client.hpp"

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
