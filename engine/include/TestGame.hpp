/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** TestGame
*/

#pragma once
#include "Register.hpp"
#include "Components.hpp"
#include "Game.hpp"

class TestGame {
    public:
        /**
         * @brief Construct a new Test Game object
         * 
         * @param reset The reset Time for the creation
         */
        TestGame(float reset);
        ~TestGame();
        /**
         * @brief Generation of random Entity
         * 
         * @param r The Registry
         * @param time The current time
         * @param currentEntity The total of entity nbr
         * @param textures The list of all the Texture
         */
        void Stages(Register &r, float time, std::size_t);
    private:
        float _reset;
        float _time;
};
