/*
** EPITECH PROJECT, 2024
** whack-a-mole
** File description:
** TextDrawableSystem
*/

#include "TextDrawable.hpp"
#include "TextDrawableSystem.hpp"

void Systems::TextDrawableSystem::system(Register &r)
{
    auto &texts = r.getComp<Components::TextDrawable>();

    for (std::size_t i = 0; i < texts.size(); i++) {
        if (texts[i].has_value() && !texts[i].value().mess.empty()) {
            texts[i].value().Draw();
        }
    }
}
