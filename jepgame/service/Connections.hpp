/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Connections
*/

#pragma once

#include <optional>
#include <vector>
#include <string>
#include <queue>
#include <functional>

#include "Asio.hpp"

using asio::ip::udp;

namespace jgo {
    class Connection {
        public:
            Connection(asio::ip::address const &addr, asio::ip::port port);

            inline explicit operator bool(void) const {
                return not _queue.empty();
            }

            inline auto operator==(std::string const &other) const -> bool {
                return _ip == other;
            }

            inline void feed(std::string const &more) {
                _queue.push(more);
            }

            inline udp::endpoint &getEndpoint(void) {
                return _end;
            }

            auto getMessage(void) -> jgo::Reply;
            static std::string makeIP(asio::ip::address const &addr, asio::ip::port port);

        private:
            std::string _ip;
            std::queue<std::string> _queue;
            udp::endpoint _end;
    };

    using ConnectionRef = std::reference_wrapper<Connection>;    

    class ConnectionPool {
        public:
            ConnectionPool() = default;
            void feed(udp::endpoint const &, asio::ip::cppBuffer const &, std::size_t);
            auto getYapers(void) -> std::vector<ConnectionRef>;

            inline auto getEveryone(void) -> std::vector<Connection> & {
                return _connections;
            }

        private:
            std::optional<ConnectionRef> _findConnection(
                asio::ip::address const &,
                asio::ip::port
            );
            std::vector<Connection> _connections;
            std::optional<std::size_t> _limit;
    };
}
