/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Drawable
*/

#ifndef DRAWABLE_HPP_
    #define DRAWABLE_HPP_
    #include <raylib.h>
    #include <vector>
    #include <optional>
    #include "Position.hpp"

namespace Components {
    class Drawable {
        public:
            /**
             * @brief Construct a new Drawable object
             *
             * @param ind The index of the texture in the List of all the texture
             * @param r optional rectangle for The Sprite to Draw
             * @param s A Optional Vector of 2 float for the Scale
             */
            Drawable(
                std::size_t ind, std::optional<Rectangle> r = std::nullopt,
                std::optional<std::vector<float>> s = std::nullopt
            );

            /**
             * @brief Destroy the Drawable object
             * 
             */
            ~Drawable() = default;



            /**
             * @brief Draw the texture
             * 
             * @param textures The List of all the texture
             * @param pos The Position of the Sprite
             */
            void draw(std::vector<Texture2D> &textures, Position2D &pos);

            /**
             * @brief Change the index of the texture
             * 
             * @param ind The new index
             */
            void change_ind(std::size_t ind);

            /**
             * @brief Get the Index of the texture
             * 
             * @return std::size_t 
             */
            std::size_t getIndex();

            /**
             * @brief Get the Rect object
             * 
             * @return std::optional<Rectangle>& 
             */
            std::optional<Rectangle> &getRect();


            /**
             * @brief The scale of the texture
             * 
             */
            std::vector<float> scale;

            /**
             * @brief The start of the rectangle
             * 
             */
            int start;
        private:
            /**
             * @brief The index of the texture
             * 
             */
            std::size_t index;


            /**
             * @brief The rectangle of the texture
             * 
             */
            std::optional<Rectangle> rect;
    };
}


#endif /* !DRAWABLE_HPP_ */
