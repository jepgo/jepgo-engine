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
        float(int(IsKeyDown(KEY_RIGHT)) - int(IsKeyDown(KEY_LEFT))),
        float(int(IsKeyDown(KEY_DOWN)) - int(IsKeyDown(KEY_UP)))
    };
}
