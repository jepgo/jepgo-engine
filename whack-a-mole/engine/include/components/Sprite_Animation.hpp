/*
** EPITECH PROJECT, 2024
** whack-a-mole
** File description:
** Sprite_Animation
*/

#ifndef SPRITE_ANIMATION_HPP_
    #define SPRITE_ANIMATION_HPP_

    #include <optional>

namespace Components {

    class Sprite_Animation {
        public:
            /**
             * @brief Construct a new Sprite_Animation object
             *
             * @param sta The number of Status for the Sprite
             * @param value The value to be increase for the Sprite
             * @param res The time for the Sprite to be reseted
             * @param dead A Bool to know if the Sprite animation need to be delete after the max status
             */
            Sprite_Animation(int sta, int value, double res, std::optional<bool> dead = std::nullopt);

            /**
             * @brief Destroy the Sprite_Animation object
             * 
             */
            ~Sprite_Animation() = default;




            /**
             * @brief Is the Sprite Animation is negative
             * 
             */
            bool isneg;

            /**
             * @brief The number of states for the Sprite
             * 
             */
            int status;

            /**
             * @brief The value to be increased for the Sprite
             * 
             */
            int val;

            /**
             * @brief The time for the Sprite to be reseted
             * 
             */
            double reset;

            /**
             * @brief The time for the Sprite to be refreshed
             * 
             */
            float t;

            /**
             * @brief The bool to know if the Sprite animation need to be delete after the max status
             * 
             */
            bool deadAnimation;
    };

}

#endif /* !SPRITE_ANIMATION_HPP_ */
