/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** HitSystem
*/

#pragma once
#include <map>
#include "Register.hpp"
#include "Components.hpp"

class HitSystem {
    public:
        HitSystem();
        ~HitSystem();
        static bool compareHitable(std::map<std::size_t, Hitable*> &list, std::map<size_t, Hitable*>::iterator &me, std::map<size_t, Hitable*>::iterator &where, Positions &m, Positions &him, std::vector<sf::Texture> &texture, Register &re);
        void system(Register &r, std::vector<sf::Texture> &texture);
    protected:
    private:
};
