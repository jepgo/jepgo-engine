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
            DrawKmSystem::system(base.ecs);
            DrawLvlSystem::system(base.ecs);
            DrawPointsSystem::system(base.ecs);
            DrawRebornSystem::system(base.ecs);
            MessageSystem::system(base.ecs);
            base.systems.draw.system(base.ecs, base.textures);
            if (base.settings.use3D) {
                Rotation3DSystem::system(base.ecs, base.getTime(), base.models);
                BeginMode3D(base.tools3D.camera);
                base.systems.draw3D.system(base.ecs, base.getTime(), base.models);
                EndMode3D();
            }
        } else {
            base.systems.move.system(base.ecs, base.getTime());
            // DmgSystem::system(base.ecs, base.getTime());
            // ExplosionSystem::system(base.ecs); TODO: update to use with sounds
            // DeathSystem::system(base.ecs, playerEntity);
            // SoundLoopSystem::system(base.ecs, sounds, base.getTime());
            // DetachModulesSystem::system(base.ecs, base.getTime(), key);
            // SystemGame.system(base.ecs, base.getTime(), playerEntity);
            // LoopMoveSystem::system(base.ecs, height, width);
            // SystemMoveTo.system(base.ecs, base.getTime());
            // movetoplayer.system(base.ecs, base.getTime());
            // moveSys.system(base.ecs, base.getTime());
            Animation2TimeSystem::system(base.ecs, base.getTime());
            // animSys.system(base.ecs, base.getTime());
            // RebornSystem::system(base.ecs, playerEntity, base.getTime(), key);
            // DestoyersSystem::system(base.ecs, height, width);
            // SoundLoopSystem::system(base.ecs, sounds, base.getTime());

            // AttachModuleSystem::system(base.ecs);
            // MoveToPlayerTimeSystem::system(base.ecs, base.getTime());
            // Animation2TimeSystem::system(base.ecs, base.getTime());
            // ShortAnimationSystem::system(base.ecs, base.getTime());
            // InvinsibleSystem::system(base.ecs, base.getTime());
            // ModuleSystem::system(base.ecs);
            // BombGenerationTimeSystem::system(base.ecs, base.getTime());
            // BombGenerationSystem::system(base.ecs, base.getTime());
            // MoveToPlayerTimeSystem::system(base.ecs, base.getTime());
            // AutoShootSystem::system(base.ecs, base.getTime());
            // ShortAnimationSystem::system(base.ecs, base.getTime());
            // InvinsibleSystem::system(base.ecs, base.getTime());
            // AttachModuleSystem::system(base.ecs);
            // BombGenerationTimeSystem::system(base.ecs, base.getTime());
            // BombGenerationSystem::system(base.ecs, base.getTime());
            // ModuleSystem::system(base.ecs);
            // DmgSystem::system(base.ecs, base.getTime());
            // ExplosionSystem::system(base.ecs, 3);
            // base.systems.addDmg.system(base.ecs, base.getTime());
            // base.systems.hit.system(base.ecs);
            // MessageTimeSystem::system(base.ecs, base.getTime());

            std::optional<jgo::ConnectionRef> client = base.getFirstClient();
            if (client) {
                jgo::Connection &ref = client->get();
                try {
                    int n = std::any_cast<int>(ref.storage["id"]);
                    // DeathSystem::system(base.ecs, n);
                    // base.systems.test.Stages(base.ecs, base.getTime(), n);
                } catch(std::exception const &) {}
            }
        }
    }, something);
}
