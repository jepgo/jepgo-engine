/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Menu
*/

#include <iostream>
#include "MainGame.hpp"
#include "Menu.hpp"

Menu::Menu::Menu(const size_t screenWidth, const size_t screenHeight) :
    _screenWidth(screenWidth),
    _screenHeight(screenHeight),
    _state(ENTER_MENU),
    _instructionOpacity(std::make_tuple(true, 0)),
    _CInstruction(500),
    _inTransition(false),
    _transitionOpacity(std::make_tuple(true, 0)),
    _CTransition(100),
    _playerName(""),
    _logIcon(screenWidth - 400, 25, 400, 50, "Login / Register", _font)
{
    _bckgrnd = LoadTexture("sprites/background-menu.png");
    _font = LoadFont("sprites/eurocine-regular.ttf");
    _titlePos = { 50, 20 };

    _buttons.push_back(Button(true, 0, 100, (screenWidth / 10) * 4 - 50, 50, screenWidth, screenHeight, "Play", "Start the game from the hangar (where pilots can customize their starfighters).", _font, []() { std::cout << "Play" << std::endl; MainGame::mainGame();}));
    _buttons.push_back(Button(false, 0, 150, (screenWidth / 10) * 4 - 50, 50, screenWidth, screenHeight, "Level and score attack", "See all completed levels and your score.", _font, []() { std::cout << "Level and score attack" << std::endl; }));
    _buttons.push_back(Button(false, 0, 200, (screenWidth / 10) * 4 - 50, 50, screenWidth, screenHeight, "Data and gallery", "See your data and your gallery.", _font, []() { std::cout << "Data and gallery" << std::endl; }));
    _buttons.push_back(Button(true, 0, 250, (screenWidth / 10) * 4 - 50, 50, screenWidth, screenHeight, "Options", "Options of the game.", _font, []() { std::cout << "Options" << std::endl; }));
    _buttons.push_back(Button(false, 0, 300, (screenWidth / 10) * 4 - 50, 50, screenWidth, screenHeight, "Shop", "Buy skins and customize your starfighter.", _font, []() { std::cout << "Shop" << std::endl; }));
    _buttons.push_back(Button(true, 0, 350, (screenWidth / 10) * 4 - 50, 50, screenWidth, screenHeight, "Manual R", "See key guide and game rules.", _font, []() { std::cout << "Shop" << std::endl; }));
    _buttons.push_back(Button(true, 0, 400, (screenWidth / 10) * 4 - 50, 50, screenWidth, screenHeight, "Special", "Special.", _font, []() { std::cout << "Special" << std::endl; }));
    _buttons.push_back(Button(false, 0, 450, (screenWidth / 10) * 4 - 50, 50, screenWidth, screenHeight, "Competition", "Play in competition mode.", _font, []() { std::cout << "Competition" << std::endl; }));
    _buttons.push_back(Button(false, 0, 500, (screenWidth / 10) * 4 - 50, 50, screenWidth, screenHeight, "Online", "Play with other pilots across the world.", _font, []() { std::cout << "Online" << std::endl; }));

    for (auto &button : _buttons) {
        button.updateWidth(_screenWidth);
    }

    _lines.push_back(AnimLine(_screenWidth, 3, _screenWidth, screenHeight, 6, 10, Color{ 79, 255, 103, 50 }));
    _lines.push_back(AnimLine(_screenWidth, 5, _screenWidth, screenHeight, 1000, 50, Color{ 116, 255, 199, 100 }));
    _lines.push_back(AnimLine(_screenWidth, 5, _screenWidth, screenHeight, 1000, 100, Color{ 116, 255, 199, 100 }));
}

Menu::Menu::~Menu()
{
    UnloadFont(_font);
    UnloadTexture(_bckgrnd);
}

void Menu::Menu::updateSize(const size_t screenWidth, const size_t screenHeight)
{
    _screenWidth = screenWidth;
    _screenHeight = screenHeight;

    for (auto &button : _buttons) {
        button.updateWidth(_screenWidth);
        button.updateHeight(_screenHeight);
    }
    for (auto &line : _lines) {
        line.updateSize(_screenWidth, _screenHeight);
    }
}

void Menu::Menu::_drawInMenu()
{
    DrawTextEx(_font, "Menu", _titlePos, _font.baseSize, 2, WHITE);
    DrawRectangleGradientH(0, 60, (_screenWidth / 5) * 2, 5, Color{ 143, 255, 167, 255 }, Color{ 143, 255, 167, 0 });

    for (auto &button : _buttons) {
        button.checkMouseHover();
        button.drawButton();
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        for (auto &button : _buttons) {
            button.buttonClicked();
        }
    }

    _logIcon.drawIcon();
}

void Menu::Menu::_drawEnterMenu()
{
    std::string instruction = "Click on the screen to start.";
    Vector2 instructionPos = {(_screenWidth / 2) - (MeasureTextEx(_font, instruction.c_str(), _font.baseSize, 2).x / 2), (float)_screenHeight - 100};

    if (_CInstruction.isTicked()) {
        _instructionOpacity = std::make_tuple(std::get<0>(_instructionOpacity), std::get<1>(_instructionOpacity) + (std::get<0>(_instructionOpacity) ? 1 : -1));
        if (std::get<1>(_instructionOpacity) > 255)
            _instructionOpacity = std::make_tuple(false, 255);
        if (std::get<1>(_instructionOpacity) < 0)
            _instructionOpacity = std::make_tuple(true, 0);
    }

    DrawTextEx(_font, instruction.c_str(), instructionPos, _font.baseSize, 2, Color{ 143, 255, 167, (unsigned char)std::get<1>(_instructionOpacity) });

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        _inTransition = true;
}

void Menu::Menu::drawMenu()
{
    DrawTexture(_bckgrnd, _screenWidth / 2 - _bckgrnd.width / 2, _screenHeight / 2 - _bckgrnd.height / 2, WHITE);

    for (auto &line : _lines) {
        line.draw();
    }

    DrawRectangle(0, 0, _screenWidth, _screenHeight, Color{ 0, 0, 0, 100 });
    DrawRectangleGradientH(0, 0, (_screenWidth / 5) * 3, _screenHeight, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 0 });
    DrawRectangle(0, 0, _screenWidth, _screenHeight, Color{ 116, 255, 199, 50 });

    _menuPage.at(_state)();

    if (_inTransition && _CTransition.isTicked()) {
        _transitionOpacity = std::make_tuple(std::get<0>(_transitionOpacity), std::get<1>(_transitionOpacity) + (std::get<0>(_transitionOpacity) ? 10 : -10));
        if (std::get<1>(_transitionOpacity) > 255) {
            _transitionOpacity = std::make_tuple(false, 255);
            _state = IN_MENU;
        }
        if (std::get<1>(_transitionOpacity) < 0) {
            _transitionOpacity = std::make_tuple(true, 0);
            _inTransition = false;
        }
    }

    if (_inTransition)
        DrawRectangle(0, 0, _screenWidth, _screenHeight, Color{ 0, 0, 0, (unsigned char)std::get<1>(_transitionOpacity) });    
}