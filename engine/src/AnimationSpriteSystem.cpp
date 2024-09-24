/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** AnimationSpriteSystem
*/

#include "AnimationSpriteSystem.hpp"

AnimationSpriteSystem::AnimationSpriteSystem()
{
}

AnimationSpriteSystem::~AnimationSpriteSystem()
{
}

/**
 * @brief Function who check the Sprite Animations
 * 
 * @param r The Registry
 * @param time The current time
 */
void AnimationSpriteSystem::system(Register &r, sf::Time &time)
{
    //sf::Time time = clock.getElapsedTime();
    auto &rec = r.getComp<Sprite_Animation>();
    auto &draw = r.getComp<Drawable>();

    for (std::size_t i = 0; i < rec.size(); i++) {
        if (rec[i].has_value() && draw[i].has_value() && time.asSeconds() - rec[i].value().t >= rec[i].value().reset)
        {
            draw[i].value().getRect().value().left += rec[i].value().val;
            if ((rec[i].value().isneg == false) && draw[i].value().getRect().value().left >= (rec[i].value().status) * rec[i].value().val) {
                if (rec[i].value().deadAnimation == true) {
                    r.removeComponent<Drawable>(i);
                    r.removeComponent<Sprite_Animation>(i);
                } else
                    draw[i].value().getRect().value().left = draw[i].value().start;
            }
            else if ((rec[i].value().isneg == true) && draw[i].value().getRect().value().left <= (rec[i].value().status) * rec[i].value().val) {
                if (rec[i].value().deadAnimation == true) {
                    r.removeComponent<Drawable>(i);
                    r.removeComponent<Sprite_Animation>(i);
                } else
                draw[i].value().getRect().value().left = draw[i].value().start;
            }
            if (rec[i].has_value()) {
                rec[i].value().t = time.asSeconds();
            }
        }
    }
}