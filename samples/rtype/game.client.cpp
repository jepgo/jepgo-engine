/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** game.client
*/

#include <iostream>
#include <chrono>
#include <thread>

#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"
#include "jepmaker/components/Position.hpp"
#include "jepmaker/components/Game.hpp"
#include "jepmaker/components/Drawable2D.hpp"

exported(void) onStart(jgo::Client &game)
{
    game.loadGraphic("Raylib");
    game.loadNetworkClient("Asio");

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
    // Game::CreateBackGround(game);
    // Game::CreateStars(game);
    // Game::CreatePlayer(game, 800, 600);
    // Game::CreateShootModule(game, Position2D(300, 300));
    // Game::CreateShootModule(game, Positions(600, 300));
    // Game::CreateBoostModule(game, 1);
    // Game::CreateEasyEnemies(game);
    // Game::CreateObstacle(game);

    game.useComponent<Position2D>();
    game.useComponent<Drawable>("Draw2DSystem");
}

exported(void) onBegin(jgo::Client &game)
{
    std::vector<jgo::u8> const &v = {jgo::NEW_PLAYER_BYTE};
    game.sendToServer(v);
}

exported(void) onUpdate(jgo::Client &game)
{
    // std::vector<jgo::u32> &a = std::any_cast<std::vector<jgo::u32> &>(game.storage["keys"]);
    std::vector<jgo::u32> const &v = game.getGraphicLib()->getKeyPressed();
    int it = 0;
    std::vector<jgo::u32> nv = {0, 0, 0, 0};
    std::vector<jgo::u8> vv;
    CBuffer<jgo::u32> buf(4);

    for (jgo::u32 const &k : v) {
        if (it < 4) {
            nv[it] = (k);
            ++it;
        } else break;
    }
    buf.fill(nv.data());
    // if (nv[0] == 0 and nv[1] == 0 and nv[2] == 0 and nv[3] == 0)
    //     return;
    vv = buf.toBytes();
    vv.insert(vv.begin(), jgo::DIRECTION_BYTE);
    game.sendToServer(vv);
}

exported(void) onServerMessage(jgo::Client &game, std::vector<jgo::u8> const &msg)
{
    if (game.maybeTreatComponent<Drawable, 0x01>(msg)) {
        std::cout << "receive drawable" << std::endl;
        return;
    }
    if (game.maybeTreatComponent<Position2D, 0x02>(msg)) {
        std::cout << "receive drawable" << std::endl;
        return;
    }
}

int main(int ac, char const *const av[])
{
    jgo::Client game(ac, av);
    onStart(game);
    if (game.hasNetwork()) game.connect("localhost", 4242);
    if (game.hasGraphicLib())
        game.getGraphicLib()->openWindow("my windows", {0, 0, 800, 600});
    onBegin(game);
    while (game.hasGraphicLib() ? game.getGraphicLib()->isWindowOpen() : true) {
        if (game.hasNetwork()) {
            auto const msg = game.getServerMessage();
            if (not msg.empty()) onServerMessage(game, msg);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        onUpdate(game);
        if (game.hasGraphicLib()) game.getGraphicLib()->update();
        game.callSystems();
        if (game.lua) game.lua->callAllSystems();
    }
    if (game.hasGraphicLib()) game.getGraphicLib()->closeWindow();
}
