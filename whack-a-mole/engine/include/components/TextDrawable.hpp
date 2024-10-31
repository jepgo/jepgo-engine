/*
** EPITECH PROJECT, 2024
** whack-a-mole
** File description:
** TextDrawable
*/

#ifndef TEXTDRAWABLE_HPP_
    #define TEXTDRAWABLE_HPP_
    #include <string>
    #include <raylib.h>
    #include "Position.hpp"

namespace Components {

    class TextDrawable {
        public:
            TextDrawable(std::string const &mess, Positions &&pos, std::size_t size, Color color);
            ~TextDrawable();
            void Draw();
    
            std::string mess;
        private:
            Positions _pos;
            std::size_t _size;
            Color _color;
    };
}

#endif /* !TEXTDRAWABLE_HPP_ */
