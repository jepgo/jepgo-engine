/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** LibGraph
*/

#ifndef LIBGRAPH_HPP_
#define LIBGRAPH_HPP_
#include <iostream>

class ILibGraph
{
public:
    virtual ~ILibGraph() = default;
    virtual void Init(int width, int height, std::string name) = 0;
    virtual void setFramePerSec(int fps) = 0;
    virtual void clearWindowIn(int r, int g, int b, int a) = 0;
    virtual void beginDraw() = 0;
    virtual void endDraw() = 0;
    virtual bool windowClosed() = 0;
    virtual void closeWindow() = 0;
};

class ITextRenderer
{
public:
    virtual ~ITextRenderer() = default;
    virtual void drawText(const std::string &text, int x, int y, int fontSize, int r, int g, int b, int a) = 0;
};

class IInputBox
{
public:
    virtual ~IInputBox() = default;
    virtual void handleInput() = 0;
    virtual void draw(bool isPassword = false) = 0;
    virtual bool isPressed() = 0;
    virtual std::string getText() const = 0;
};

class IButton
{
public:
    virtual ~IButton() = default;
    virtual void drawBox(const std::string& nameBox, int rBox, int gBox, int bBox, int aBox, int rText, int gText, int bText, int aText) = 0;
    virtual bool isPressed() = 0;
};

#endif /* !LIBGRAPH_HPP_ */
