/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Reborn
*/

#pragma once
#include <string>

class Reborn {
    public:
        Reborn(std::size_t live) : _live(live) {};
        ~Reborn() {};
        std::size_t &getLive() {return _live;};
    private:
        std::size_t _live;
};