/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Button
*/

#include "Button.hpp"
#include "RaylibPlus.hpp"
#include <iostream>

Menu::Button::Button(bool accessible, const float x, const float y, const float width, const float height, const float screenWidth, const float screenHeight, const std::string &text, const std::string &selectedText, Font &font, std::function<int()> onClick) :
    _x(x),
    _y(y),
    _width(width),
    _height(height),
    _screenWidth(screenWidth),
    _screenHeight(screenHeight),
    _text(text),
    _selectedText(selectedText),
    _font(font),
    _isSelected(false),
    _onClick(onClick),
    _endBoxButton(0),
    _buttonBorderLine({x - width, y, x, y}),
    _clock(500),
    _accessible(accessible)
{}

void Menu::Button::drawButton()
{
    DrawRectangleGradientH(_x, _y, _endBoxButton, _height, _isSelected ? _C_SELECTED_D : _C_UNSELECTED, _isSelected ? _C_SELECTED : _C_UNSELECTED);

    if (_isSelected)
        DrawTextEx(_font, _selectedText.c_str(), { 50, _screenHeight - 50 }, (_font.baseSize / 10) * 7, 2, GRAY);

    if (_clock.isTicked()) {
        if (_endBoxButton < _width) {
            _endBoxButton += 5;
        } else {
            _buttonBorderLine.x = _buttonBorderLine.x + 1 > _x + _width ? _x + _width : _buttonBorderLine.x + 1;
            _buttonBorderLine.z = _buttonBorderLine.z + 1 > _x + _width ? _x + _width : _buttonBorderLine.z + 1;
        }
    }
    _endBoxButton = _endBoxButton > _width ? _width : _endBoxButton;

     if (_isSelected)
        RaylibPlus::DrawRectangleGradient3H(_buttonBorderLine.x,  _buttonBorderLine.y + _height - 2, _buttonBorderLine.z - _buttonBorderLine.x , (_buttonBorderLine.w - _buttonBorderLine.y) + 2, Color{ 255, 255, 255, 0 }, WHITE, Color{ 255, 255, 255, 0 });

    Vector2 textSize = MeasureTextEx(_font, _text.c_str(), (_font.baseSize / 10) * 8, 2);

    Vector2 textPos = { _x + 1, _y + (_height / 2) - (textSize.y / 2) };
    DrawTextEx(_font, _text.c_str(), textPos, (_font.baseSize / 10) * 8, 2, _accessible ? WHITE : GRAY);
}

void Menu::Button::checkMouseHover() {
    Vector2 mousePos = GetMousePosition();

    if (_accessible && CheckCollisionPointRec(mousePos, { _x, _y, _width, _height })) {
        if (!_isSelected) {
            _endBoxButton = 0;
            _buttonBorderLine.x = _x - _width;
            _buttonBorderLine.z = _x;
        }
        _isSelected = true;
    } else {
        _isSelected = false;
    }
}

int Menu::Button::buttonClicked()
{
    Vector2 mousePos = GetMousePosition();

    if (CheckCollisionPointRec(mousePos, { _x, _y, _width, _height })) {
        int status = _onClick();
        std::cout << "STATUS = " << status << std::endl;
        return status;
    }
    return 0;
}

void Menu::Button::updateWidth(float newScreenWidth)
{
    _width = (newScreenWidth / 10) * 4 - 50;
    _screenWidth = newScreenWidth;
}

void Menu::Button::updateHeight(float newScreenHeight)
{
    _screenHeight = newScreenHeight;
}
