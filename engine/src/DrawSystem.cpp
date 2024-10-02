/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** DrawSystem
*/

#include "DrawSystem.hpp"

DrawSystem::DrawSystem()
{
}

DrawSystem::~DrawSystem()
{
}

/**
 * @brief The drawable System
 * 
 * @param window The window of the screen
 * @param r The Registry
 * @param texture The list of texture for all the sprite
 */
void DrawSystem::system(Register &r, std::vector<Texture2D> &texture)
{
    auto &pos = r.getComp<Positions>();
    auto &draw = r.getComp<Drawable>();

    for (std::size_t i = 0; i < draw.size(); i++) {
        if (draw[i].has_value() && pos[i].has_value())
        {
            // std::cout << "draw" << std::endl;
            draw[i].value().draw(texture, pos[i].value());
        }
    }
}
