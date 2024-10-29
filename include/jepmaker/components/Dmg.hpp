/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Dmg
*/

#pragma once
#include <string>

class Dmg {
    public:
        /**
         * @brief Construct a new Dmg object (ephemeral component)
         * 
         * @param dmg The dmg deal
         */
        Dmg(std::size_t dmg) : _dmg(dmg) {};
        ~Dmg() {};
        std::size_t _dmg;
    private:
};