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
#include "jepmod/exported.hpp"

// this is the function that will be called when starting
exported(void) onStart(jgo::Client &game)
{
    game.loadGraphic("Raylib");
    game.useComponent<Positions>("KeySystem");
    game.useComponent<Hitable>("HitSystem");
    game.useComponent<Move>("MoveSystem");
    game.useComponent<Sprite_Animation>("AnimationSpriteSystem");
    game.useComponent<Invincible>("InvincibleSystem");
    game.useComponent<AutoShoot>("AutoShootSystem");
    game.useComponent<Module>("ModuleSystem");
    game.useComponent<DoDmg>("DoDmgSystem");
    game.useComponent<Dmg>("DmgSystem");
    game.useComponent<Death>("DeathSystem");
    game.useComponent<Explosion>("ExplosionSystem");
    game.useComponent<Animation2Time>("Animation2TimeSystem");
    game.useComponent<BombGeneration>("BombGenerationSystem");
    game.useComponent<BombGenerationTime>("BombGenerationTimeSystem");
    game.useComponent<Drawable>("Draw2DSystem");
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
    game.useComponent<Reborn>();
    game.useComponent<DrawReborn>();
    game.useComponent<Exp>();
    game.useComponent<Points>();
    game.useComponent<DrawPoints>();
    game.useComponent<Lvl>("GameLogic");
    game.useComponent<DrawLvl>();
    game.useComponent<DistanceKm>();
    game.useComponent<DrawKm>();
    game.useComponent<InvincibleTime>();
    game.useComponent<Hit>();
    game.useComponent<Colision>();
    game.useComponent<Controllable>();
    game.useComponent<LvLUp>();

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
        "sprites/parallax-space-stars.png"
    });
    Game::CreatePlayer(game, 800, 600);
    Game::CreateBoostModule(game, 0);
    Game::CreateEasyEnemies(game);
    //Game::CreateObstacle(game);
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
