/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Game
*/

#pragma once

#include <string>
#include <cstdint>
#include <optional>
#include "jepmaker/graphic/IGraphic.hpp"
#include "jepmod/EasyLife.hpp"
#include "jepmod/Clock++.hpp"
#include "jepmod/DLLoader.hpp"
#include "jepengine/Register.hpp"

#define onlyOnExistPtr(x) if (x) x->get()

namespace jgo {
    /**
     * A Game is a file structure that can load modules and contains the
     * engine.
     * 
     * It manages the time, the ECS system and the components.
     */
    class Game {
        public:
            /**
             * The game constructor.
             */
            Game(int ac, char const *const av[]);

            /**
             * ## DO NOT CALL
             *
             * Compile your game.
             */
            auto compile(void) -> bool;

            /**
             * Load a network module.
             * 
             * `game.loadNetwork("asio");`
             */
            auto loadNetwork(std::string const &name) -> void;

            /**
             * Load a graphic module.
             * 
             * `game.loadGraphic("raylib");`
             */
            auto loadGraphic(std::string const &name) -> void;

            /**
             * Use a component from a .hpp and .so file.
             * 
             * `game.useComponent("health");`
             */
            template <typename T>
            auto useComponent(std::string const &sys = "") -> void {
                std::string realLib;

                if (not sys.empty()) {
                    realLib = jmod::EasyLife(argv[0])/"jepgo.system." + sys;
                    _systems[sys] = std::make_shared<jmod::DLLoader>(realLib);
                }
                this->ecs.runTimeInsert<T>();
                this->ecs.addRule([](Register::RuleMap &r) {
                    std::any_cast<SparseArray<T>&>(r[std::type_index(typeid(T))]).add();
                });
            }

            /**
             * Call all systems.
             */
            auto callSystems(void) -> void;

            /**
             * Get the time from the beginning of the game.
             */
            auto getTime(void) -> float;

            inline auto getGraphicLib(void) ->
                std::optional<std::unique_ptr<jgo::IGraphic>> & {
                return _graphicLib;
            }

            /**
             * The engine manager for components.
             */
            Register ecs;

            /**
             * The argument vector (input given).
             */
            std::vector<std::string> const argv;

        private:
            /**
             * The time structure.
             */
            jmod::ClockPP _clock;

            /**
             * The graphic library (if any)
             */
            std::optional<std::unique_ptr<jgo::IGraphic>> _graphicLib;

            /**
             * The components.
             */
            std::map<std::string, std::optional<jmod::DLLoaderPtr>> _systems;
    };
}
