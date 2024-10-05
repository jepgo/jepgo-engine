/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** UDPBase
*/

#pragma once

#include <vector>
#include <optional>
#include <string>

#include "Builder.hpp"
#include "Asio.hpp"
#include "UDP.hpp"
#include "engine/engine.hpp"

namespace jgo {
    class UDPBase {
        public:
            inline UDPBase(void) {
                return;
            }
            inline UDPBase(int ac, char const *av[]): argv(av + 1, av + ac) {
                return;
            }
            inline auto compile(void) -> bool {
                _time.start = GetTime();
                if (not _udp)
                    return false;
                _udp->listen();
                return true;
            }
            inline auto getTime(void) const -> float {
                return _time.current;
            }
            inline auto updateTime(void) -> void {
                _time.current = GetTime() - _time.start;
            }
            inline auto getYapers() -> std::vector<jgo::ConnectionRef> {
                return _udp->getYapers();
            }
            Register ecs;
            std::vector<std::string> const argv;

        protected:
            asio::io_service _service;
            std::optional<jgo::UDP> _udp;

        private:
            struct {
                float start = 0.f;
                float current = 0.f;
            } _time;
    };
}

