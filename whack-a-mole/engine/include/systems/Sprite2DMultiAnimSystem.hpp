/*
** EPITECH PROJECT, 2024
** whack-a-mole
** File description:
** Sprite2DMultiAnimSystem
*/

#ifndef SPRITE2DMULTIANIMSYSTEM_HPP_
    #define SPRITE2DMULTIANIMSYSTEM_HPP_
    #include "Register.hpp"

namespace Systems {

    /**
     * @brief The Sprite2DMultiAnimSystem class
     * 
     */
    class Sprite2DMultiAnimSystem {
        public:
            /**
             * @brief Construct a new Sprite 2 D Multi Anim System object
             * 
             */
            Sprite2DMultiAnimSystem();
        
            /**
             * @brief Destroy the Sprite 2 D Multi Anim System object
             * 
             */
            ~Sprite2DMultiAnimSystem();



            /**
             * @brief Function who check the Sprite Animations
             * 
             * @param r The Registry
             * @param time The current time
             */
            void system(Register &r, float time);
        private:
    };

}

#endif /* !SPRITE2DMULTIANIMSYSTEM_HPP_ */
