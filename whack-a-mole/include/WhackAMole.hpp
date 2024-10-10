/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** WhackAMole
*/

#ifndef WHACKAMOLE_HPP_
    #define WHACKAMOLE_HPP_
    #include "Register.hpp"
    #include "DrawSystem.hpp"

namespace WhackAMole {

    class WhackAMole {
        public:
            WhackAMole();
            ~WhackAMole();

            void start();

        private:
            Register _r;
            DrawSystem _drawSys;

            std::vector<Texture2D> _textures;

        private:
    };
}

#endif /* !WHACKAMOLE_HPP_ */
