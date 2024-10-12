/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game
*/

#ifndef GAME_HPP_
    #define GAME_HPP_
    #include <map>
    #include <string>
    #include "Register.hpp"
    #include "Position.hpp"

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
            /**
             * @brief Create a Background object
             * 
             * @param r The Register object
             */
            static void createBackground(Register &r);

            /**
             * @brief Create a Mole object
             * 
             * @param r The Register object
             * @param pos The Positions object
             * @param time The time
             */
            static void createMole(
                Register &r,
                Components::Positions &&pos
            );
        private:
            enum MoleStates {
                SLEEP,
                WAKE_UP,
                ATTACK,
                DEAD,
                SPAWN_BOMB,
                LEAVE,
            };
    };
}

#endif /* !GAME_HPP_ */
