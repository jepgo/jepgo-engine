/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Server
*/

#pragma once

#include <string>
#include <optional>

#include "jepgame/service/Asio.hpp"
#include "jepgame/service/UDP.hpp"
#include "engine/engine.hpp"
#include "jepgame/service/Builder.hpp"

namespace jgame {
    class Server {
        public:
            inline Server(void) {
                return;
            }
            inline Server(int ac, char const *av[]): argv(av + 1, av + ac) {
                return;
            }
            inline ~Server() {
                return;
            }
            inline auto compile(void) -> bool {
                _time.start = GetTime();
                return bool(_udp);
            }
            inline auto getTime(void) const -> float {
                return _time.current;
            }
            inline auto updateTime(void) -> void {
                _time.current = GetTime() - _time.start;
            }
            inline auto sendToAll(std::string const &str) -> void {
                _udp->sendToAll(str);
            }
            inline auto sentToAll(jgo::Builder const &builder) -> void {
                _udp->sendToAll(builder.toString());
            }
            inline auto getYapers() -> std::vector<jgo::ConnectionRef> {
                return _udp->getYapers();
            }
            auto host(asio::ip::port port) -> void;

            Register ecs;
            std::vector<std::string> const argv;

        private:
            struct {
                float start = 0.f;
                float current = 0.f;
            } _time;
            asio::io_service _service;
            std::optional<jgo::UDP> _udp;
    };
}
