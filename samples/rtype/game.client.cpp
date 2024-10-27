/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** a
*/

#include <iostream>
#include <chrono>
#include <thread>

#include "jepengine/Client.hpp"
#include "jepmaker/components/Health.hpp"
#include "jepmaker/components/Poison.hpp"
#include "jepmaker/components/Position.hpp"
#include "jepmaker/components/Drawable2D.hpp"
#include "jepmod/exported.hpp"

// this is the function that will be called when starting
exported(void) onStart(jgo::Client &game)
{
    game.loadGraphic("Raylib");
    game.useComponent<Positions>();
    game.useComponent<Drawable>("Draw2DSystem");

    game.getGraphicLib()->preloadImages({
        "sprites/r-typesheet3.gif",
        "sprites/r-typesheet1.gif",
        "sprites/r-typesheet2.gif",
        "sprites/parallax-space-backgound.png",
        "sprites/parallax-space-big-planet.png",
        "sprites/r-typesheet32.gif",
        "sprites/r-typesheet14.gif",
        "sprites/parallax-space-far-planets.png",
        "sprites/parallax-space-ring-planet.png",
        "sprites/parallax-space-stars.png",
        "sprites/asteroid.png",
        "sprites/spaceship.png"
    });

    game.ecs.createEntity();
    game.ecs.emplaceComp<Positions>(game.ecs.currentEntity, Positions(200, 400));
    game.ecs.emplaceComp<Drawable>(game.ecs.currentEntity, Drawable("sprites/r-typesheet1.gif", jgo::Rectangle{202, 0, 30, 18}, std::vector<float>{1.5, 1.5}));
}

// this is the function that will be called each tick BEFORE rendering and
// system's call.
exported(void) onUpdate(jgo::Client &game)
{
    return;
}

int main(int ac, char const *const av[])
{
    jgo::Client game(ac, av);

    onStart(game);
    if (game.hasGraphicLib())
        game.getGraphicLib()->openWindow("my windows", {0, 0, 800, 600});
    while (game.hasGraphicLib() ? game.getGraphicLib()->isWindowOpen() : true) {
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
        onUpdate(game);
        game.getGraphicLib()->update();
        game.callSystems();
    }
    if (game.hasGraphicLib())
        game.getGraphicLib()->closeWindow();
}
