/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** TextDrawable
*/

#pragma once
#include "Register.hpp"

class TextDrawable {
    public:
        TextDrawable(Positions &&pos, std::size_t size, Color color);
        ~TextDrawable();
        void Draw(std::string mess);
    private:
        Positions _pos;
        std::size_t _size;
        Color _color;
};
