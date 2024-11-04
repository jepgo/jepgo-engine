/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** game.client
*/

#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"

#include "jepmaker/components/Position.hpp"
#include "jepmaker/components/Drawable2D.hpp"



exported(void) onStart(jgo::Client &game)
{
    std::vector<std::string> textures;

    game.loadGraphic("Raylib");
    game.getGraphicLib()->preloadImages({
        "assets/your-asset.png"
    });

    game.useComponent<Drawable>();
    game.useComponent<Drawable>("Draw2DSystem");
    game.useComponent<Position2D>();

    game.getGraphicLib()->setBackgroundColor(0xffffff);

    game.ecs.createEntity();
    game.ecs.emplaceComp(game.ecs.currentEntity, Position2D(0, 0));
    game.ecs.emplaceComp(game.ecs.currentEntity, Drawable("assets/your-asset.png"));
}

exported(void) onUpdate(jgo::Client &game)
{
}

int main(int ac, char const *const av[])
{
    jgo::Client game(ac, av);

    onStart(game);
    if (game.hasGraphicLib())
        game.getGraphicLib()->openWindow("Whack A Mole", {0, 0, 800, 600});
    while (game.hasGraphicLib() ? game.getGraphicLib()->isWindowOpen() : true) {
        onUpdate(game);
        game.getGraphicLib()->update();
        game.callSystems();
    }
    if (game.hasGraphicLib())
        game.getGraphicLib()->closeWindow();
}
