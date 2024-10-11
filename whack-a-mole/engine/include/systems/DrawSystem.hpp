/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** DrawSystem
*/

#pragma once

#include <raylib.h>
#include "Register.hpp"


/**
 * @brief The namespace of all the systems
 * 
 */
namespace Systems {
    /**
     * @brief The DrawSystem class
     * 
     */
    class DrawSystem {
        public:
            /**
             * @brief Construct a new DrawSystem object
             * 
             */
            DrawSystem();

            /**
             * @brief Destroy the DrawSystem object
             * 
             */
            ~DrawSystem();



            /**
             * @brief The drawable System
             * 
             * @param window The window of the screen
             * @param r The Registry
             * @param texture The list of texture for all the sprite
             */
            void system(Register &r, std::vector<Texture2D> &texture);
        protected:
        private:
    };
}
