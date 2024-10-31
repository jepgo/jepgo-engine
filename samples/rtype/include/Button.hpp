/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Button
*/

#ifndef BUTTON_HPP_
    #define BUTTON_HPP_
    #include <raylib.h>
    #include <functional>
    #include <stddef.h>
    #include <string>
    #include "Clock.hpp"

/**
 * @brief Menu namespace of the game
 * 
 */
namespace Menu {
    /**
     * 
     * @brief The class of the buttons
     * 
     */
    class Button {
    public:
        /**
         * @brief Construct a new Button object
         * 
         * @param x The x position of the button
         * @param y The y position of the button
         * @param width The width of the button
         * @param height The height of the button
         * @param screenWidth The width of the screen
         * @param screenHeight The height of the screen
         * @param text The text of the button
         * @param selectedText The text of the button when it is selected
         * @param font The font of the button
         * @param onClick The function called when the button is clicked
         * @param accessible If the button is accessible
         */
        Button(
            bool accessible,
            const float x,
            const float y,
            const float width,
            const float height,
            const float screenWidth,
            const float screenHeight,
            const std::string &text,
            const std::string &selectedText,
            Font &font,
            std::function<void()> onClick
        );
        ~Button() = default;

        /**
         * @brief Draw the button
         * 
         */
        void drawButton();
        
        /**
         * @brief Check if the mouse is hovering the button
         * 
         */
        void checkMouseHover();

        /**
         * @brief Check if the button is clicked,
         * and if the button is clicked, call the function onClick
         * 
         */
        void buttonClicked();

        /**
         * @brief Update the width of the button, and the width of the screen
         * 
         * @param newScreenWidth The new width of the screen
         */
        void updateWidth(float newScreenWidth);
        
        /**
         * @brief Update the height of the button, and the height of the screen
         * 
         * @param newScreenHeight The new height of the screen
         */
        void updateHeight(float newScreenHeight);

        /**
         * @brief Set the _accessible attribute
         * 
         * @param accessible The new value of the _accessible attribute
         */
        void setAccessible(bool accessible) { _accessible = accessible; }

        void setNewText(const std::string &newText) { _text = newText; }
    private:
        /**
         * @brief The x position of the button
         * 
         */
        float _x;

        /**
         * @brief The y position of the button
         * 
         */
        float _y;
        
        /**
         * @brief The width of the button
         * 
         */
        float _width;
        
        /**
         * @brief The height of the button
         * 
         */
        float _height;
        
        /**
         * @brief The width of the screen
         * 
         */
        float _screenWidth;
        
        /**
         * @brief The height of the screen
         * 
         */
        float _screenHeight;
        
        /**
         * @brief The text of the button
         * 
         */
        std::string _text;
        
        /**
         * @brief The text of the button when it is selected
         * 
         */
        std::string _selectedText;
        
        /**
         * @brief The font of the button
         * 
         */
        Font _font;
        
        /**
         * @brief If the button is selected
         * 
         */
        bool _isSelected;
        
        /**
         * @brief The function called when the button is clicked
         * 
         */
        std::function<void()> _onClick;

        /**
         * @brief The end of the box of the button
         * 
         */
        size_t _endBoxButton;

        /**
         * @brief Position of the line animation
         * 
         */
        Vector4 _buttonBorderLine;

        /**
         * @brief The clock of the button
         * 
         */
        Clock _clock;

        /**
         * @brief If the button is accessible
         * 
         */
        bool _accessible;


        /**
         * @brief The color of the button when it is selected
         * 
         */
        const Color _C_SELECTED = Color{89, 253, 142, 255};
        /**
         * @brief The color of the button when it is selected,
         * but with less opacity to make a gradient
         */
        const Color _C_SELECTED_D = Color{89, 253, 142, 55};
        /**
         * @brief The color of the button when it is not selected
         * 
         */
        const Color _C_UNSELECTED = Color{0, 0, 0, 0};
    };
}

#endif /* !BUTTON_HPP_ */