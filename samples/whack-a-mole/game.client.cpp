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
#include "jepmaker/components/Clickable2D.hpp"

#include "Game.hpp"
#include "Global.hpp"

exported(void) onStart(jgo::Client &game)
{
    std::vector<std::string> textures;

    game.loadGraphic("Raylib");

    for (auto &t : WhackAMole::TEXTURES_PATH)
        textures.push_back(t.second);

    game.getGraphicLib()->preloadImages(textures);

    game.useComponent<Drawable>();
    game.useComponent<Drawable>("Draw2DSystem");
    game.useComponent<Positions>();
    game.useComponent<Clickable2D>();

    game.getGraphicLib()->setBackgroundColor(0xffff0000);

    WhackAMole::Game::createBackground(game);

    for (std::size_t y = 0; y < 4; y++) {
        for (std::size_t x = 0; x < 7; x++) {
            WhackAMole::Game::createMole(game, Positions(110 + (200) * x, 400 + (200) * y));
        }
    }
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
