/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** SpriteAnimation
*/

#pragma once
#include <optional>

class Sprite_Animation {
public:
    /**
     * @brief Construct a new Sprite_Animation object
     *
     * @param sta The number of Status for the Sprite
     * @param value The value to be increase for the Sprite
     * @param res The time for the Sprite to be reseted
     * @param dead A Bool to know if the Sprite animation need to be delete after the max status
     */
    Sprite_Animation(int sta, int value, double res, std::optional<bool> dead = std::nullopt)
    {
        status = sta;
        if (value < 0)
            isneg = true;
        else
            isneg = false;
        val = value;
        reset = res;
        t = 0;
        if (dead.has_value())
            deadAnimation = true;
        else
            deadAnimation = false;
    };
    ~Sprite_Animation() {};

    bool isneg;
    int status;
    int val;
    double reset;
    float t;
    bool deadAnimation;
};