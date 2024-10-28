/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** MoveToPlayerTime
*/

#pragma once

class MoveToPlayerTime {
    public:
        MoveToPlayerTime(float time, float reset) : _time(time), _reset(reset) {};
        ~MoveToPlayerTime() {};
        float _time;
        float _reset;
};