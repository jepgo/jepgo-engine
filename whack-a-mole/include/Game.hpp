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
            static void createMole(Register &r, Components::Positions &&pos);
            
            static void setStateMole(Register &r);

            static void setWhack(Register &r);

            static int randomgen(int min, int max);

            /**
             * @enum MoleStates
             * @brief The states of the mole
             * 
             * @var SLEEP The mole is sleeping
             * @brief The mole is waking up
             * 
             * @var WAKE_UP The mole is waking up
             * @brief The mole is attacking
             * 
             * @var ATTACK The mole is attacking
             * @brief The mole is dead
             * 
             * @var DEAD The mole is dead
             * @brief The mole is spawning a bomb
             * 
             * @var SPAWN_BOMB The mole is spawning a bomb
             * @brief The mole is leaving
             * 
             * @var LEAVE The mole is leaving
             * @brief The mole is sleeping
             * 
             */
            enum MoleStates {
                SLEEP,
                WAKE_UP,
                ATTACK,
                IMMORTAL,
                IMMORTAL_WAIT,
                STOP_IMMORTAL,
                DEAD,
                SPAWN_BOMB,
                LEAVE,
                LEAVE_BOMB,
                WAIT,
                WAIT_BOMB
            };
        private:
            static const float WIDTH_MOLE_SPRITE;
            static const float HEIGHT_MOLE_SPRITE;
        
            static const Vector2 RECSIZE;
        
            static const std::map<int, std::vector<Vector2>> MOLES_ANIM;
    };
}

#endif /* !GAME_HPP_ */
