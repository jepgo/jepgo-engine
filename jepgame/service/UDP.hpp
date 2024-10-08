/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Server
*/

#pragma once

#include <mutex>

#include "Asio.hpp"
#include "Connections.hpp"

namespace jgo {
    class UDP {
        public:
            UDP(asio::ip::port port, asio::io_service &service);
            UDP(std::string const &addr,
                asio::ip::port port, asio::io_service &service);

            auto listen(void) -> void;
            auto send(std::string const &s) -> void;
            auto sendToAll(std::string const &s) -> void;

            inline auto getYapers(void) -> std::vector<jgo::ConnectionRef> {
                return _pool.getYapers();
            }

        private:
            auto _handleReceive(void) -> void;
            std::mutex _mutex;
            jgo::ConnectionPool _pool;
            asio::ip::port _port;
            udp::endpoint _endpoint;
            udp::socket _socket;
    };
}
