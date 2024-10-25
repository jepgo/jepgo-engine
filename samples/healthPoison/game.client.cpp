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
    game.ecs.emplaceComp<Poison>(game.ecs.currentEntity, Poison(5));
}

exported(void) onUpdate(jgo::Client &game)
{
    auto &healthComponents = game.ecs.getComp<Health>();
    auto &health = healthComponents[game.ecs.currentEntity];

    if (health and not health->isDead())
        std::cout << health->get() << std::endl;
}

int main(int ac, char const *const av[])
{
    jgo::Client game(ac, av);

    onStart(game);
    onlyOnExistPtr(game.getGraphicLib())->openWindow(
        "window", jgo::Rectangle(0, 0, 800, 600)
    );
    while (game.getGraphicLib() ? game.getGraphicLib()->get()->isWindowOpen() : true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        onUpdate(game);
        onlyOnExistPtr(game.getGraphicLib())->update();
        game.callSystems();
    }
    onlyOnExistPtr(game.getGraphicLib())->closeWindow();
}
