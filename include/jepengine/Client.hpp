/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Client
*/

#pragma once

#include <vector>
#include "Game.hpp"

namespace jgo {

    /**
     * A Client is a game that can only send data and reply to one server.
     */
    class Client: public Game {
        public:
            Client(int ac, char const *const av[]): Game(ac, av) {
                return;
            }

            ~Client() = default;

            /**
             * Requires `loadNetwork()`.
             * 
             * Send something to server.
             */
            auto sendToServer(std::vector<u8> const &data) -> bool;

            /**
             * Requires `loadNetwork()`.
             * 
             * Connect to a server.
             */
            auto connect(std::string const &ip, u16 port) -> bool;

            /**
             * Requires `loadNetwork()`.
             * 
             * Receive components the server sent.
             */
            auto receiveComponents(void) -> bool;
            
    };
}