/*
** EPITECH PROJECT, 2024
** whack-a-mole
** File description:
** Points
*/

#ifndef POINTS_HPP_
    #define POINTS_HPP_
    #include <bits/c++config.h>

namespace Components {
    /**
     * @brief Component for the score of the player
     * 
     */
    class Points {
        public:
            Points() { _point = 0; };
            ~Points() {};

            std::size_t _point;
    };

}

#endif /* !POINTS_HPP_ */
