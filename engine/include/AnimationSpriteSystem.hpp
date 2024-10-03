/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** AnimationSpriteSystem
*/

#pragma once
#include "Register.hpp"
#include "Components.hpp"

class AnimationSpriteSystem {
    public:
        AnimationSpriteSystem();
        ~AnimationSpriteSystem();
        /**
 * @brief Function who check the Sprite Animations
 * 
 * @param r The Registry
 * @param time The current time
 */
void system(Register &r, float time);

    protected:
    private:
};
