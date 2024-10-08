/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Server
*/

#include "Server.hpp"

using namespace jgame;

auto Server::host(asio::ip::port port) -> void
{
    _udp.emplace(port, _service);
}
