/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Menu
*/

#ifndef MENU_HPP_
    #define MENU_HPP_
    #include <map>
    #include <vector>
    #include <functional>
    #include <raylib.h>
    #include "Button.hpp"
    #include "AnimLine.hpp"
    #include "Clock.hpp"
    #include "LogIcon.hpp"

/**
 * @brief Menu namespace of the game
 * 
 */
namespace Menu {
    /**
     * @brief Class of the main menu game
     * 
     */
    class Menu {
        public:
            /**
             * @brief Construct a new Menu object
             * 
             * @param screenWidth The width of the screen at the creation of the menu
             * @param screenHeight The height of the screen at the creation of the menu
             */
            Menu(const size_t screenWidth, const size_t screenHeight);
            /**
             * @brief Destroy the Menu object
             * 
             */
            ~Menu();

            /**
             * @brief Update the size of the screen
             * 
             * @param screenWidth The new width of the screen
             * @param screenHeight The new height of the screen
             */
            void updateSize(const size_t screenWidth, const size_t screenHeight);
            /**
             * @brief Draw the menu
             * 
             */
            void drawMenu();


        private:
            enum MenuState {
                ENTER_MENU,
                IN_MENU
            };

            void _drawEnterMenu();
            void _drawInMenu();

            const std::map<MenuState, std::function<void ()>> _menuPage = {
                {MenuState::ENTER_MENU, [this](){_drawEnterMenu();}},
                {MenuState::IN_MENU, [this](){_drawInMenu();}}
            };

            /**
             * @brief The background of the menu
             * 
             */
            Texture2D _bckgrnd;
            /**
             * @brief The font used for the menu
             * 
             */
            Font _font;
            /**
             * @brief The position of the title
             * 
             */
            Vector2 _titlePos;

            /**
             * @brief Vector of all the buttons on the menu
             * 
             */
            std::vector<Button> _buttons;

            /**
             * @brief The width of the screen
             * 
             */
            size_t _screenWidth;
            /**
             * @brief The height of the screen
             * 
             */
            size_t _screenHeight;

            /**
             * @brief The lines to animate the screen
             * 
             */
            std::vector<AnimLine> _lines;

            /**
             * @brief The current home page
             * 
             */
            MenuState _state;

            /**
             * @brief To save the opacity of an instruction at time t,
             * and if in the next move we need ton increase (true) or
             * decrease (false) the opacity
             * 
             */
            std::tuple<bool, int> _instructionOpacity;

            /**
             * @brief The clock to handle the opacity instruction animation update
             * 
             */
            Clock _CInstruction;


            bool _inTransition;

            /**
             * @brief To save the opacity of an transition at time t,
             * and if in the next move we need ton increase (true) or
             * decrease (false) the opacity
             * 
             */
            std::tuple<bool, int> _transitionOpacity;

            /**
             * @brief 
             * 
             */
            Clock _CTransition;

            /**
             * @brief The name of the player
             * 
             */
            std::string _playerName;

            /**
             * @brief The icon of the player
             * 
             */
            LogIcon _logIcon;
    };
}
#endif /* !MENU_HPP_ */
