/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** MessageTime
*/

#pragma once

class MessageTime {
    public:
        MessageTime(float time, float reset) : _time(time), _reset(reset) {};
        ~MessageTime() {};
        float &getTime() {return _time;};
        float &getReset() {return _reset;};
    private:
        float _time;
        float _reset;
};