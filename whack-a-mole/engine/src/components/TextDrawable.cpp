/*
** EPITECH PROJECT, 2024
** whack-a-mole
** File description:
** TextDrawable
*/

#include "TextDrawable.hpp"

Components::TextDrawable::TextDrawable(std::string const &mess, Position2D &&pos, std::size_t size, Color color) : mess(mess), _pos(pos), _size(size), _color(color)
{

}

Components::TextDrawable::~TextDrawable()
{
}

void Components::TextDrawable::Draw()
{
    DrawText(mess.c_str(), _pos.x, _pos.y, _size, _color);
}
