/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** game.client
*/

#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"

#include "components/Score.hpp"
#include "jepmaker/components/Message.hpp"
#include "jepmaker/components/Position.hpp"
#include "jepmaker/components/Drawable2D.hpp"
#include "jepmaker/components/Clickable2D.hpp"
#include "jepmaker/components/Sprite2DMultiAnim.hpp"

#include "Global.hpp"


static void createBackground(jgo::Client &game)
{
    game.ecs.createEntity();
    game.ecs.emplaceComp<Position2D>(game.ecs.currentEntity, Position2D(0, 0));
    game.ecs.emplaceComp<Drawable>(game.ecs.currentEntity, Drawable(WhackAMole::TEXTURES_PATH.at(WhackAMole::GAME_BACKGROUND), jgo::Rectangle(0, 50, 800, 600)));
}

static void createMole(jgo::Client &game, Position2D &&pos)
{
    const jgo::Rectangle REC = {WhackAMole::WIDTH_MOLE_SPRITE * 0, WhackAMole::HEIGHT_MOLE_SPRITE * 0, WhackAMole::WIDTH_MOLE_SPRITE, WhackAMole::HEIGHT_MOLE_SPRITE};

    game.ecs.createEntity();
    game.ecs.emplaceComp<Position2D>(game.ecs.currentEntity, std::move(pos));
    game.ecs.emplaceComp<Clickable2D>(game.ecs.currentEntity, Clickable2D());
    game.ecs.emplaceComp<Drawable>(game.ecs.currentEntity, Drawable(WhackAMole::TEXTURES_PATH.at(WhackAMole::MOLE_SPRITE), jgo::Rectangle(WhackAMole::WIDTH_MOLE_SPRITE * 0, WhackAMole::HEIGHT_MOLE_SPRITE * 0, WhackAMole::WIDTH_MOLE_SPRITE, WhackAMole::HEIGHT_MOLE_SPRITE), std::vector<float>{0.5, 0.5}));
    game.ecs.emplaceComp<Sprite2DMultiAnim>(game.ecs.currentEntity, Sprite2DMultiAnim(WhackAMole::RECSIZE, WhackAMole::MOLES_ANIM, WhackAMole::SLEEP, 0.2f, 11));
    game.ecs.emplaceComp<Message>(game.ecs.currentEntity, Message("", Position2D(pos.x * 0.5, pos.y * 0.5), 20, 0xa97a1c00));
}

static void createScore(jgo::Client &game)
{
    game.ecs.createEntity();
    game.ecs.emplaceComp(game.ecs.currentEntity, Position2D(10, 180));
    game.ecs.emplaceComp(game.ecs.currentEntity, Score("Score"));
}


exported(void) onStart(jgo::Client &game)
{
    std::vector<std::string> textures;

    game.loadGraphic("Raylib");

    for (auto &t : WhackAMole::TEXTURES_PATH)
        textures.push_back(t.second);

    game.getGraphicLib()->preloadImages(textures);

    game.useComponent<Drawable>();
    game.useComponent<Drawable>("Draw2DSystem");
    game.useComponent<Position2D>();
    game.useComponent<Clickable2D>("HandleMoleBehaviorSystem");
    game.useComponent<Score>();
    game.useComponent<Score>("ScoreSystem");
    game.useComponent<Sprite2DMultiAnim>();
    game.useComponent<Sprite2DMultiAnim>("Sprite2DMultiAnimSystem");
    game.useComponent<Message>();
    game.useComponent<Message>("MessageSystem");

    game.getGraphicLib()->setBackgroundColor(0xffffff);

    createBackground(game);

    for (std::size_t y = 0; y < 4; y++) {
        for (std::size_t x = 0; x < 7; x++) {
            createMole(game, Position2D(110 + (200) * x, 400 + (200) * y));
        }
    }

    createScore(game);
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
