/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Server
*/

#include <string>
#include <iostream>
#include <thread>

#include "UDP.hpp"
#include "engine/engine.hpp"

using namespace jgo;

UDP::UDP(asio::ip::port port, asio::io_service &service)
    : _port(port), _socket(service, udp::endpoint(udp::v4(), _port))
{
}

UDP::UDP(
    std::string const &addr,
    asio::ip::port port,
    asio::io_service &service)
    : _endpoint(asio::ip::address::from_string(addr), port), _socket(service)
{
    _socket.open(udp::v4());
}

auto UDP::listen(void) -> void
{
    std::thread([this]() {
        _handleReceive();
    }).detach();
}

void UDP::_handleReceive(void)
{
    asio::ip::cppBuffer buf;
    std::size_t size;

    try {
        size = this->_socket.receive_from(
            asio::buffer(buf),
            _endpoint
        );
    } catch(std::exception const &e) {
        return;
    }
    _mutex.lock();
    _pool.feed(_endpoint, buf, size);
    _mutex.unlock();
    listen();
}

auto UDP::sendToAll(std::string const &s) -> void
{
    for (auto &e : _pool.getEveryone())
        _socket.send_to(asio::buffer(s), e.getEndpoint());
}

auto UDP::send(std::string const &s) -> void
{
    _socket.send_to(asio::buffer(s), _endpoint);
}
