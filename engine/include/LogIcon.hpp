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
             * @param text The text of the icon
             * @param font The font of the icon
             */
            LogIcon(
                const size_t x,
                const size_t y,
                const size_t width,
                const size_t height,
                const std::string text,
                Font &font
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
