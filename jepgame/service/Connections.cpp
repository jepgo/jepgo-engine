/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Connections
*/

#include <iostream>

#include "Connections.hpp"
#include "UDP.hpp"

// signel connection

jgo::Connection::Connection(asio::ip::address const &a, asio::ip::port p)
: _ip(jgo::Connection::makeIP(a, p)), _end(a, p), _queue(10)
{
    std::cout << "new connection at " << _ip << std::endl;
}

std::string jgo::Connection::makeIP(asio::ip::address const &a, asio::ip::port p)
{
    return a.to_string() + ":" + std::to_string(static_cast<unsigned int>(p));
}

auto jgo::Connection::getMessage(void) -> jgo::Reply
{
    std::string e = _queue.front();

    _queue.pop();
    return {e, _end};
}

// connection pool

void jgo::ConnectionPool::feed(
    udp::endpoint const &ep,
    asio::ip::cppBuffer const &buf,
    std::size_t bytes)
{
    auto maybeConnection = _findConnection(ep.address(), ep.port());
    std::string content(buf.data(), bytes);

    if (maybeConnection) {
        Connection &c = maybeConnection->get();
        c.feed(content);
    } else {
        Connection c(ep.address(), ep.port());
        c.feed(content);
        _connections.push_back(c);
    }
}

std::optional<jgo::ConnectionRef> jgo::ConnectionPool::_findConnection(
    asio::ip::address const &a,
    asio::ip::port p)
{
    std::string ip = jgo::Connection::makeIP(a, p);

    for (jgo::Connection &e : _connections)
        if (e == ip)
            return std::ref(e);
    return std::nullopt;
}

auto jgo::ConnectionPool::getYapers(void) -> std::vector<ConnectionRef>
{
    std::vector<ConnectionRef> res;

    for (Connection &e : _connections)
        if (e)
            res.push_back(std::ref(e));
    return res;
}
