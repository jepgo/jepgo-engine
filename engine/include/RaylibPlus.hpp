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
    void DrawRectangleGradient3H(int posX, int posY, int width, int height, Color color1, Color color2, Color color3)
    {
        int midWidth = width / 2;

        DrawRectangleGradientH(posX, posY, midWidth, height, color1, color2);
        DrawRectangleGradientH(posX + midWidth, posY, midWidth, height, color2, color3);
    }

}

#endif /* !RAYLIBPLUS_HPP_ */
