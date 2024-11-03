/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** preload
*/

#include "components.hpp"
#include "jepengine/Server.hpp"

void useSystemsAndComponents(jgo::Server &game)
{
    game.useComponent<Position2D>("KeySystem", 1);
    game.useSystem("GameSystem", 0);
    game.useComponent<Hitable>("HitSystem", 2);
    game.useComponent<Move>("MoveSystem", 3);
    game.useComponent<Sprite_Animation>("AnimationSpriteSystem", 4);
    game.useComponent<Invincible>("InvincibleSystem", 5);
    game.useComponent<InvincibleTime>("InvincibleTimeSystem", 6);
    game.useComponent<AutoShoot>("AutoShootSystem", 6);
    game.useComponent<Module>("ModuleSystem", 7);
    game.useSystem("AttachModuleSystem", 8);
    game.useComponent<DoDmg>("DoDmgSystem", 9);
    game.useComponent<Dmg>("DmgSystem", 10);
    game.useComponent<Explosion>("ExplosionSystem", 11);
    game.useSystem("MyFree", 12);
    game.useComponent<Free>("FreeSystem", 13);
    game.useComponent<Death>("DeathSystem", 14);
    game.useComponent<Animation2Time>("Animation2TimeSystem", 14);
    game.useComponent<BombGeneration>("BombGenerationSystem", 15);
    game.useComponent<Reborn>("RebornSystem", 16);
    game.useComponent<BombGenerationTime>("BombGenerationTimeSystem", 17);
    // game.useComponent<DrawKm>("DrawKmSystem", 19);
    // game.useComponent<Drawable>("Draw2DSystem", 18);
    game.useComponent<DrawKm>();
    game.useComponent<Drawable>();
    game.useComponent<Velocity>();
    game.useComponent<Type>();
    game.useComponent<Sprite_Status>();
    game.useComponent<SoundLoop>();
    game.useComponent<Short_Animation>();
    game.useComponent<Shoot>();
    game.useComponent<ScreenLimit>();
    game.useComponent<MoveToPlayerTime>("MoveToPlayerTimeSystem");
    game.useComponent<MoveToPlayer>("MoveToPlayerSystem");
    game.useComponent<MoveTo>("MoveToSystem");
    game.useComponent<Life>();
    game.useComponent<Enemy>();
    game.useComponent<LoopMove>();
    game.useComponent<ModuleArmor>();
    game.useComponent<ModuleShoot>();
    game.useComponent<DrawReborn>("DrawRebornSystem", 19);
    game.useComponent<Exp>();
    game.useComponent<Points>();
    // game.useComponent<DrawPoints>("DrawPointsSystem", 19);
    game.useComponent<DrawPoints>();
    // game.useComponent<Lvl>("GameLogic", 18);
    game.useComponent<Lvl>();
    // game.useComponent<DrawLvl>("DrawLvlSystem", 19);
    game.useComponent<DrawLvl>();
    // game.useComponent<DistanceKm>("GameSystem");
    game.useComponent<DistanceKm>();
    game.useComponent<InvincibleTime>();
    game.useComponent<Hit>();
    game.useComponent<Colision>();
    game.useComponent<Controllable>();
    game.useComponent<LvLUp>();
    game.useComponent<Message>();
    game.useComponent<MessageTime>();
    game.useComponent<ToFree>("DestroyerSystem", 21);
}