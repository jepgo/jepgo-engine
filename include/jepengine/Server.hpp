/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Server
*/

#pragma once

#include <vector>
#include <any>
#include <optional>
#include <map>
#include <string>
#include "Game.hpp"

namespace jgo {

    /**
     * A Connection is basically a Node that corrrespond to a client.
     */
    class Connection {
        public:
            /**
             * Create a new connection.
             * 
             * Takes the ip and the port.
             * `Connection("127.0.0.1", 1234);`
             */
            Connection(std::string const &ip, u16 port)
            : _key(ip + std::to_string(static_cast<int>(port))) {
                return;
            }

            /**
             * Some internal storage for the connection.
             */
            std::map<std::string, std::optional<std::any>> storage;

            /**
             * Get the connection key
             */
            inline auto getKey(void) const noexcept -> std::string {
                return _key;
            }
        private:
            std::string _key;
    };

    /**
     * A Server is a game that can receive data from multiple clients and
     * broadcast to all the clients.
     */
    class Server: public Game {
        public:
            Server() = default;
            ~Server() = default;

            /**
             * Requires `loadNetwork()`.
             * 
             * Send something to all clients.
             */
            auto sendToAll(std::vector<u8> const &data) -> bool;

            /**
             * Requires `loadNetwork()`.
             * 
             * Host a server.
             */
            auto host(u16 port) -> bool;

            /**
             * Requires `loadNetwork()`.
             * 
             * Send components the all clients.
             */
            auto sendComponents(void) -> bool;
            
    };
}