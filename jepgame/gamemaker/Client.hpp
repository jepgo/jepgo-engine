/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Client
*/

#pragma once

#include <string>
#include <optional>

#include "jepgame/service/Asio.hpp"
#include "jepgame/service/UDP.hpp"
#include "engine/engine.hpp"

namespace jgame {
    class Client {
        public:
            inline Client(void) {
                return;
            }
            inline Client(int ac, char const *av[]): argv(av + 1, av + ac) {
                return;
            }
            inline ~Client() {
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
            auto connect(std::string ip, asio::ip::port port) -> void;
            auto getDirection(void) const -> Vector2;

            Register ecs;
            std::vector<std::string> const argv;
            struct {
                unsigned int width = 800;
                unsigned int heigth = 600;
                std::string name = "Can you consider giving me a name ?";
            } window;

        private:
            struct {
                float start = 0.f;
                float current = 0.f;
            } _time;
            asio::io_service _service;
            std::optional<jgo::UDP> _udp;
    };
}

