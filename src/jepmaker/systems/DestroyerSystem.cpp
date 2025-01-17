/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** DestroyerSystem
*/

#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"
#include "jepmaker/components/Position.hpp"
#include "jepmaker/components/Drawable2D.hpp"
#include "jepmaker/components/Life.hpp"
#include "jepmaker/components/Hitable2D.hpp"
#include "jepmaker/components/Colision.hpp"
#include "jepmaker/components/ToFree.hpp"

/**
 * @brief The CheckPosition
 * 
 * @param pos Position obj
 * @param height the height of the obj
 * @param width the width of the obj
 * @return true 
 * @return false 
 */
static bool checkPosition(Position2D &pos, int height, int width)
{
    if (pos.x > width * 10)
        return true;
    if (pos.y > height * 10)
        return true;
    if (pos.x < -width)
        return true;
    if (pos.y < -height)
        return true;
    return false;
}

/**
 * @brief The DestroyerSystem
 * 
 */
exported(void) jepgoSystem(jgo::Game &game, float time)
{
    auto &life = game.ecs.getComp<Life>();
    auto &pos = game.ecs.getComp<Position2D>();

    for (std::size_t i = 0; i < pos.size(); i++) {
        if (pos[i].has_value() && checkPosition(pos[i].value(), 600, 800)) {
            game.ecs.removeComponent<Hitable>(i);
            game.ecs.removeComponent<Drawable>(i);
            game.ecs.removeComponent<Colision>(i);
            game.ecs.emplaceComp(i, ToFree());
        }
    }
}