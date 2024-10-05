/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** AutoShoot
*/

#pragma once
#include "Components.hpp"

class AutoShoot {
    public:
        AutoShoot(Shoot &&shoot, Type &&type, float time, float reset) : _shoot(shoot), _type(type), _time(time), _reset(reset) {};
        ~AutoShoot() {};
        Shoot &&getShoot() {return std::move(_shoot);};
        Type &&getType() {return std::move(_type);};
        float &getTime() {return _time;};
        float &getReset() {return _reset;};
    private:
        Shoot _shoot;
        Type _type;
        float _time;
        float _reset;
};
