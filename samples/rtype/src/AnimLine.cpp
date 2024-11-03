/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AnimLine
*/

#include <iostream>
#include "AnimLine.hpp"

void Menu::AnimLine::draw(bool mouvLine)
{
    if (mouvLine && _clock.isTicked())
        _startGen = _startGen >= _interval ? 1 : _startGen + 1;

    for (size_t y = _startGen; y < _screenHeight + _interval; y += _interval) {
        DrawRectangle(0, y, _width, _height, _color);
    }
}

void Menu::AnimLine::updateSize(const float screenWidth, const float screenHeight)
{
    _width = (_width / _screenWidth) * screenWidth;
    _screenWidth = screenWidth;
    _screenHeight = screenHeight;
}