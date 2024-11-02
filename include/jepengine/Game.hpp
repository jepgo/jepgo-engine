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
#include <map>
#include <any>
#include "jepmaker/graphic/IGraphic.hpp"
#include "jepmod/EasyLife.hpp"
#include "jepmod/Clock++.hpp"
#include "jepmod/DLLoader.hpp"
#include "jepengine/Register.hpp"
#include "jeplua/Lua.hpp"
#include "jepengine/exceptions.hpp"

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
             * Load a graphic module.
             * 
             * `game.loadGraphic("raylib");`
             */
            auto loadGraphic(std::string const &name) -> void;

            /**
             * Load Lua.
             * 
             * `game.loadLua();`
             */
            auto loadLua(void) -> void {
                lua.emplace(jmod::EasyLife()/"sharedlua", ecs);
            }

            /**
             * Access lua
             */
            std::optional<jgo::LuaHelper> lua = std::nullopt;

            /**
             * Use a component from a .hpp and .so file.
             * 
             * `game.useComponent("health");`
             */
            template <typename T>
            auto useComponent(std::string const &sys = "", int prio = 0) -> void {
                if (not sys.empty())
                    useSystem(sys, prio);
                this->ecs.runTimeInsert<T>();
                this->ecs.addRule([](Register::RuleMap &r) {
                    std::any_cast<SparseArray<T>&>(r[std::type_index(typeid(T))]).add();
                });
                if constexpr (lua::LuaFriend<T>) /* and */ if (lua)
                    lua->applyComponent<T>();
            }

            /**
             * A function for using a system.
             */
            auto useSystem(std::string const &sys, int prio = 0) -> void {
                try {
                    _systems.emplace(_ComponentKey(sys, prio), std::make_pair(
                        std::make_shared<jmod::DLLoader>(
                            jmod::EasyLife()/"jepgo.system." + sys
                        ),
                        getTime()
                    ));
                } catch (jgo::errors::DLError const &e) {
                    _systems.emplace(_ComponentKey(sys, prio), std::make_pair(
                        std::make_shared<jmod::DLLoader>(
                            jmod::EasyLife(argv[0])/"jepgo.system." + sys
                        ),
                        getTime()
                    ));
                }
            }

            /**
             * Call all systems.
             */
            auto callSystems(void) -> void;

            /**
             * Get the time from the beginning of the game.
             */
            auto getTime(void) -> double;

            /**
             * Get the graphic lib (throw if not exists)
             */
            inline auto getGraphicLib(void) ->
                jgo::ptr<jgo::IGraphic> & {
                if (not _graphicLib)
                    throw jgo::errors::NoGraphic();
                return *_graphicLib;
            }

            /**
             * Returns true if you have a graphic lib.
             */
            inline auto hasGraphicLib(void) const noexcept -> bool {
                return static_cast<bool>(_graphicLib);
            }

            /**
             * The engine manager for components.
             */
            Register ecs;

            /**
             * The argument vector (input given).
             */
            std::vector<std::string> const argv;

            /**
             * The internal storage (if you wanna store stuff)
             */
            std::map<std::string, std::any> storage;

        private:
            /**
             * The time structure.
             */
            jmod::ClockPP _clock;

            /**
             * The graphic library (if any)
             */
            std::optional<jgo::ptr<jgo::IGraphic>> _graphicLib;

            /**
             * The component key so that i can sort by priority.
             */
            struct _ComponentKey {
                _ComponentKey(std::string const &str, int i): str(str), prio(i) {
                    return;
                }
                std::string str;
                int prio;
                auto inline operator<(_ComponentKey const &other) const -> bool {
                    return prio < other.prio;
                }
            };

            /**
             * The components.
             */
            std::multimap<_ComponentKey, std::pair<jmod::DLLoaderPtr, float>> _systems;
    };
}
