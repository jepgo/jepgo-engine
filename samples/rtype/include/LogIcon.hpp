/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** LogIcon
*/

#ifndef LOGICON_HPP_
    #define LOGICON_HPP_
    #include <string>    
    #include <raylib.h>
    #include <stddef.h>
    #include <functional>

/**
 * @brief Menu namespace of the game
 * 
 */
namespace Menu {
    /**
     * @brief This class is a simple icon for the log
     * 
     */
    class LogIcon {
        public:
            /**
             * @brief Construct a new Log Icon object
             * 
             * @param x The x position of the icon
             * @param y The y position of the icon
             * @param width The width of the icon
             * @param height The height of the icon
             * @param screenWidth The width of the screen
             * @param screenHeight The height of the screen
             * @param text The text of the icon
             * @param font The font of the icon
             */
            LogIcon(
                const size_t x,
                const size_t y,
                const size_t width,
                const size_t height,
                const float screenWidth,
                const float screenHeight,
                const std::string text,
                Font &font,
                std::function<int ()> onClick
            );

            /**
             * @brief Destroy the Log Icon object
             * 
             */
            ~LogIcon();


            /**
             * @brief Draw the icon
             * 
             */
            void drawIcon();

            /**
             * @brief Set the Text object
             * 
             * @param text The text of the icon
             */
            void setText(const std::string &text) { _text = text; }

            /**
             * @brief Update the size of the width
             * 
             * @param screenWidth The new width of the screen
             * @param screenHeight The new height of the screen
             */
            void updateSize(const float screenWidth, const float screenHeight);

        private:
            /**
             * @brief The x position of the icon
             * 
             */
            size_t _x;

            /**
             * @brief The y position of the icon
             * 
             */
            size_t _y;

            /**
             * @brief The width of the icon
             * 
             */
            size_t _width;

            /**
             * @brief The height of the icon
             * 
             */
            size_t _height;

            /**
             * @brief The text of the icon
             * 
             */
            std::string _text;

            /**
             * @brief The font of the icon
             * 
             */
            Font &_font;

            /**
             * @brief The state of the icon
             * 
             */
            bool _isOpen;

            /**
             * @brief The icon of the icon
             * 
             */
            Texture2D _icon;

            float _screenWidth;
            float _screenHeight;

            std::function<int ()> _onClick;


            /**
             * @brief The state of the icon
             * 
             */
            bool _isSelect;




            /**
             * @brief The color of the border
             * 
             */
            const Color _C_BORDER = Color{ 175, 175, 175, 255};

            /**
             * @brief The color of the unselected icon
             * 
             */
            const Color _C_UNSELECTED = Color{ 0, 0, 0, 100 };

            /**
             * @brief The color of the selected icon
             * 
             */
            const Color _C_SELECTED = Color{ 0, 0, 0, 200 };

    
            void _isSelectIcon();

    };
}

#endif /* !LOGICON_HPP_ */