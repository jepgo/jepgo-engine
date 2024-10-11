/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Drawable
*/

#include "Drawable.hpp"

Components::Drawable::Drawable(
        std::size_t ind, std::optional<Rectangle> r,
        std::optional<std::vector<float>> s
    ) : index(ind), rect(r)
{
    if (r.has_value())
        start = r.value().x;
    if (s.has_value())
        scale = s.value();
    else
    {
        scale.push_back(1);
        scale.push_back(1);
    }
};

void Components::Drawable::draw(std::vector<Texture2D> &textures, Positions &pos)
{
    if (rect.has_value()) {
        float a = (rect.value().width * scale[0]);
        float b = (rect.value().height * scale[1]);
        DrawTexturePro(textures[index], rect.value(), Rectangle{pos.x, pos.y, a, b}, {pos.x / 2, pos.y / 2}, 0, WHITE);
    } else
        DrawTextureEx(textures[index], {pos.x, pos.y}, 0.0f, scale[0], WHITE);
}

void Components::Drawable::change_ind(std::size_t ind)
{
    index = ind;
}

std::size_t Components::Drawable::getIndex()
{
    return index;
}

std::optional<Rectangle> &Components::Drawable::getRect()
{
    return rect;
}