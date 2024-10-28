/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** InvinsibleTime
*/

#pragma once

class InvincibleTime {
    public:
        InvincibleTime(float time, float reset) : _time(time), _reset(reset) {};
        ~InvincibleTime() {};
    float _time;
    float _reset;
};