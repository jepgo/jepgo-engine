/*
** EPITECH PROJECT, 2024
** whack-a-mole
** File description:
** TextDrawableSystem
*/

#ifndef TEXTDRAWABLESYSTEM_HPP_
    #define TEXTDRAWABLESYSTEM_HPP_
    #include "Register.hpp"

namespace Systems {

    class TextDrawableSystem {
        public:
            TextDrawableSystem() {};
            ~TextDrawableSystem() = default;

            void system(Register &r);
        protected:
        private:
    };
}

#endif /* !TEXTDRAWABLESYSTEM_HPP_ */
