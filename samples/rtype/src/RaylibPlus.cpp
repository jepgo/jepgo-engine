/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** RaylibPlus
*/

#include "RaylibPlus.hpp"

void RaylibPlus::DrawRectangleGradient3H(
        const int posX,
        const int posY,
        const int width,
        const int height,
        const Color &color1,
        const Color &color2,
        const Color &color3
    )
{
    int midWidth = width / 2;

    DrawRectangleGradientH(posX, posY, midWidth, height, color1, color2);
    DrawRectangleGradientH(posX + midWidth, posY, midWidth, height, color2, color3);
}

void RaylibPlus::DrawImage(
        const Texture2D &texture,
        const float posX,
        const float posY,
        const float width,
        const float height
    )
{
    const auto src = Rectangle{0, 0, (float)texture.width, (float)texture.height};
    const auto dest = Rectangle{posX, posY, width, height};

    DrawTexturePro(texture, src, dest, Vector2{0, 0}, 0, WHITE);
}
