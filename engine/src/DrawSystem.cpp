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
void DrawSystem::system(sf::RenderWindow &window, Register &r, std::vector<sf::Texture> &texture)
{
    auto &pos = r.getComp<Positions>();
    auto &draw = r.getComp<Drawable>();

    for (std::size_t i = 0; i < draw.size(); i++)
    {
        // if (draw[i].has_value() && i == 4)
        //     std::cout << "is draw" << std::endl;
        // if (draw[i].has_value() == false && i == 4)
        //     std::cout << "not draw" << std::endl;
        if (draw[i].has_value() && pos[i].has_value())
        {
            draw[i].value().draw(window, texture[draw[i].value().getIndex()], pos[i].value());
        }
    }
}
