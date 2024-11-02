#include <iostream>
#include "jepengine/Game.hpp"
#include "jepmaker/components/Position.hpp"
#include "Direction.hpp"

exported(void) jepgoSystem(jgo::Game &game, float &time)
{
    float const now = static_cast<float>(game.getTime());
    if (now - time < 0.1f)
        return;
    time = now;

    auto &poses = game.ecs.getComp<Position2D>();
    auto &dirs = game.ecs.getComp<Direction>();
    int const velocity = 10;
    for (size_t n = 0; n < poses.size(); ++n) {
        if (not poses[n] or not dirs[n])
            continue;

        if (dirs[n]->dir == Direction::Enum::Left)
            poses[n]->x -= velocity;
        else
            poses[n]->x += velocity;

        if (poses[n]->x <= 200)
            dirs[n]->dir = Direction::Enum::Right;
        else if (poses[n]->x >= 400)
            dirs[n]->dir = Direction::Enum::Left;

    }
}