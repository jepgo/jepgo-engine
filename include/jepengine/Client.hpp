/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Client
*/

#pragma once

#include <vector>
#include <optional>
#include <memory>
#include "Game.hpp"
#include "jepmaker/network/INetwork.hpp"

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
             * Load a network library.
             */
            auto loadNetworkClient(std::string const &lib);

            /**
             * Requires `loadNetwork()`.
             * 
             * Send something to server.
             */
            inline auto sendToServer(std::vector<u8> const &data) -> void {
                _client->get()->sendToServer(data);
            }

            /**
             * Requires `loadNetwork()`.
             * 
             * Connect to a server.
             */
            auto connect(std::string const &ip, u16 port) -> void {
                _client->get()->connect(ip, port);
            }

            /**
             * Requires `loadNetwork()`.
             * 
             * Receive components the server sent.
             */
            template <typename T, jgo::u8 byte>
            auto maybeTreatComponent(std::vector<u8> data) -> bool {
                data = std::vector(data.begin() + MAGIC_START.size(), data.end());
                if (data[0] != COMPONENT_BYTE)
                    return false;
                data.erase(data.begin());

                std::size_t n;
                while (std::string(reinterpret_cast<char const *>(data.data())).substr(0, MAGIC_END.length()) == MAGIC_END) {
                    data.erase(data.begin(), data.begin() + sizeof(T));
                    ++n;
                }
                std::cout << n << std::endl;
                return true;
            }

        private:
            /**
             * Your jepgo client.
             */
            std::optional<std::shared_ptr<jgo::IClient>> _client;

    };

}