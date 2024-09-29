/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** ShortAnimationSystem
*/

#include "ShortAnimationSystem.hpp"

void ShortAnimationSystem:: system(Register &r, sf::Time &time)
{
    auto &rec = r.getComp<Short_Animation>();
    auto &draw = r.getComp<Drawable>();

    for (std::size_t i = 0; i < rec.size(); i++) {
        if (rec[i].has_value() && draw[i].has_value() && time.asSeconds() - rec[i].value().t >= rec[i].value().reset)
        {
            draw[i].value().getRect().value().left += rec[i].value().val;
            //std::cout << "valeur = " << draw[i].value().getRect().value().left << std::endl;
            if ((rec[i].value().isneg == false) && draw[i].value().getRect().value().left >= (rec[i].value().status) * rec[i].value().val) {
                r.removeComponent<Short_Animation>(i);
                //std::cout << "i remove" << std::endl;
            }
            else if ((rec[i].value().isneg == true) && draw[i].value().getRect().value().left <= (rec[i].value().status) * rec[i].value().val + draw[i].value().start) {
                r.removeComponent<Short_Animation>(i);
            }
            if (rec[i].has_value()) {
                rec[i].value().t = time.asSeconds();
            }
        }
    }
}