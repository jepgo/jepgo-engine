/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** DoDmg
*/

#pragma once
#include <string>

class DoDmg {
    public:
        DoDmg(std::size_t dmg) : _dmg(dmg) {};
        ~DoDmg() {};
        std::size_t &getDmg() {return _dmg;};
    private:
        std::size_t _dmg;
};