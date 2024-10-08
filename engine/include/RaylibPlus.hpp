/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** RaylibPlus
*/

#ifndef RAYLIBPLUS_HPP_
    #define RAYLIBPLUS_HPP_
    #include <raylib.h>

/**
 * @brief Namespace to add new functions link to raylib functionalities
 * 
 */
namespace RaylibPlus {

    /**
     * @brief Draw a rectangle with a gradient color from left to right, with 3 colors
     * 
     * @param posX The x position of the rectangle
     * @param posY The y position of the rectangle
     * @param width The width of the rectangle
     * @param height The height of the rectangle
     * @param color1 The first color of the gradient
     * @param color2 The second color of the gradient
     * @param color3 The third color of the gradient
     */
    void DrawRectangleGradient3H(
        const int posX,
        const int posY,
        const int width,
        const int height,
        const Color &color1,
        const Color &color2,
        const Color &color3
    );

    /**
     * @brief Draw a rectangle with a gradient color from top to bottom, with 3 colors
     * 
     * @param posX The x position of the rectangle
     * @param posY The y position of the rectangle
     * @param width The width of the rectangle
     * @param height The height of the rectangle
     * @param color1 The first color of the gradient
     * @param color2 The second color of the gradient
     * @param color3 The third color of the gradient
     */
    void DrawImage(
        const Texture2D &texture,
        const float posX,
        const float posY,
        const float width,
        const float height
    );
}

#endif /* !RAYLIBPLUS_HPP_ */