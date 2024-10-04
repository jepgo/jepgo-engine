/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** hardcoded
*/

#include "engine/engine.hpp"
#include "hardcoded.hpp"

void jgame::hardcodedSystems(jgame::Client &client)
{
    AttachModuleSystem::system(client.ecs);
    LoopMoveSystem::system(client.ecs,
        client.window.heigth, client.window.width);
    MoveToPlayerTimeSystem::system(client.ecs, client.getTime());
    Animation2TimeSystem::system(client.ecs, client.getTime());
    ShortAnimationSystem::system(client.ecs, client.getTime());
    InvinsibleSystem::system(client.ecs, client.getTime());
    ModuleSystem::system(client.ecs);
    DmgSystem::system(client.ecs, client.getTime());
    ExplosionSystem::system(client.ecs);
    // DeathSystem::system(client.ecs, playerEntity);
    DestoyersSystem::system(client.ecs,
        client.window.heigth, client.window.width);
    // SoundLoopSystem::system(client.ecs, sounds, client.getTime());
    BombGenerationTimeSystem::system(client.ecs, client.getTime());
    BombGenerationSystem::system(client.ecs, client.getTime());
}
