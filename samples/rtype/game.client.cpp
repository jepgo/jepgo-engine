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
#include "jepmaker/components/Game.hpp"
#include "jepmaker/components/Position.hpp"
#include "jepmaker/components/SoundLoop.hpp"
#include "jepmaker/components/Move.hpp"
#include "jepmaker/components/Life.hpp"
#include "jepmaker/components/Hitable2D.hpp"
#include "jepmaker/components/Drawable2D.hpp"
#include "jepmaker/components/SpriteAnimation.hpp"
#include "jepmaker/components/SpriteStatus.hpp"
#include "jepmaker/components/Velocity.hpp"
#include "jepmaker/components/Type.hpp"
#include "jepmaker/components/Enemy.hpp"
#include "jepmaker/components/DoDmg.hpp"
#include "jepmaker/components/Explosion.hpp"
#include "jepmaker/components/MoveToPlayer.hpp"
#include "jepmaker/components/MoveToPlayerTime.hpp"
#include "jepmaker/components/ShortAnimation.hpp"
#include "jepmaker/components/Colision.hpp"
#include "jepmaker/components/ScreenLimit.hpp"
#include "jepmaker/components/Shoot.hpp"
#include "jepmaker/components/LoopMove.hpp"
#include "jepmaker/components/Modules.hpp"
#include "jepmaker/components/Controllable.hpp"
#include "jepmaker/components/Reborn.hpp"
#include "jepmaker/components/DrawReborn.hpp"
#include "jepmaker/components/Exp.hpp"
#include "jepmaker/components/Points.hpp"
#include "jepmaker/components/DrawPoints.hpp"
#include "jepmaker/components/Lvl.hpp"
#include "jepmaker/components/DrawLvl.hpp"
#include "jepmaker/components/DistanceKm.hpp"
#include "jepmaker/components/DrawDistanceKm.hpp"
#include "jepmaker/components/Message.hpp"
#include "jepmaker/components/MessageTime.hpp"
#include "jepmaker/components/Invincible.hpp"
#include "jepmaker/components/InvincibleTime.hpp"
#include "jepmaker/components/Hit.hpp"
#include "jepmaker/components/Death.hpp"
#include "jepmaker/components/Dmg.hpp"
#include "jepmaker/components/BombGeneration.hpp"
#include "jepmaker/components/BombGenerationTime.hpp"
#include "jepmaker/components/AutoShoot.hpp"
#include "jepmaker/components/LvlUp.hpp"
#include "jepmaker/components/Animation2Time.hpp"
#include "jepmaker/components/Free.hpp"
#include "jepmaker/components/ToFree.hpp"
#include "jepmod/exported.hpp"

// this is the function that will be called when starting
exported(void) onStart(jgo::Client &game)
{
    std::cout << "on Start!" << std::endl;
    game.loadGraphic("Raylib");
    game.storage["keys"] = std::vector<jgo::u32>();

    game.useComponent<Positions>("KeySystem", 1);
    game.useComponent<Hitable>("HitSystem", 2);
    game.useComponent<Move>("MoveSystem", 3);
    game.useComponent<Sprite_Animation>("AnimationSpriteSystem", 4);
    game.useComponent<Invincible>("InvincibleSystem", 5);
    game.useComponent<InvincibleTime>("InvincibleTimeSystem", 6);
    game.useComponent<AutoShoot>("AutoShootSystem", 6);
    game.useComponent<Module>("ModuleSystem", 7);
    game.useComponent<DoDmg>("DoDmgSystem", 8);
    game.useComponent<Dmg>("DmgSystem", 9);
    game.useComponent<Free>("FreeSystem", 10);
    game.useComponent<Explosion>("ExplosionSystem", 11);
    game.useComponent<Death>("DeathSystem", 12);
    game.useComponent<Animation2Time>("Animation2TimeSystem", 13);
    game.useComponent<BombGeneration>("BombGenerationSystem", 14);
    game.useComponent<Reborn>("RebornSystem", 15);
    game.useComponent<BombGenerationTime>("BombGenerationTimeSystem", 16);
    game.useComponent<Drawable>("Draw2DSystem", 17);
    game.useComponent<Velocity>();
    game.useComponent<Type>();
    game.useComponent<Sprite_Status>();
    game.useComponent<SoundLoop>();
    game.useComponent<Short_Animation>();
    game.useComponent<Shoot>();
    game.useComponent<ScreenLimit>();
    game.useComponent<MoveToPlayerTime>();
    game.useComponent<MoveToPlayer>();
    game.useComponent<Life>();
    game.useComponent<Enemy>();
    game.useComponent<MoveToPlayer>();
    game.useComponent<MoveToPlayerTime>();
    game.useComponent<LoopMove>();
    game.useComponent<ModuleArmor>();
    game.useComponent<ModuleShoot>();
    game.useComponent<DrawReborn>();
    game.useComponent<Exp>();
    game.useComponent<Points>();
    game.useComponent<DrawPoints>();
    game.useComponent<Lvl>("GameLogic", 18);
    game.useComponent<DrawLvl>();
    game.useComponent<DistanceKm>();
    game.useComponent<DrawKm>();
    game.useComponent<Hit>();
    game.useComponent<Colision>();
    game.useComponent<Controllable>();
    game.useComponent<LvLUp>();
    game.useComponent<Message>();
    game.useComponent<MessageTime>();
    game.useComponent<ToFree>("DestroyerSystem", 19);

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
    Game::CreateBackGround(game);
    //Game::CreateStars(game);
    Game::CreatePlayer(game, 800, 600);
    //Game::CreateBoostModule(game, 1);
    //Game::CreateEasyEnemies(game);
    //Game::CreateObstacle(game);
}

// this is the function that will be called each tick BEFORE rendering and
// system's call.
exported(void) onUpdate(jgo::Client &game)
{
    //std::vector<jgo::u32> tmp = game.getGraphicLib()->getKeyPressed();
    std::vector<jgo::u32> &a = std::any_cast<std::vector<jgo::u32> &>(game.storage["keys"]);
    a = game.getGraphicLib()->getKeyPressed();
    std::vector<jgo::u32> &o = std::any_cast<std::vector<jgo::u32>&>(game.storage["keys"]);

    for (auto &b : o) {
        std::cout << "so = " << b << std::endl;
    }

    //
    //std::cout << "nbr of entity = " << game.ecs.entityNbr() << std::endl;
    return;
}

int main(int ac, char const *const av[])
{
    jgo::Client game(ac, av);
    onStart(game);
    if (game.hasGraphicLib())
        game.getGraphicLib()->openWindow("my windows", {0, 0, 800, 600});
    while (game.hasGraphicLib() ? game.getGraphicLib()->isWindowOpen() : true) {
        //std::this_thread::sleep_for(std::chrono::milliseconds(100));
        onUpdate(game);
        game.getGraphicLib()->update();
        game.callSystems();
    }
    if (game.hasGraphicLib())
        game.getGraphicLib()->closeWindow();
}
