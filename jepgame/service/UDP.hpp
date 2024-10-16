/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Server
*/

#pragma once

#include <mutex>
#include <functional>

#include "Asio.hpp"
#include "Connections.hpp"

namespace jgo {
    class UDP {
        public:
            using CustomCallback =
                std::function<std::string(jgo::Connection &)>;

            UDP(asio::ip::port port, asio::io_service &service);
            UDP(std::string const &addr,
                asio::ip::port port, asio::io_service &service);

            auto listen(void) -> void;
            auto send(std::string const &s) -> void;
            auto sendToAll(std::string const &s) -> void;
            auto sendToAllCustom(CustomCallback callback) -> void;
            auto getFirstClient(void) -> std::optional<jgo::ConnectionRef> {
                if (_pool.getEveryone().empty())
                    return std::nullopt;
                return _pool.getEveryone()[0];
            }

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
