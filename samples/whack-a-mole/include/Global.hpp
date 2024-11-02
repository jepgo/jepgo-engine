/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Global
*/

#ifndef GLOBAL_HPP_
    #define GLOBAL_HPP_
    #include <map>
    #include <string>
    #include "jepengine/Client.hpp"
    #include "jepmod/exported.hpp"

/**
 * @brief The namespace of the WhackAMole game
 * 
 */
namespace WhackAMole {
    /**
     * @brief The default width and height of the game
     * 
     */
    static const float DEFFAULT_WIDTH = 800;

    /**
     * @brief The default height of the game
     * 
     */
    static const float DEFFAULT_HEIGHT = 600;

    /**
     * @brief The textures indexes of the game
     * 
     */
    enum Textures {
        GAME_BACKGROUND,
        MOLE_SPRITE
    };

    /**
     * @brief The path of the textures
     * 
     */
    const std::map<Textures, std::string> TEXTURES_PATH = {
        {Textures::GAME_BACKGROUND, "./assets/background.png"},
        {Textures::MOLE_SPRITE, "./assets/sprite-mole.png"} 
    };

    const float WIDTH_MOLE_SPRITE = 190.0f;
    const float HEIGHT_MOLE_SPRITE = 144.0f;


    const jgo::Vector2 RECSIZE = {WIDTH_MOLE_SPRITE, HEIGHT_MOLE_SPRITE};

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

    const int NO_RANDOM_GEN = -1;

    const std::map<int, std::vector<jgo::Vector2>> MOLES_ANIM = {
        {(int)MoleStates::SLEEP, {{3, 7}}},
        {(int)MoleStates::WAKE_UP, {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}}},
        {(int)MoleStates::ATTACK, {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {1, 1}, {0, 1}}},
        {(int)MoleStates::DEAD, {{0, 6}, {1, 6}, {2, 6}, {0, 7}, {1, 7}, {2, 7}, {0, 0}}},
        {(int)MoleStates::SPAWN_BOMB, {{0, 0}, {5, 2}, {0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}}},
        {(int)MoleStates::LEAVE_BOMB, {{5, 3}, {4, 3}, {3, 3}, {2, 3}, {1, 3}, {0, 3}, {5, 2}, {0, 0}}},
        {(int)MoleStates::LEAVE, {{4, 0}, {3, 0}, {2, 0}, {1, 0}, {0, 0}}},
        {(int)MoleStates::WAIT, {{4, 0}}},
        {(int)MoleStates::WAIT_BOMB, {{5, 3}}},
        {(int)MoleStates::IMMORTAL_WAIT, {{3, 5}}},
        {(int)MoleStates::IMMORTAL_LEAVE, {{5, 5}, {4, 0}, {3, 0}, {2, 0}, {1, 0}, {0, 0}}},
        {(int)MoleStates::IMMORTAL, {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {0, 5}, {1, 5}, {2, 5}, {3, 5}}},
        {(int)MoleStates::STOP_IMMORTAL, {{4, 5}, {5, 5}, {4, 5}, {5, 0}}},
        {(int)MoleStates::BOMB_EXPLOSION, {{4, 3}, {4, 3}, {4, 3}, {5, 6}, {4, 6}, {3, 6}, {3, 6}, {4, 6}, {5, 6}, {0, 0}}}
    };

}

#endif /* !GLOBAL_HPP_ */
