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
#include <thread>

#include "Game.hpp"
#include "jepmod/CBuf.hpp"
#include "jepmaker/network/INetwork.hpp"

namespace jgo {

    /**
     * A Server is a game that can receive data from multiple clients and
     * broadcast to all the clients.
     */
    class Server: public Game {
        public:
            Server(int ac, char const *const av[]): Game(ac, av) {
                return;
            }
            ~Server() = default;

            /**
             * Load a network library server.
             */
            auto loadNetworkServer(std::string const &lib) -> void;

            /**
             * Check if you have network.
             */
            auto hasNetwork(void) -> bool {
                return static_cast<bool>(_server);
            }

            /**
             * Requires `loadNetwork()`.
             * 
             * Send something to all clients.
             */
            auto sendToAll(std::vector<u8> const &data) -> bool {
                _server->get()->sendToAll(data);
                return true;
            }

            /**
             * Requires `loadNetwork()`.
             * 
             * Send some string message to all clients.
             */
            auto sendToAll(std::string const &str) -> bool {
                std::vector<jgo::u8> const vec(str.begin(), str.end());
                _server->get()->sendToAll(vec);
                return true;
            }

            /**
             * Requires `loadNetwork()`.
             * 
             * Host a server.
             */
            auto host(u16 port) -> bool {
                auto &server = _server;

                std::thread t([&server, port]() -> void {
                    server->get()->host(port);
                });
                t.detach();
                return true;
            }

            /**
             * Requires `loadNetwork()`
             * 
             * Get all messages.
             */
            auto getMessages(void) -> std::vector<jgo::NetMessage> {
                return _server->get()->getAllMessages();
            }

            /**
             * Requires `loadNetwork()`.
             * 
             * Send components the all clients.
             */
            template <typename T, jgo::u8 B>
            auto sendComponents(void) -> bool {
                auto &comp = ecs.getComp<T>();
                CBuffer<T> buf;
                std::vector<jgo::u8> vec = { COMPONENT_BYTE, B };
                std::vector<jgo::u8> bytes;

                for (std::size_t n = 0; n < comp.size(); ++n) {
                    if (not comp[n]) {
                        vec.emplace_back(0xff);
                        continue;
                    }
                    vec.emplace_back(0x00);
                    buf.fill(&comp[n].value());
                    bytes = buf.toBytes();
                    vec.insert(vec.end(), bytes.begin(), bytes.end());
                }
                std::cout << "=== foo ===" << std::endl;
                std::cout << vec.size() << std::endl;
                sendToAll(vec);
                return true;
            }

        private:
            /**
             * Your jepgo server.
             */
            std::optional<jgo::ptr<jgo::IServer>> _server;
            
    };
}