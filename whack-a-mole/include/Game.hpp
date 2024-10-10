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
             * @param reset The reset
             */
            static void createMole(Register &r, Positions &&pos, float time, float reset);
        private:
    };
}

#endif /* !GAME_HPP_ */
