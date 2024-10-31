/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game
*/

#ifndef GAME_HPP_
    #define GAME_HPP_
    #include <map>
    #include <tuple>
    #include <string>
    #include <raylib.h>
    #include <functional>
    #include "jepengine/Client.hpp"
    #include "jepmod/exported.hpp"
    #include "jepmaker/components/Position.hpp"


/**
 * @brief The namespace of the WhackAMole game
 * 
 */
namespace WhackAMole {
    /**
     * @brief The Game class
     * 
     */
    class Game {
        public:
            static void createBackground(jgo::Client &game);

            static void createMole(jgo::Client &game, Positions &&pos);
        
            enum MoleStates {
                SLEEP,
                WAKE_UP,
                ATTACK,
                IMMORTAL,
                IMMORTAL_WAIT,
                IMMORTAL_LEAVE,
                STOP_IMMORTAL,
                DEAD,
                SPAWN_BOMB,
                BOMB_EXPLOSION,
                LEAVE,
                LEAVE_BOMB,
                WAIT,
                WAIT_BOMB
            };
        private:
        
            static const float WIDTH_MOLE_SPRITE;
            static const float HEIGHT_MOLE_SPRITE;
    };
}

#endif /* !GAME_HPP_ */
