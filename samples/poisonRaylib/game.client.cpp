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

// this is the function that will be called when starting
exported(void) onStart(jgo::Client &game)
{
    // we first load the 'raylib' graphic library
    game.loadGraphic("Raylib");

    // then, we say we are using Health and Poison
    game.useComponent<Health>();
    game.useComponent<Poison>("Poison");

    // we then create an entity, that have Health (100 hp)
    // and then we create the poison component, that deals 5 damage each second
    game.ecs.createEntity();
    game.ecs.emplaceComp<Health>(game.ecs.currentEntity, Health(100));
    game.ecs.emplaceComp<Poison>(game.ecs.currentEntity, Poison(5, 0.1));

    // and finally, we preload the account image.
    game.getGraphicLib()->preloadImages({
        "sprites/account.png"
    });

    game.getGraphicLib()->setBackgroundColor(0xffff0000);
}

// this is the function that will be called each tick BEFORE rendering and
// system's call.
exported(void) onUpdate(jgo::Client &game)
{
    // we get our unique entity's health
    auto &healthComponents = game.ecs.getComp<Health>();
    auto &health = healthComponents[game.ecs.currentEntity];

    // if it have the component health, we just return.
    if (not health)
        return;

    // if he is still not dead, we can display him, else, we just remove
    // the health and poison component.
    if (not health->isDead()) {
        game.getGraphicLib()->drawImage(
            "sprites/account.png",
            {1, 1, 230, 250},
            {1, 1}
        );
    } else {
        std::cout << std::boolalpha;
        std::cout
            << static_cast<bool>(healthComponents[game.ecs.currentEntity])
            << std::endl;
        game.ecs.removeComponents<Health, Poison>(game.ecs.currentEntity);
        std::cout
            << static_cast<bool>(healthComponents[game.ecs.currentEntity])
            << std::endl;
        std::cout << std::dec;
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
