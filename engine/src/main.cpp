/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <vector>
#include <stddef.h>
#include <raylib.h>
#include <iostream>
#include "DrawKmSystem.hpp"
#include "DrawLvlSystem.hpp"
#include "MessageSystem.hpp"
#include "DrawPointsSystem.hpp"
#include "MoveToPlayerSystem.hpp"
#include "Animation2TimeSystem.hpp"
#include "BombGenerationSystem.hpp"
#include "BombGenerationTimeSystem.hpp"
#include "MoveToPlayerTimeSystem.hpp"
#include "InvinsibleSystem.hpp"
#include "LoopMoveSystem.hpp"
#include "DestroyerSystem.hpp"
#include "ShortAnimationSystem.hpp"
#include "SoundLoopSystem.hpp"
#include "AddDmgSystem.hpp"
#include "GameSystem.hpp"
#include "TestGame.hpp"
#include "Game.hpp"
#include "DeathSystem.hpp"
#include "AttachModuleSystem.hpp"
#include "DmgSystem.hpp"
#include "ModuleSystem.hpp"
#include "HitSystem.hpp"
#include "DrawSystem.hpp"
#include "Register.hpp"
#include "Components.hpp"
#include "ExplosionSystem.hpp"
#include "SparseArray.hpp"
#include "MoveSystem.hpp"
#include "AnimationSpriteSystem.hpp"

int main(void)
{
    size_t screenWidth = 800, screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "rtype");
    InitAudioDevice();
    Register r;
    Game::CreateBackGround(r);
    Game::CreatePlanet(r);
    Game::CreatPlayer(r, height, width);
    playerEntity = r.currentEntity;
    float startTime = GetTime();
    Game player = Game();
    AddDmgSystem addDmgSystem = AddDmgSystem(0.1);
    TestGame game = TestGame(1);
    GameSystem SystemGame = GameSystem(0.1);
    MoveSystem moveSys = MoveSystem(0.01);
    HitSystem hitSys = HitSystem();
    DrawSystem drawSys = DrawSystem();
    MoveToPlayerSystem movetoplayer = MoveToPlayerSystem(0.3);
    AnimationSpriteSystem animSys = AnimationSpriteSystem();
    std::vector<Sound> sounds = getAllSound({"sprites/test.ogg", "sprites/level1.ogg", "sprites/laser.wav"});
    std::vector<Texture2D> texture = getAllTexture({ "sprites/r-typesheet3.gif", "sprites/r-typesheet1.gif", "sprites/r-typesheet2.gif", "sprites/parallax-space-backgound.png", "sprites/parallax-space-big-planet.png", "sprites/r-typesheet32.gif", "sprites/r-typesheet14.gif"});

    r.creatEntity();
    r.emplace_comp(r.currentEntity, SoundLoop(1));
    while (!WindowShouldClose()) {
        float time = GetTime() - startTime;
        keySystem(r, time, sounds);
        hitSys.system(r);
        AttachModuleSystem::system(r);
        SystemGame.system(r, time, playerEntity);
        LoopMoveSystem::system(r, height, width);
        MoveToPlayerTimeSystem::system(r, time);
        movetoplayer.system(r, time);
        moveSys.system(r, time);
        Animation2TimeSystem::system(r, time);
        animSys.system(r, time);
        ShortAnimationSystem::system(r, time);
        InvinsibleSystem::system(r, time);
        addDmgSystem.system(r, time);
        ModuleSystem::system(r);
        DmgSystem::system(r, time);
        ExplosionSystem::system(r);
        DeathSystem::system(r, playerEntity);
        DestoyersSystem::system(r, height, width);
        SoundLoopSystem::system(r, sounds, time);
        BombGenerationTimeSystem::system(r, time);
        BombGenerationSystem::system(r, time);
        game.Stages(r, time, playerEntity, sounds);
        BeginDrawing();
        ClearBackground(RAYWHITE);
<<<<<<< HEAD
        m.drawMenu();
=======
        drawSys.system(r, texture);
        DrawKmSystem::system(r);
        DrawLvlSystem::system(r);
        DrawPointsSystem::system(r);
<<<<<<< HEAD
>>>>>>> c351202 (feat(Engine): add the Text Components)
=======
        MessageSystem::system(r);
>>>>>>> 5f4ac64 (feat(Engine): add the Dead text)
        EndDrawing();
    }
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
