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
    #include "ScoreSystem.hpp"
    #include "TextDrawableSystem.hpp"
    #include "Sprite2DMultiAnimSystem.hpp"

/**
 * @brief The namespace of the WhackAMole game
 * 
 */
namespace WhackAMole {

    /**
     * @brief The WhackAMole class
     * 
     */
    class WhackAMole {
        public:
            /**
             * @brief Construct a new WhackAMole object
             * 
             */
            WhackAMole();

            /**
             * @brief Destroy the Whack A Mole object
             * 
             */
            ~WhackAMole() = default;


            /**
             * @brief Start the game
             * 
             */
            void start();

        private:
            /**
             * @brief The Register object
             * 
             */
            Register _r;



            /**
             * @brief The DrawSystem object
             * 
             */
            Systems::DrawSystem _drawSys;

            /**
             * @brief The Sprite2DMultiAnimSystem object
             * 
             */
            Systems::Sprite2DMultiAnimSystem _animSys;

            Systems::TextDrawableSystem _textSys;
        
            Systems::ScoreSystem _scoreSys;
        
            /**
             * @brief All the loaded textures of the game
             * 
             */
            std::vector<Texture2D> _textures;
        private:
    };
}

#endif /* !WHACKAMOLE_HPP_ */
