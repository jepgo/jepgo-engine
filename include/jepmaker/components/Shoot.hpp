/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Shoot
*/

#pragma once
#include "jepmaker/components/EnumDirection.hpp"

class Shoot {
public:
    /**
     * @brief Construct a new Shoot object
     * 
     * @param fireRate The time gap between each shot
     * @param dir The direction of the shoot
     * @param decal The decal of the shoot and the obj who are shooting
     */
    Shoot(float fireRate, Direction dir, int decal, std::size_t ind) {
        _time = 0;
    };
    ~Shoot() {};
    /**
     * @brief Verif if the reset time is repected
     * 
     * @param time The current time
     * @return true: The current time respect the reset timer
     * @return false: The curent time not respect the reset timer
     */
    bool verif(float time) {
        if (time - _time >= _fireRate)
        {
            _time = time;
            return true;
        }
        else
            return false;
    };
    float _fireRate;
    float _time;
    std::size_t _ind;
    Direction _direction;
    int _decal;
private:
};