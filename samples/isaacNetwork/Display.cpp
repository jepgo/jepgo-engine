#include <iostream>
#include "jepengine/Game.hpp"
#include "jepmaker/components/Position.hpp"

exported(void) jepgoSystem(jgo::Game &game, float &time)
{
    float const now = static_cast<float>(game.getTime());

    if (now - time < 0.1f)
        return;
    time = now;
    auto &poses = game.ecs.getComp<Position2D>();
    for (size_t n = 0; n < poses.size(); ++n) {
        if (not poses[n])
            continue;
        game.getGraphicLib()->drawImage(
            jmod::EasyLife(game.argv[0])/"isaac.png",
            jgo::Rectangle(0, 0, 500, 500),
            jgo::Rectangle(poses[n]->x, poses[n]->y, 100, 100),
            jgo::Vector2(1, 1)
        );
    }
}