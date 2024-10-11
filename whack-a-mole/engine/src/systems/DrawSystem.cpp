/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** DrawSystem
*/

#include "DrawSystem.hpp"

#include "Position.hpp"
#include "Drawable.hpp"

Systems::DrawSystem::DrawSystem()
{
}

Systems::DrawSystem::~DrawSystem()
{
}

void Systems::DrawSystem::system(Register &r, std::vector<Texture2D> &texture)
{
    auto &pos = r.getComp<Components::Positions>();
    auto &draw = r.getComp<Components::Drawable>();

    for (std::size_t i = 0; i < draw.size(); i++) {
        if (draw[i].has_value() && pos[i].has_value())
        {
            draw[i].value().draw(texture, pos[i].value());
        }
    }
}
