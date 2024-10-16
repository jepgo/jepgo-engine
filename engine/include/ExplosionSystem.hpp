/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** ExplosionSystem
*/

#pragma once
#include "Register.hpp"
#include "Components.hpp"

class ExplosionSystem {
    public:
        /**
         * @brief The System of the explosion, The goal of this system is to check after colision the Explosion one
         * 
         * @param r The Register of the entities
         */
        static void system(Register &r, std::size_t ind);
    protected:
    private:
};
