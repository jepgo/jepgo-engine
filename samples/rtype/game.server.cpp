/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** game.client
*/

#include <iostream>
#include <chrono>
#include <thread>

#include "jepmaker/components/Position.hpp"
#include "jepengine/Server.hpp"
#include "jepmod/exported.hpp"
#include "components.hpp"
#include "jepmaker/components/Game.hpp"

void useSystemsAndComponents(jgo::Server &game);

using KMap = std::map<size_t, std::vector<jgo::u32>>;

exported(void) onStart(jgo::Server &game)
{
    // game.loadGraphic("Raylib");
    game.loadNetworkServer("Asio");

    game.storage["players"] = 0;
    game.storage["keys"] = KMap();
    useSystemsAndComponents(game);

    // game.getGraphicLib()->preloadImages({
    //     "sprites/r-typesheet3.gif",
    //     "sprites/r-typesheet1.gif",
    //     "sprites/r-typesheet2.gif",
    //     "sprites/parallax-space-backgound.png",
    //     "sprites/parallax-space-big-planet.png",
    //     "sprites/r-typesheet32.gif",
    //     "sprites/r-typesheet14.gif",
    //     "sprites/parallax-space-far-planets.png",
    //     "sprites/parallax-space-ring-planet.png",
    //     "sprites/parallax-space-stars.png",
    //     "sprites/asteroid.png",
    //     "sprites/spaceship.png"
    // });
    // Game::CreateBackGround(game);
    // Game::CreateObstacle(game);
    // Game::CreateObstacle(game);
    // Game::CreateObstacle(game);
    // Game::CreateObstacle(game);
    // Game::CreateObstacle(game);
    // Game::CreateObstacle(game);
}

exported(void) onUpdate(jgo::Server &game)
{
    game.sendComponents<Drawable, 0x01>();
    game.sendComponents<Position2D, 0x02>();
}

exported(void) onMessage(jgo::Server &game, jgo::NetMessage const &msg)
{
    std::string str(msg.first.begin(), msg.first.end());
    std::string who = msg.second->getIP() + ":";

    who += msg.second->getPort();
    std::cout << "received " << str << " from " << who << std::endl;

    if (msg.first[0] == jgo::NEW_PLAYER_BYTE) {

        auto &players = std::any_cast<int &>(game.storage["players"]);
        if (players >= 4)
            return;
        Game::CreatePlayer(game, 800, 600);
        game.storage[who] = game.ecs.currentEntity;
        ++players;
        auto zizi = std::any_cast<KMap &>(game.storage["keys"]);
        auto e = std::any_cast<int>(game.storage[who]);
        zizi[e] = {0, 0, 0, 0};

    } else if (msg.first[0] == jgo::DIRECTION_BYTE) {
        std::vector<jgo::u8> caca = msg.first;
        std::vector<jgo::u32> foo;
        CBuffer<jgo::u32> buf(4);

        caca.erase(caca.begin());
        buf.fill(caca.data());
        for (int n = 0; n < 4; ++n)
            foo.emplace_back(buf[n]);

        auto &zizi = std::any_cast<KMap &>(game.storage["keys"]);
        auto e = std::any_cast<int>(game.storage[who]);
        std::cout << "== input ==" << std::endl;
        zizi[e] = foo;
        for (auto const &n : foo)
            std::cout << n << std::endl;
    }
}

int main(int ac, char const *const av[])
{
    jgo::Server game(ac, av);

    onStart(game);
    if (game.hasGraphicLib())
        game.getGraphicLib()->openWindow("my windows", {0, 0, 800, 600});
    if (game.hasNetwork()) game.host(4242);
    while (game.hasGraphicLib() ? game.getGraphicLib()->isWindowOpen() : true) {
        if (game.hasNetwork()) for (auto const &msg : game.getMessages())
                onMessage(game, msg);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        onUpdate(game);
        game.callSystems();
        if (game.hasGraphicLib()) game.getGraphicLib()->update();
        if (game.lua) game.lua->callAllSystems();
    }
    if (game.hasGraphicLib()) game.getGraphicLib()->closeWindow();
}
