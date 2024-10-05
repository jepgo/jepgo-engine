/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Client
*/

#pragma once

#include <string>
#include <optional>

#include "jepgame/service/UDPBase.hpp"

namespace jgame {
    class Client: public jgo::UDPBase {
        public:
            inline Client(void) {
                return;
            }
            inline Client(int ac, char const *av[]): UDPBase(ac, av) {
                return;
            }
            inline auto sendToServer(std::string const &str) -> void {
                _udp->send(str);
            }
            inline auto sentToServer(jgo::Builder const &builder) -> void {
                _udp->send(builder.toString());
            }
            auto connect(std::string ip, asio::ip::port port) -> void;
            auto getDirection(void) const -> Vector2;

            struct {
                unsigned int width = 800;
                unsigned int heigth = 600;
                std::string name = "Can you consider giving me a name ?";
            } window;

    };
}

