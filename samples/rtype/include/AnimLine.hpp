/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AnimLine
*/

#ifndef ANIMLINE_HPP_
    #define ANIMLINE_HPP_
    #include <raylib.h>
    #include <stddef.h>
    #include "Clock.hpp"

/**
 * @brief Menu namespace of the game
 * 
 */
namespace Menu {
    /**
     * @brief Class that represent a line that will be drawn on the screen
     */
    class AnimLine {
        public:
            /**
             * @brief Construct a new AnimLine object
             * 
             * @param width The width of the line
             * @param height The height of the line
             * @param screenWidth The width of the screen
             * @param screenHeight The height of the screen
             * @param interval The interval between the generation of the lines
             * @param speed The speed of the line
             * @param color The color of the line
             */
            AnimLine(const float width, const float height, const float screenWidth, const float screenHeight, const float interval, const float speed, const Color color)
                : _width(width), _height(height), _screenWidth(screenWidth), _screenHeight(screenHeight), _interval(interval), _startGen(0), _color(color), _clock(speed) {};
            /**
             * @brief Destroy the Anim Line object
             * 
             */
            ~AnimLine() = default;

            /**
             * @brief Draw the lines
             * 
             */
            void draw(bool mouvLine);
            /**
             * @brief Update the size of the screen,
             * and the size of the line to adapt it to the new screen size
             * 
             * @param screnWidth The new width of the screen
             * @param screnHeight The new height of the screen
             */
            void updateSize(const float screnWidth, const float screnHeight);

        private:
            /**
             * @brief The width of the line
             * 
             */
            float _width;

            /**
             * @brief The height of the line
             * 
             */
            float _height;

            /**
             * @brief The width of the screen
             * 
             */
            float _screenWidth;

            /**
             * @brief The height of the screen
             * 
             */
            float _screenHeight;

            /**
             * @brief The interval between the generation of the lines
             * 
             */
            float _interval;

            /**
             * @brief The start of the generation of the lines
             * 
             */
            float _startGen;

            /**
             * @brief The color of the line
             * 
             */
            Color _color;

            /**
             * @brief The clock to handle when to update the animation
             * 
             */
            Clock _clock;
    };
}
#endif /* !ANIMLINE_HPP_ */