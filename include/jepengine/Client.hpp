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
#include "jepmod/CBuf.hpp"

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
            auto loadNetworkClient(std::string const &lib) -> void;

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
             * Send a string to the server.
             */
            inline auto sendToServer(std::string const &str) -> void {
                _client->get()->sendToServer(
                    std::vector<jgo::u8>(str.cbegin(), str.cend())
                );
            }

            /**
             * Requires `loadNetwork()`.
             * 
             * Get the latest server message.
             * If none, it should return an empty vector.
             */
            inline auto getServerMessage(void) -> std::vector<jgo::u8> {
                return _client->get()->getMessage();
            }

            /**
             * Requires `loadNetwork()`.
             * 
             * Connect to a server.
             */
            auto connect(std::string const &ip, u16 port) -> void {
                if (ip == "localhost")
                    _client->get()->connect("127.0.0.1", port);
                else
                    _client->get()->connect(ip, port);
            }

            /**
             * Check if you have network.
             */
            auto hasNetwork(void) -> bool {
                return static_cast<bool>(_client);
            }

            /**
             * Requires `loadNetwork()`.
             * 
             * Receive components the server sent.
             */
            template <typename T, jgo::u8 B>
            auto maybeTreatComponent(std::vector<u8> data) -> bool {
                CBuffer<T> buf;

                if (data[0] != COMPONENT_BYTE)
                    return false;
                data.erase(data.begin());

                if (data.front() != B)
                    return false;
                data.erase(data.begin());

                for (int n = 0; data.size() > 0; ++n) {
                    if (data.front() == 0xff) {
                        data.erase(data.begin());
                        ++n;
                        continue;
                    } else if (data.front() != 0x00)
                        throw std::runtime_error("invalid format error");
                    data.erase(data.begin());
                    buf.fill(data.data());
                    if (n >= ecs.currentEntity)
                        ecs.createEntity();
                    ecs.emplaceComp<T>(n, *buf);
                    data.erase(data.begin(), data.begin() + sizeof(T));
                }
                return true;
            }

        private:
            /**
             * Your jepgo client.
             */
            std::optional<jgo::ptr<jgo::IClient>> _client;

    };

}