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
#include "jepmod/exported.hpp"

exported(void) onStart(jgo::Client &game)
{
    game.loadGraphic("Raylib");

    game.useComponent<Health>();
    game.useComponent<Poison>("Poison");

    game.ecs.createEntity();
    game.ecs.emplaceComp<Health>(game.ecs.currentEntity, Health(100));
    game.ecs.emplaceComp<Poison>(game.ecs.currentEntity, Poison(5, 1.0));

    game.getGraphicLib()->preloadImages({
        "sprites/account.png"
    });
}

exported(void) onUpdate(jgo::Client &game)
{
    auto &healthComponents = game.ecs.getComp<Health>();
    auto &health = healthComponents[game.ecs.currentEntity];

    if (health and not health->isDead()) {
        game.getGraphicLib()->drawImage(
            "sprites/account.png",
            {100, 100, 230, 250},
            {0.5, 0.5}
        );
        std::cout << health->get() << std::endl;
    }
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
