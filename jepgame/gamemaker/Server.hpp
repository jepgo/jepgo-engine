/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Server
*/

#pragma once

#include <string>
#include <functional>

#ifdef JEPGO_USE_EXTERNAL
#include <optional>
#include "jepmod/external/external.hpp"
#include "jepmod/DLLoader.hpp"
#endif

#include "jepgame/service/UDP.hpp"
#include "jepgame/service/UDPBase.hpp"
#include "engine/engine.hpp"
#include "jepgame/toolbox/Clock++.hpp"

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
            inline auto sendToAll(jgo::Builder const &builder) -> void {
                _udp->sendToAll(builder.toString());
            }
            auto sendCustom(jgo::UDP::CustomCallback callback) -> void {
                _udp->sendToAllCustom(callback);
            }
            inline void updateTime(void) override {
                _time.current = static_cast<float>(_clock());
            }
            auto host(asio::ip::port port) -> void;

            struct {
                std::size_t frequency = 0;
            } settings;

            /// FIXME: hardcoded
            struct AllSystems {
                AllSystems(void)
                : addDmg(.1), test(1), game(.1), move(.01), moveTo(.3) {
                    return;
                }
                AllSystems(double a, double b, double c, double d, double e)
                : addDmg(a), test(b), game(c), move(d), moveTo(e) {
                    return;
                }
                AddDmgSystem addDmg;
                TestGame test;
                GameSystem game;
                MoveSystem move;
                MoveToPlayerSystem moveTo;
                HitSystem hit;
            } systems;

            Register ecs;

            #ifdef JEPGO_USE_EXTERNAL
            auto useExternal(std::string const &hppFile) -> void {
                std::string soPath = jgame::generateServerModule(hppFile);

                _loader.emplace(soPath);
                // std::remove(soPath.c_str());
            }

            auto sendAllExternals(void) -> void {
                auto f = _loader->getFunc<void, Server &>("entrypoint");
                f(*this);
            }
            #endif

        private:
            #ifdef JEPGO_USE_EXTERNAL
            std::optional<jmod::DLLoader> _loader;
            #endif
            ClockPP _clock;
    };
}
