/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** LogIcon
*/

#include "LogIcon.hpp"
#include "RaylibPlus.hpp"

Menu::LogIcon::LogIcon(
    const size_t x,
    const size_t y,
    const size_t width,
    const size_t height,
    const float screenWidth,
    const float screenHeight,
    const std::string text,
    Font &font,
    std::function<int ()> onClick
):
    _x(x),
    _y(y),
    _width(width),
    _height(height),
    _screenWidth(screenWidth),
    _screenHeight(screenHeight),
    _text(text),
    _font(font),
    _isOpen(false),
    _isSelect(false),
    _onClick(onClick)
{
    _icon = LoadTexture("sprites/account.png");
}

Menu::LogIcon::~LogIcon()
{
}

void Menu::LogIcon::drawIcon()
{
    _isSelectIcon();
    if (_isSelect && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        _onClick();
    DrawRectangle(_x, _y, _width, _height, _isSelect ? _C_SELECTED : _C_UNSELECTED);
    DrawRectangle(_x, _y, _width, 3, _C_BORDER);
    DrawRectangle(_x, _y, 3, _height, _C_BORDER);
    DrawRectangle(_x, _y + _height - 3, _width, 3, _C_BORDER);

    RaylibPlus::DrawImage(_icon, _x + 10, _y + 15, 20, 20);
    DrawTextEx(_font, _text.c_str(), Vector2{ (float)_x + 50, (float)_y + 15 }, _font.baseSize * 0.7, 2, _C_BORDER);
}

void Menu::LogIcon::_isSelectIcon()
{
    if (CheckCollisionPointRec(GetMousePosition(), { (float)_x, (float)_y, (float)_width, (float)_height })) {
        _isSelect = true;
    } else {
        _isSelect = false;
    }
}

void Menu::LogIcon::updateSize(const float screenWidth, const float screenHeight)
{
    _screenWidth = screenWidth;
    _screenHeight = screenHeight;

    _x = _screenWidth - 400;
}
