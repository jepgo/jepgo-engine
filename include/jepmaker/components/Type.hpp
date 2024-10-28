/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Type
*/

#pragma once

enum TYPE {
    BOMB,
    SHIPSHOOT,
    CONTRO,
    COLISION,
    MODULE,
    MODULE_ARM,
    MINIBOSS,
    NEUTRAL,
};

class Type {
    public:
        Type(TYPE type) : _type(type) {};
        ~Type() {};
        TYPE &getType() {return _type;};
        private:
            TYPE _type;
};