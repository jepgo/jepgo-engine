/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** SoloMoveSystem
*/

#pragma once
#include "Register.hpp"
#include "Components.hpp"

class SoloMoveSystem {
    public:
        /**
         * @brief Construct a new Solo Move System object
         * 
         * @param t The time to be reset
         */
        SoloMoveSystem(float re);
        ~SoloMoveSystem();
        void system(Register &r, sf::Time &time);

    private:
        float _time;
        float _reset;
};
