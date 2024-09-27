/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Text
*/

#include "Text.hpp"
#include "Register.hpp"

void Text::system(Register &r, sf::RenderWindow &window)
{
    auto &text = r.getComp<Text>();
    auto &pos = r.getComp<Positions>();

    for (std::size_t i = 0; i < text.size(); i++) {
        if (text[i].has_value() && pos[i].has_value()) {
            //std::cout << "text draw" << std::endl;
            text[i].value().draw(window, pos[i].value());
        }
    }
};