/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Server
*/

#pragma once

#include <string>
#include <optional>

#include "jepgame/service/UDPBase.hpp"
#include "engine/engine.hpp"

namespace jgame {
    class Server: public jgo::UDPBase {
        public:
            inline Server(void) {
                return;
            }
            inline Server(int ac, char const *av[]): UDPBase(ac, av) {
                return;
            }
            inline auto sendToAll(std::string const &str) -> void {
                _udp->sendToAll(str);
            }
            inline auto sentToAll(jgo::Builder const &builder) -> void {
                _udp->sendToAll(builder.toString());
            }
            auto host(asio::ip::port port) -> void;

            Register ecs;
            std::vector<std::string> const argv;
    };
}
