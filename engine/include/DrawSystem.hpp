/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** DrawSystem
*/

#pragma once

#include "Register.hpp"
#include "Components.hpp"
#include <SFML/Graphics.hpp>

class DrawSystem {
    public:
        DrawSystem();
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
