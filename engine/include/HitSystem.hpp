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
        static bool compareHitable(std::map<std::size_t, Hitable*> &list, Hitable &me, Positions &m, SparseArray<Positions> &pos, std::size_t ind);
        void system(Register &r, std::vector<sf::Texture> &texture);
    protected:
    private:
};