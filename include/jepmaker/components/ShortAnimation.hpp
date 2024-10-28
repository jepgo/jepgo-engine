
/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** ShortAnimation
*/

#pragma once
#include <optional>

class Short_Animation {
public:
    /**
     * @brief Construct a new Sprite_Animation object
     *
     * @param sta The number of Status for the Sprite
     * @param value The value to be increase for the Sprite
     * @param res The time for the Sprite to be reseted
     * @param dead A Bool to know if the Sprite animation need to be delete after the max status
     */
    Short_Animation(int sta, int value, double res, std::optional<std::size_t> start = std::nullopt)
    {
        status = sta;
        if (value < 0)
            isneg = true;
        else
            isneg = false;
        val = value;
        reset = res;
        t = 0;
        if (start.has_value())
            _start = start.value();
        else
            _start = 0;
    };
    ~Short_Animation() {};

    std::size_t getStart() {return _start;};
    bool isneg;
    int status;
    int val;
    double reset;
    std::size_t _start;
    float t;
};
