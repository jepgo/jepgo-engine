/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** main
*/

#include "Raylib.hpp"
#include <iostream>
#include "DrawKmSystem.hpp"
#include "DrawLvlSystem.hpp"
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
int keySystem(Register &r, float time, std::vector<Sound> &sounds)
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
        auto key = GetKeyPressed();
        if (key == KeyboardKey::KEY_A && shoot[i].has_value() && shoot[i].value().verif(time)) {
            PlaySound(sounds[shoot[i].value()._ind]);
            shoot[i].value().shoot(r, pos[i].value());
            shoot[i].value()._time =  time;
            return 2;
        }
        if (stat[i].has_value() and draw[i].has_value())
            control[i].value().moveStatus(stat[i], draw[i], key);
        vel[i].value().setVel(getDirectionVector());
        // if (keyUp)
        //     control[i].value().onKeyUp(key, vel[i].value());
        // else
        //     control[i].value().onKeyDown(key, vel[i].value());
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

int main()
{
    int playerEntity = 0;
    std::size_t height = 800;
    std::size_t width = 600;
    InitWindow(height, width, "R-TYPE");
    InitAudioDevice();
    Register r;
    Game::CreateBackGround(r);
    Game::CreatePlanet(r);
    Game::CreatPlayer(r, height, width);
    playerEntity = r.entity_nbr;
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
    //Sound sound = LoadSound("sprites/level1.ogg");
    r.creatEntity();
    r.emplace_comp(r.entity_nbr, SoundLoop(1));
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
        drawSys.system(r, texture);
        DrawKmSystem::system(r);
        DrawLvlSystem::system(r);
        DrawPointsSystem::system(r);
        EndDrawing();
    }
    CloseAudioDevice();
    CloseWindow();
    return 0;
}

// int main()
// {
//     std::size_t height = 800;
//     std::size_t width = 600;
//     Register r;
//     int playerEntity = 2;
//     sf::Clock clock;
//     sf::Time time;
//     sf::Event event;
//     std::vector<sf::Texture> texture = getAllTexture({ "sprites/r-typesheet3.gif", "sprites/r-typesheet1.gif", "sprites/r-typesheet2.gif", "sprites/parallax-space-backgound.png", "sprites/parallax-space-big-planet.png", "sprites/r-typesheet32.gif", "sprites/r-typesheet14.gif"});
//     std::vector<sf::SoundBuffer> sounds = getAllSound({"sprites/test.ogg", "sprites/level1.ogg", "sprites/laser.wav"});
//     sf::RenderWindow window(sf::VideoMode(height, width), "R-TYPE");
//     sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

//     window.setPosition(sf::Vector2i((desktopMode.width / 4), (desktopMode.height / 4)));
//     Game player = Game();
//     AddDmgSystem addDmgSystem = AddDmgSystem(0.1);
//     TestGame game = TestGame(1);
//     GameSystem SystemGame = GameSystem(0.1);
//     MoveSystem moveSys = MoveSystem(10);
//     HitSystem hitSys = HitSystem();
//     DrawSystem drawSys = DrawSystem();
//     MoveToPlayerSystem movetoplayer = MoveToPlayerSystem(0.3);
//     AnimationSpriteSystem animSys = AnimationSpriteSystem();

//     sf::Font font;
//     font.loadFromFile(".font/arial.ttf");
//     Game::CreateBackGround(r);
//     Game::CreatePlanet(r);
//     Game::CreatPlayer(r, height, width);
//     playerEntity = r.entity_nbr;
//     //Game::CreatText(r, Positions(350, 0), "R-TYPE", font);
//     sf::Sound test;
//     r.creatEntity();
//     r.emplace_comp(r.entity_nbr, SoundLoop(1, 10)); 
//     test.setBuffer(sounds[2]);
//     test.setVolume(50);
//     sf::Sound sound;
//     //sound.setBuffer(sounds[1]);
//     //sound.setLoop(true);
//     //sound.play();
//     while (window.isOpen()) {
//         //std::cout << "life = " << r.getComp<Life>()[5].value()._life << std::endl;
//         //std::cout << "lvl = " << player.getLvl() << " exp = " << player.getExp() << " km = " << player.getKm() << std::endl;
//         //std::cout << "drawable is = " << r.getComp<Drawable>()[4].value().getRect().value().left << std::endl; 
//         time = clock.getElapsedTime();
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//             if (event.type == sf::Event::KeyPressed)
//                 keySystem(r, event.key.code, false, time, test);
//             if (event.type == sf::Event::KeyReleased) {
//                 keySystem(r, event.key.code, true, time, test);
//                 MidSpriteSystem(r);
//             }
//         }
//         window.clear(sf::Color::White);
//         // Text::system(r, window);
//         // hitSys.system(r);
//         // AttachModuleSystem::system(r);
//         // SystemGame.system(r, time, playerEntity, sound);
//         // LoopMoveSystem::system(r, height, width);
//         // MoveToPlayerTimeSystem::system(r, time);
//         // movetoplayer.system(r, time);
//         // moveSys.system(r, time);
//         // Animation2TimeSystem::system(r, time);
//         // animSys.system(r, time);
//         // ShortAnimationSystem::system(r, time);
//         // InvinsibleSystem::system(r, time);
//         // addDmgSystem.system(r, time);

//         // ModuleSystem::system(r);
//         // DmgSystem::system(r, time);
//         //ExplosionSystem::system(r);
//         // DeathSystem::system(r, playerEntity);
//         drawSys.system(window, r, texture);
//         // DestoyersSystem::system(r, height, width);
//         SoundLoopSystem::system(r, sounds, time);
//         //BombGenerationTimeSystem::system(r, time);
//         //BombGenerationSystem::system(r, time);
//         //game.Stages(r, time, playerEntity, sound, sounds);
//         window.display();
//     }
//     return 0;
// }