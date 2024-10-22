/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Game
*/

#pragma once

#include <string>
#include <cstdint>
#include "jepmod/Clock++.hpp"
#include "jepmod/DLLoader.hpp"
#include "jepengine/Register.hpp"

namespace jgo {

    using u8 = std::uint8_t;
    using s8 = std::int8_t;
    using u16 = std::uint16_t;
    using s16 = std::int16_t;
    using u32 = std::uint32_t;
    using s32 = std::int32_t;
    using u64 = std::uint64_t;
    using s64 = std::int64_t;

    /**
     * A Rectangle that have x, y width and height.
     */
    struct Rectangle {
        int x;
        int y;
        int width;
        int height;
    };

    /**
     * Just a vector with 3 float positions.
     */
    struct Vector3 {
        float x, y, z;
    };

    /**
     * Same as rectangle, but in 3D so it have a pos and size.
     */
    struct HitBox {
        Vector3 pos;
        Vector3 size;
    };

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
            auto useComponent(std::string const &name) -> bool;

            /**
             * Get the time from the beginning of the game.
             */
            auto getTime(void) -> float;

            /**
             * Requires `loadGraphic()`.
             * 
             * Draw something on the graphic library.
             * Example: `drawSomething("assets/foo.png", {0, 0, 100, 100});`
             */
            auto drawSomething(std::string const &, Rectangle const &);

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
             * The dynamic libraries map.
             */
            std::map<std::string, std::optional<jmod::DLLoader>> _libs;
    };
}
