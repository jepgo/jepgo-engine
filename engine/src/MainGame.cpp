/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** main
*/

#include "MainGame.hpp"
#include "Raylib.hpp"
#include "Draw3DSystem.hpp"
#include <iostream>
#include "DrawKmSystem.hpp"
#include "DrawLvlSystem.hpp"
#include "DetachModulesSystem.hpp"
#include "MessageTimeSystem.hpp"
#include "MessageSystem.hpp"
#include "MoveToSystem.hpp"
#include "AutoShootSystem.hpp"
#include "DrawRebornSystem.hpp"
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
#include "RebornSystem.hpp"
#include "HitSystem.hpp"
#include "DrawSystem.hpp"
#include "Register.hpp"
#include "Components.hpp"
#include "ExplosionSystem.hpp"
#include "SparseArray.hpp"
#include "MoveSystem.hpp"
#include "AnimationSpriteSystem.hpp"

/**
 * @brief Get the All Texture object
 * 
 * @param list List of all the file of the textures
 * @return std::vector<sf::Texture> 
 */
// std::vector<sf::Texture> getAllTexture(std::vector<std::string> list)
// {
//     sf::Texture tmp;
//     std::vector<sf::Texture> texture;

//     for (std::size_t i = 0; i < list.size(); i++)
//     {
//         tmp.loadFromFile(list[i].c_str());
//         texture.push_back(tmp);
//     }
//     return texture;
// }

/**
 * Get the direction vector (x, y)
 */
static Vector2 getDirectionVector(void)
{
    Vector2 vec(
        IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT),
        IsKeyDown(KEY_DOWN) - IsKeyDown(KEY_UP)
    );

    return vec;
}

/**
 * @brief The Controllable system
 * 
 * @param r The Registry
 * @param key The keyboard key who's pressed
 */
int keySystem(Register &r, float time, std::vector<Sound> &sounds, int key)
{
    auto &control = r.getComp<Controllable>();
    auto &vel = r.getComp<Velocity>();
    auto &pos = r.getComp<Positions>();
    auto &stat = r.getComp<Sprite_Status>();
    auto &draw = r.getComp<Drawable>();
    auto &shoot = r.getComp<Shoot>();

    for (std::size_t i = 0; i < control.size(); i++) {
        if (!control[i].has_value() or !vel[i].has_value() or !pos[i].has_value())
            continue;
        if (key == KeyboardKey::KEY_A && shoot[i].has_value() && shoot[i].value().verif(time)) {
            SetSoundVolume(sounds[shoot[i].value()._ind], 0.1);
            PlaySound(sounds[shoot[i].value()._ind]);
            shoot[i].value().shoot(r, pos[i].value());
            shoot[i].value()._time =  time;
            return 2;
        }
        if (stat[i].has_value() and draw[i].has_value())
            control[i].value().moveStatus(stat[i], draw[i], key);
        vel[i].value().setVel(getDirectionVector());
        r.emplace_comp(i, Move(vel[i].value().getVel()));
    }
    return -1;
}

/**
 * @brief The Sprite Status System
 * 
 * @param r The Regsitry
 */
void MidSpriteSystem(Register &r)
{
    auto &control = r.getComp<Controllable>();
    auto &stat = r.getComp<Sprite_Status>();
    auto &draw = r.getComp<Drawable>();

    for (std::size_t i = 0; i < stat.size(); i++) {
        if (control[i].has_value() && stat[i].has_value() && draw[i].has_value() && draw[i].value().getRect().has_value()) {
            draw[i].value().getRect().value().width = stat[i].value().mid();
        }
    }
}

std::vector<Sound> getAllSound(const std::vector<std::string>& list)
{
    std::vector<Sound> res;

    for (const auto& filename : list) {
        Sound buffer = LoadSound(filename.c_str());
        res.push_back(std::move(buffer));
    }
    return res;
}

std::vector<Texture2D> getAllTexture(std::vector<std::string> list)
{
    std::vector<Texture2D> texture;
    texture.reserve(list.size());

    for (std::size_t i = 0; i < list.size(); i++)
    {
        Texture2D tmp = LoadTexture(list[i].c_str());
        //tmp.loadFromFile(list[i].c_str());
        texture.push_back(std::move(tmp));
    }
    return texture;
}

void deletAll(std::vector<Sound> sounds, std::vector<Texture2D> texture)
{
    // for (auto &s : sounds) {
    //     UnloadSound(s);
    // }

    // for (auto &t : texture) {
    //     UnloadTexture(t);
    // }
}

void MainGame::mainGame()
{
    int key;
    int playerEntity = 0;
    std::size_t height = 800;
    std::size_t width = 600;
    //InitWindow(height, width, "R-TYPE");
    
    Register r;
    Game::CreateBackGround(r);
    Game::CreatePlanet(r);
    Game::CreatPlayer(r, height, width);
    playerEntity = r.currentEntity;
    Game::CreateMessageTime(r, Positions(300, 100), "Farm as you can !", 0, 5);
    //Game::CreateArmorModule(r, Positions(300, 300));
    float startTime = GetTime();
    Game player = Game();
    AddDmgSystem addDmgSystem = AddDmgSystem(0.1);
    TestGame game = TestGame(1);
    MoveToSystem SystemMoveTo = MoveToSystem(0, 0.1);
    GameSystem SystemGame = GameSystem(0.1);
    MoveSystem moveSys = MoveSystem(0.01);
    HitSystem hitSys = HitSystem();
    DrawSystem drawSys = DrawSystem();
    Draw3DSystem draw3D = Draw3DSystem(0, 0.1);
    Model mod = LoadModel("models/model/ship.obj");
    Texture2D tex = LoadTexture("models/texture/texture_ship.png");
    mod.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = tex;
    MoveToPlayerSystem movetoplayer = MoveToPlayerSystem(0.3);
    AnimationSpriteSystem animSys = AnimationSpriteSystem();
    std::vector<Sound> sounds = getAllSound({"sprites/test.ogg", "sprites/level1.ogg", "sprites/laser.wav", "sprites/explose.wav"});
    std::vector<Texture2D> texture = getAllTexture({ "sprites/r-typesheet3.gif", "sprites/r-typesheet1.gif", "sprites/r-typesheet2.gif", "sprites/parallax-space-backgound.png", "sprites/parallax-space-big-planet.png", "sprites/r-typesheet32.gif", "sprites/r-typesheet14.gif"});

    r.creatEntity();
    r.emplace_comp(r.currentEntity, SoundLoop(1));
    while (!WindowShouldClose()) {
        key = GetKeyPressed();
        if (key == KeyboardKey::KEY_P) {
            return;
        }
        float time = GetTime() - startTime;
        keySystem(r, time, sounds, key);
        hitSys.system(r);
        DetachModulesSystem::system(r, time, key);
        AttachModuleSystem::system(r);
        SystemGame.system(r, time, playerEntity);
        LoopMoveSystem::system(r, height, width);
        MoveToPlayerTimeSystem::system(r, time);
        AutoShootSystem::system(r, time);
        SystemMoveTo.system(r, time);
        movetoplayer.system(r, time);
        moveSys.system(r, time);
        Animation2TimeSystem::system(r, time);
        animSys.system(r, time);
        ShortAnimationSystem::system(r, time);
        InvinsibleSystem::system(r, time);
        addDmgSystem.system(r, time);
        ModuleSystem::system(r);
        DmgSystem::system(r, time);
        ExplosionSystem::system(r, sounds, 3);
        DeathSystem::system(r, playerEntity);
        RebornSystem::system(r, playerEntity, time, key);
        DestoyersSystem::system(r, height, width);
        SoundLoopSystem::system(r, sounds, time);
        BombGenerationTimeSystem::system(r, time);
        BombGenerationSystem::system(r, time);
        game.Stages(r, time, playerEntity, sounds);
        MessageTimeSystem::system(r, time);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        drawSys.system(r, texture);
        BeginMode3D(camera);
        draw3D.system(r, time, mod);
        EndMode3D();
        DrawKmSystem::system(r);
        DrawLvlSystem::system(r);
        DrawPointsSystem::system(r);
        DrawRebornSystem::system(r);
        MessageSystem::system(r);
        EndDrawing();
    }
}
