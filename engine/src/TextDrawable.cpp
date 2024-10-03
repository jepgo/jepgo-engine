/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** TextDrawable
*/

#include "TextDrawable.hpp"

TextDrawable::TextDrawable(Positions &&pos, std::size_t size, Color color) : _pos(pos), _size(size), _color(color)
{

}

TextDrawable::~TextDrawable()
{
}

void TextDrawable::Draw(std::string mess)
{
    DrawText(mess.c_str(), _pos.x, _pos.y, _size, _color);
}