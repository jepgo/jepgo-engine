/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** DrawSystem
*/

#include "jepmod/exported.hpp"
#include "jepengine/Game.hpp"
#include "jepmaker/components/Drawable2D.hpp"
#include "jepmaker/components/Position.hpp"

/**
 * @brief The DrawSystem
 * 
 * @param game Game
 * @param pos Position
 * @param rect the jgo::Rectangle
 * @param index The index of the image
 * @param scale The scale of the image
 */
static void Todraw(jgo::Game &game, Position2D &pos, std::optional<jgo::Rectangle> &rect, std::string const &index, std::array<float, 2> scale)
{
        if (rect.has_value()) {
            float a = (rect.value().width * scale[0]);
            float b = (rect.value().height * scale[1]);
            game.getGraphicLib()->drawImage(index, rect.value(), jgo::Rectangle{pos.x, pos.y, a, b}, jgo::Vector2{scale[0], scale[1]});
            //DrawTexturePro(textures[index], rect.value(), Rectangle{pos.x, pos.y, a, b}, {pos.x / 2, pos.y / 2}, 0, WHITE);
        } else {
            game.getGraphicLib()->drawImage(index, jgo::Rectangle{-1, -1, -1, -1}, jgo::Rectangle{pos.x, pos.y, 0, 0}, jgo::Vector2{scale[0], scale[1]});
            //DrawTextureEx(textures[index], {pos.x, pos.y}, 0.0f, scale[0], WHITE);
        }
}

/**
 * @brief The drawable System
 * 
 * @param window The window of the screen
 * @param r The Registry
 * @param texture The list of texture for all the sprite
 */
exported(void) jepgoSystem(jgo::Game &game, float &t)
{
    auto &pos = game.ecs.getComp<Position2D>();
    auto &draw = game.ecs.getComp<Drawable>();

    for (std::size_t i = 0; i < draw.size(); ++i) {
        if (draw[i].has_value() && pos[i].has_value()) {
            Drawable &tmp = draw[i].value();
            Todraw(game, pos[i].value(), tmp.getRect(), tmp.getIndex(), tmp.getScale());
        }
    }
}