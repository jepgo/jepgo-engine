/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** AnimationSpriteSystem
*/

<<<<<<<< HEAD:src/jepmaker/systems/AnimationSpriteSystem.cpp
#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"
#include "jepmaker/components/SpriteAnimation.hpp"
#include "jepmaker/components/Drawable2D.hpp"

/**
 * @brief Function who check the Sprite Animations
 * 
 * @param r The Registry
 * @param time The current time
 */
exported(void) jepgoSystem(jgo::Game &game, float time)
{
    auto &rec = game.ecs.getComp<Sprite_Animation>();
    auto &draw = game.ecs.getComp<Drawable>();
========
#include "AnimationSpriteSystem.hpp"

#include "Position.hpp"
#include "Drawable.hpp"
#include "Sprite_Animation.hpp"

Systems::AnimationSpriteSystem::AnimationSpriteSystem()
{
}

Systems::AnimationSpriteSystem::~AnimationSpriteSystem()
{
}

void Systems::AnimationSpriteSystem::system(Register &r, float time)
{
    auto &rec = r.getComp<Components::Sprite_Animation>();
    auto &draw = r.getComp<Components::Drawable>();
>>>>>>>> origin/dev:whack-a-mole/engine/src/systems/AnimationSpriteSystem.cpp

    for (std::size_t i = 0; i < rec.size(); i++) {
        if (rec[i].has_value() && draw[i].has_value() && game.getTime() - rec[i].value().t >= rec[i].value().reset)
        {
            draw[i].value().getRect().value().x += rec[i].value().val;
            if ((rec[i].value().isneg == false) && draw[i].value().getRect().value().x >= (rec[i].value().status) * rec[i].value().val + draw[i].value().start) {
                if (rec[i].value().deadAnimation == true) {
<<<<<<<< HEAD:src/jepmaker/systems/AnimationSpriteSystem.cpp
                    game.ecs.removeComponent<Drawable>(i);
                    game.ecs.removeComponent<Sprite_Animation>(i);
========
                    r.removeComponent<Components::Drawable>(i);
                    r.removeComponent<Components::Sprite_Animation>(i);
>>>>>>>> origin/dev:whack-a-mole/engine/src/systems/AnimationSpriteSystem.cpp
                } else
                    draw[i].value().getRect().value().x = draw[i].value().start;
            }
            else if ((rec[i].value().isneg == true) && draw[i].value().getRect().value().x <= (rec[i].value().status) * rec[i].value().val + draw[i].value().start) {
                if (rec[i].value().deadAnimation == true) {
<<<<<<<< HEAD:src/jepmaker/systems/AnimationSpriteSystem.cpp
                    game.ecs.removeComponent<Drawable>(i);
                    game.ecs.removeComponent<Sprite_Animation>(i);
========
                    r.removeComponent<Components::Drawable>(i);
                    r.removeComponent<Components::Sprite_Animation>(i);
>>>>>>>> origin/dev:whack-a-mole/engine/src/systems/AnimationSpriteSystem.cpp
                } else
                draw[i].value().getRect().value().x = draw[i].value().start;
            }
            if (rec[i].has_value()) {
                rec[i].value().t = game.getTime();
            }
        }
    }
}