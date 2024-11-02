/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Raylib
*/

#ifndef RAYLIB_HPP_
#define RAYLIB_HPP_
#include <string>
#include <raylib.h>
#include "LibGraph.hpp"

/**
 * @class Raylib
 * @brief everything i need in the raylib lib
 *
 */
class Raylib : public ILibGraph
{
public:
    /**
     * @brief Construct a new Window Raylib object
     *
     */
    Raylib() : ILibGraph() {};
    /**
     * @brief Destroy the Window Raylib object
     *
     */
    ~Raylib() = default;
    /**
     * @brief Initialize window and OpenGL context
     *
     * @param width
     * @param height
     * @param name the name of the window
     */
    virtual void Init(int width, int height, std::string name) override { InitWindow(width, height, name.c_str()); };
    /**
     * @brief Set target FPS (maximum)
     *
     * @param fps frame par secondes
     */
    virtual void setFramePerSec(int fps) override { SetTargetFPS(60);};
    /**
     * @brief Set background color (framebuffer clear color)
     *
     * @param color
     */
    virtual void clearWindowIn(int r, int g, int b, int a) override { ClearBackground(Color{(unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a}); };
    /**
     * @brief Setup canvas (framebuffer) to start drawing
     *
     */
    virtual void beginDraw() override { BeginDrawing(); };
    /**
     * @brief End canvas drawing and swap buffers (double buffering)
     *
     */
    virtual void endDraw() override { EndDrawing(); }
    /**
     * @brief Check if application should close (KEY_ESCAPE pressed or windows close icon clicked)
     *
     * @return true
     * @return false
     *
     */
    virtual bool windowClosed() override { return WindowShouldClose(); }
    /**
     * @brief is button clicked
     *
     * @param button space in which we check if the mouse has clicked in this place
     * @return true button pressed
     * @return false button not pressed
     *
     */
    virtual void closeWindow() override
    {
        CloseWindow();
    }
};

class Text : public ITextRenderer
{
public:
    /**
     * @brief draw text on page raylib
     *
     * @param text text to draw
     * @param x the position x
     * @param y the position y
     * @param fontSize the font of the text
     * @param r the red color
     * @param g the green color
     * @param b the blue color
     * @param a the alpha (transparency)
     */
    void drawText(const std::string &text, int x, int y, int fontSize, int r, int g, int b, int a) override
    {
        DrawText(text.c_str(), x, y, fontSize, Color{(unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a});
    }
};

class InputBoxRaylib : public IInputBox
{
private:
    /**
     * @brief the box in which the inputbox is contained
     *
     */
    Rectangle box;
    /**
     * @brief the text contained in the input box
     *
     */
    char text[62];
    /**
     * @brief the lenght of the text
     *
     */
    int len;

public:
    bool isActive;
    /**
     * @brief Construct a new Input Box Raylib object
     *
     * @param x the position in x
     * @param y the position in y
     * @param width the width of the box rectangle
     * @param height the height of the box rectangle
     */
    InputBoxRaylib(float x, float y, float width, float height)
        : box{x, y, width, height}, isActive(false), len(0)
    {
        text[0] = '\0';
    };
    /**
     * @brief Destroy the Input Box Raylib object
     *
     */
    ~InputBoxRaylib() = default;

    /**
     * @brief handle input in the input box
     *
     */
    void handleInput() override
    {
        if (isActive)
        {
            int key = GetCharPressed();
            while (key > 0 && len < 63)
            {
                if ((key >= 32) && (key <= 125))
                {
                    text[len] = (char)key;
                    text[len + 1] = '\0';
                    len++;
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && len > 0) // erase characters
            {
                len--;
                text[len] = '\0';
            }
        }
    }
    /**
     * @brief draw the text written by the user
     *
     * @param isPassword
     */
    void draw(bool isPassword = false) override
    {
        DrawRectangleRec(box, LIGHTGRAY);
        std::string displayText = isPassword ? std::string(len, '*') : std::string(text); // to hide the password
        Text().drawText(displayText.c_str(), box.x + 10, box.y + 10, 20, 80, 80, 80, 255);
    }
    /**
     * @brief has the inputbox field been selected?
     *
     * @return true
     * @return false
     */
    bool isPressed() override { return CheckCollisionPointRec(GetMousePosition(), box) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON); };
    /**
     * @brief Get the Text object
     *
     * @return std::string
     */
    std::string getText() const override { return std::string(text); };
};

class BoxRaylib : public IButton
{
private:
    /**
     * @brief space in which we check if the mouse has clicked in this place
     *
     */
    Rectangle _button;

public:
    /**
     * @brief Construct a new Box Raylib object
     *
     * @param x the position in x of the button
     * @param y the position in y of the button
     * @param width the width of the button
     * @param height the height of the button
     */
    BoxRaylib(float x, float y, float width, float height)
        : _button{x, y, width, height} {};
    /**
     * @brief draw the button with the text inside
     *
     * @param nameBox the text written on the button
     * @param colorBox the color of the button
     * @param colorText the color of the text
     */
    void drawBox(const std::string &nameBox, int rBox, int gBox, int bBox, int aBox,
                 int rText, int gText, int bText, int aText) override
    {
        DrawRectangleRec(_button, Color{(unsigned char)rBox, (unsigned char)gBox, (unsigned char)bBox, (unsigned char)aBox});
        Text().drawText(nameBox.c_str(), _button.x + 5, _button.y + 10, 20, rText, gText, bText, aText);
    }
    /**
     * @brief is button pressed
     *
     * @return true
     * @return false
     */
    bool isPressed() override { return CheckCollisionPointRec(GetMousePosition(), _button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON); };
    ~BoxRaylib() = default;
};

#endif /* !RAYLIB_HPP_ */
