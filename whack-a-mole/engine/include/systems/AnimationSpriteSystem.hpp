/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** AnimationSpriteSystem
*/

#pragma once
#include <raylib.h>
#include "Register.hpp"

/**
 * @brief The namespace of all systems
 * 
 */
namespace Systems {

    /**
     * @brief The AnimationSpriteSystem class
     * 
     */
    class AnimationSpriteSystem {
        public:
            /**
             * @brief Construct a new Animation Sprite System object
             * 
             */
            AnimationSpriteSystem();

            /**
             * @brief Destroy the Animation Sprite System object
             * 
             */
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
}
