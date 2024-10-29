/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** BombGenerationTime
*/

#pragma once

class BombGenerationTime {
    public:
        BombGenerationTime(float time, float during) : _time(time), _during(during) {};
        ~BombGenerationTime() {};
        float getTime() {return _time;};
        float getDuring() {return _during;};
    private:
        float _time;
        float _during;
};