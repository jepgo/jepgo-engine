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

std::vector<Model> getAllModel(const std::map<std::string, std::string> models)
{
    std::vector<Model> res;

    for (auto &mod : models) {
        Model tmp = LoadModel(mod.first.c_str());
        Texture2D tex = LoadTexture(mod.second.c_str());
        tmp.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = tex;
        res.push_back(std::move(tmp));
    }
    return res;
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
    playerEntity = r.entity_nbr;
    Game::CreateBoostModule(r, playerEntity);
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
    MoveToPlayerSystem movetoplayer = MoveToPlayerSystem(0.3);
    AnimationSpriteSystem animSys = AnimationSpriteSystem();
    std::vector<Sound> sounds = getAllSound({"sprites/test.ogg", "sprites/level1.ogg", "sprites/laser.wav", "sprites/explose.wav"});
    std::vector<Texture2D> texture = getAllTexture({ "sprites/r-typesheet3.gif", "sprites/r-typesheet1.gif", "sprites/r-typesheet2.gif", "sprites/parallax-space-backgound.png", "sprites/parallax-space-big-planet.png", "sprites/r-typesheet32.gif", "sprites/r-typesheet14.gif"});
    std::vector<Model> models = getAllModel({{"models/model/ship.obj", "models/texture/texture_ship.png"}});

    r.creatEntity();
    r.emplace_comp(r.entity_nbr, SoundLoop(1));

    Camera camera = { 0 };
    camera.position = (Vector3){ height / 2.0f, width / 2.0f, 500.0f };
    camera.target = (Vector3){ height / 2.0f, width / 2.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = width;
    camera.projection = CAMERA_ORTHOGRAPHIC;
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        key = GetKeyPressed();
        if (key == KeyboardKey::KEY_P) {
            return;
        }
        float time = GetTime() - startTime;
        keySystem(r, time, sounds, key);
        hitSys.system(r);
        std::cout << "after hit" << std::endl;
        DetachModulesSystem::system(r, time, key);
        std::cout << "after detattach" << std::endl;
        AttachModuleSystem::system(r);
        std::cout << "after attach" << std::endl;
        SystemGame.system(r, time, playerEntity);
        std::cout << "after systemGame" << std::endl;
        LoopMoveSystem::system(r, height, width);
        std::cout << "after loop" << std::endl;
        MoveToPlayerTimeSystem::system(r, time);
        std::cout << "after MoveTOPLAYERTime" << std::endl;
        AutoShootSystem::system(r, time);
        std::cout << "after autoshoot" << std::endl;
        SystemMoveTo.system(r, time);
        std::cout << "after systemMoveTo" << std::endl;
        movetoplayer.system(r, time);
        std::cout << "after movetoplayer" << std::endl;
        moveSys.system(r, time);
        std::cout << "after movesys" << std::endl;
        Animation2TimeSystem::system(r, time);
        std::cout << "after animation2time" << std::endl;
        animSys.system(r, time);
        std::cout << "after anim" << std::endl;
        ShortAnimationSystem::system(r, time);
        std::cout << "after shortAnim" << std::endl;
        InvinsibleSystem::system(r, time);
        std::cout << "after invinsible" << std::endl;
        addDmgSystem.system(r, time);
        std::cout << "after addDmg" << std::endl;
        ModuleSystem::system(r);
        std::cout << "after Module" << std::endl;
        DmgSystem::system(r, time);
        std::cout << "after dmg" << std::endl;
        ExplosionSystem::system(r, sounds, 3);
        std::cout << "after sound" << std::endl;
        DeathSystem::system(r, playerEntity);
        std::cout << "after death" << std::endl;
        RebornSystem::system(r, playerEntity, time, key);
        std::cout << "after reborn" << std::endl;
        DestoyersSystem::system(r, height, width);
        std::cout << "after destroyer" << std::endl;
        SoundLoopSystem::system(r, sounds, time);
        std::cout << "after soundloop" << std::endl;
        BombGenerationTimeSystem::system(r, time);
        std::cout << "after bombgeneratortime" << std::endl;
        BombGenerationSystem::system(r, time);
        std::cout << "after bombgenertor" << std::endl;
        game.Stages(r, time, playerEntity, sounds);
        std::cout << "after stage" << std::endl;
        MessageTimeSystem::system(r, time);
        std::cout << "after messageTime" << std::endl;
        BeginDrawing();
        ClearBackground(RAYWHITE);
        drawSys.system(r, texture);
        BeginMode3D(camera);
        draw3D.system(r, time, models);
        EndMode3D();
        DrawKmSystem::system(r);
        DrawLvlSystem::system(r);
        DrawPointsSystem::system(r);
        DrawRebornSystem::system(r);
        MessageSystem::system(r);
        EndDrawing();
    }
}
