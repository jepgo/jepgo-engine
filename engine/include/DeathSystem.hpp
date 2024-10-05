/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** DeathSystem
*/

#pragma once
#include "Components.hpp"
#include "Register.hpp"
#include "Game.hpp"

class DeathSystem {
    public:
        static void death(Register &r, std::size_t entity);
        /**
         * @brief The death System for all the Obj
         * 
         * @param r The Registry of all the Entity
         * @param player The data about a player
         */
        static void system(Register &r, std::size_t playerEntity);
        static void ControlDeath(Register &r, std::size_t entity);
        static void ModulesDeath(Register &r, std::size_t entity);
    private:
};
