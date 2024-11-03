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
    #include "jepengine/Client.hpp"
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
            Menu(const size_t screenWidth, const size_t screenHeight, jgo::Client &game);
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
            int drawMenu();


        private:
            enum MenuState {
                ENTER_MENU,
                IN_MENU,
                OPTION_MENU,
                LOGREG_MENU
            };

            void _startTransition(MenuState state);

            int _drawEnterMenu();
            int _drawInMenu();
            int _drawOptionMenu();
            int _drawLogRegMenu();    

            const std::map<MenuState, std::function<int ()>> _menuPage = {
                {MenuState::ENTER_MENU, [this](){ return _drawEnterMenu(); }},
                {MenuState::IN_MENU, [this](){ return _drawInMenu(); }},
                {MenuState::OPTION_MENU, [this](){ return _drawOptionMenu(); }},
                {MenuState::LOGREG_MENU, [this](){ return _drawLogRegMenu(); }}
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
            std::vector<Button> _optionButtons;

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

            MenuState _nxtState;

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