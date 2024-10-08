/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** hardcoded
*/

#include "engine/engine.hpp"
#include "hardcoded.hpp"

/// FIXME: hardcoded
void jgame::hardcodedSystems(EitherRef<Client, Server> something)
{
    std::visit([](auto &&arg) {
        using T = std::decay_t<decltype(arg)>;
        auto &base = arg.get();

        if constexpr (std::is_same_v<T, std::reference_wrapper<Client>>) {
            LoopMoveSystem::system(base.ecs,
                base.window.heigth, base.window.width);
            DestoyersSystem::system(base.ecs,
                base.window.heigth, base.window.width);
            base.systems.draw.system(base.ecs, base.textures);
        } else {
            base.systems.move.system(base.ecs, base.getTime());
        }
        AttachModuleSystem::system(base.ecs);
        MoveToPlayerTimeSystem::system(base.ecs, base.getTime());
        Animation2TimeSystem::system(base.ecs, base.getTime());
        ShortAnimationSystem::system(base.ecs, base.getTime());
        InvinsibleSystem::system(base.ecs, base.getTime());
        ModuleSystem::system(base.ecs);
        DmgSystem::system(base.ecs, base.getTime());
        // ExplosionSystem::system(base.ecs); TODO: update to use with sounds
        BombGenerationTimeSystem::system(base.ecs, base.getTime());
        BombGenerationSystem::system(base.ecs, base.getTime());
        // DeathSystem::system(base.ecs, playerEntity);
        // SoundLoopSystem::system(base.ecs, sounds, base.getTime());
    }, something);
}
