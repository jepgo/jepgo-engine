/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** main
*/

#include <iostream>
#include "MoveToPlayerSystem.hpp"
#include "Animation2TimeSystem.hpp"
#include "InvinsibleSystem.hpp"
#include "LoopMoveSystem.hpp"
#include "DestroyerSystem.hpp"
#include "ShortAnimationSystem.hpp"
#include "SoundLoopSystem.hpp"
#include "AddDmgSystem.hpp"
#include "GameSystem.hpp"
#include <SFML/Graphics.hpp>
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
std::vector<sf::Texture> getAllTexture(std::vector<std::string> list)
{
    sf::Texture tmp;
    std::vector<sf::Texture> texture;

    for (std::size_t i = 0; i < list.size(); i++)
    {
        tmp.loadFromFile(list[i].c_str());
        texture.push_back(tmp);
    }
    return texture;
}

/**
 * @brief The Controllable system
 * 
 * @param r The Registry
 * @param key The keyboard key who's pressed
 */
int keySystem(Register &r, sf::Keyboard::Key key, bool keyUp, sf::Time &time, sf::Sound &sound)
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
        if (key == sf::Keyboard::A && shoot[i].has_value() && shoot[i].value().verif(time)) {
            //sound.play();
            //std::cout << "fire" << std::endl;
            shoot[i].value().shoot(r, pos[i].value());
            shoot[i].value()._time =  time.asSeconds();
            return 2;
        }
        if (stat[i].has_value() and draw[i].has_value())
            control[i].value().moveStatus(stat[i], draw[i], key);
        if (keyUp)
            control[i].value().onKeyUp(key, vel[i].value());
        else
            control[i].value().onKeyDown(key, vel[i].value());
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
            draw[i].value().getRect().value().left = stat[i].value().mid();
        }
    }
}

std::vector<sf::SoundBuffer> getAllSound(const std::vector<std::string>& list)
{
    std::vector<sf::SoundBuffer> res;

    for (const auto& filename : list) {
        sf::SoundBuffer buffer;
        buffer.loadFromFile(filename);
        res.push_back(std::move(buffer));
    }
    return res;
}

int main()
{
    std::size_t height = 800;
    std::size_t width = 600;
    Register r;
    int playerEntity = 2;
    sf::Clock clock;
    sf::Time time;
    sf::Event event;
    std::vector<sf::Texture> texture = getAllTexture({ "sprites/r-typesheet3.gif", "sprites/r-typesheet1.gif", "sprites/r-typesheet2.gif", "sprites/parallax-space-backgound.png", "sprites/parallax-space-big-planet.png", "sprites/r-typesheet32.gif"});
    std::vector<sf::SoundBuffer> sounds = getAllSound({"sprites/test.ogg", "sprites/level1.ogg", "sprites/laser.wav"});
    sf::RenderWindow window(sf::VideoMode(height, width), "R-TYPE");
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

    window.setPosition(sf::Vector2i((desktopMode.width / 4), (desktopMode.height / 4)));
    Game player = Game();
    AddDmgSystem addDmgSystem = AddDmgSystem(0.1);
    TestGame game = TestGame(1);
    GameSystem SystemGame = GameSystem(0.1);
    MoveSystem moveSys = MoveSystem(10);
    HitSystem hitSys = HitSystem();
    DrawSystem drawSys = DrawSystem();
    MoveToPlayerSystem movetoplayer = MoveToPlayerSystem(0.3);
    AnimationSpriteSystem animSys = AnimationSpriteSystem();

    sf::Font font;
    font.loadFromFile(".font/arial.ttf");
    Game::CreateBackGround(r);
    Game::CreatePlanet(r);
    Game::CreatPlayer(r, height, width);
    playerEntity = r.entity_nbr;
    Game::CreateBoostModule(r, playerEntity);
    //Game::CreateMiniBoss1(r, Positions(660, 200));
    //Game::CreatText(r, Positions(350, 0), "R-TYPE", font);
    sf::Sound test;
    test.setBuffer(sounds[2]);
    test.setVolume(50);
    sf::Sound sound;
    sound.setBuffer(sounds[1]);
    sound.setLoop(true);
    sound.play();
    while (window.isOpen()) {
        //std::cout << "life = " << r.getComp<Life>()[5].value()._life << std::endl;
        //std::cout << "lvl = " << player.getLvl() << " exp = " << player.getExp() << " km = " << player.getKm() << std::endl;
        //std::cout << "drawable is = " << r.getComp<Drawable>()[4].value().getRect().value().left << std::endl; 
        time = clock.getElapsedTime();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                keySystem(r, event.key.code, false, time, test);
            if (event.type == sf::Event::KeyReleased) {
                keySystem(r, event.key.code, true, time, test);
                MidSpriteSystem(r);
            }
        }
        window.clear(sf::Color::White);
        Text::system(r, window);
        hitSys.system(r);
        AttachModuleSystem::system(r);
        SystemGame.system(r, time, playerEntity, sound);
        LoopMoveSystem::system(r, height, width);
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
        drawSys.system(window, r, texture);
        DestoyersSystem::system(r, height, width);
        //SoundLoopSystem::system(r, sounds, time);
        game.Stages(r, time, playerEntity, sound, sounds);
        window.display();
    }
    return 0;
}