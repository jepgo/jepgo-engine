/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** main
*/

#include <iostream>
#include "InvinsibleSystem.hpp"
#include "LoopMoveSystem.hpp"
#include <SFML/Audio.hpp>
#include "DestroyerSystem.hpp"
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
void keySystem(Register &r, sf::Keyboard::Key key, bool keyUp, sf::Time &time)
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
            shoot[i].value().shoot(r, pos[i].value());
            shoot[i].value()._time =  time.asSeconds();
            return;
        }
        if (stat[i].has_value() and draw[i].has_value())
            control[i].value().moveStatus(stat[i], draw[i], key);
        if (keyUp)
            control[i].value().onKeyUp(key, vel[i].value());
        else
            control[i].value().onKeyDown(key, vel[i].value());
        r.emplace_comp(i, Move(vel[i].value().getVel()));
    }
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

std::vector<sf::Sound> getAllSound(std::vector<std::string> list)
{
    sf::Sound sound;
    std::vector<sf::Sound> res;
    sf::SoundBuffer buffer;

    for (std::size_t i = 0; i < list.size(); i++) {
        buffer.loadFromFile(list[i]);
        sound.setBuffer(buffer);
        res.push_back(sound);
    }
    return res;
}

int main()
{
    std::size_t height = 800;
    std::size_t width = 600;
    Register r;
    sf::Clock clock;
    sf::Time time;
    sf::Event event;
    std::vector<sf::Texture> texture = getAllTexture({ "sprites/r-typesheet3.gif", "sprites/r-typesheet1.gif", "sprites/r-typesheet2.gif", "sprites/parallax-space-backgound.png", "sprites/parallax-space-big-planet.png", "sprites/r-typesheet32.gif"});
    // std::vector<sf::Sound> sounds = getAllSound({"sprites/test.ogg"});
    sf::RenderWindow window(sf::VideoMode(height, width), "R-TYPE");
    Game player = Game();
    AddDmgSystem addDmgSystem = AddDmgSystem(1);
    TestGame game = TestGame(1);
    GameSystem SystemGame = GameSystem(0.1);
    MoveSystem moveSys = MoveSystem(10);
    HitSystem hitSys = HitSystem();
    DrawSystem drawSys = DrawSystem();
    AnimationSpriteSystem animSys = AnimationSpriteSystem();

    sf::Font font;
    font.loadFromFile(".font/arial.ttf");
    r.creatEntity();
    r.emplace_comp(r.entity_nbr, Drawable(3, std::nullopt, std::vector<float>{3, 4}));
    r.emplace_comp(r.entity_nbr, Positions(0, 0));
    r.creatEntity();
    r.emplace_comp(r.entity_nbr, Drawable(4, std::nullopt, std::vector<float>{3, 3}));
    r.emplace_comp(r.entity_nbr, Positions(800, 200));
    r.emplace_comp(r.entity_nbr, Move(Positions(-1, 0)));
    r.emplace_comp(r.entity_nbr, LoopMove(Positions(1800, 200)));
    Game::CreatPlayer(r, height, width);
    Game::CreateBoostModule(r);
    Game::CreatText(r, Positions(350, 0), "R-TYPE", font);
    //Game::CreateMiniBoss1(r, Positions(660, 200));
    //Game::Creat
    // sounds[0].setLoop(true);
    // sounds[0].setVolume(50.f);
    // sounds[0].play();
    while (window.isOpen()) {
        //std::cout << "life = " << r.getComp<Life>()[5].value()._life << std::endl;
        //std::cout << "lvl = " << player.getLvl() << " exp = " << player.getExp() << " km = " << player.getKm() << std::endl; 
        time = clock.getElapsedTime();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                keySystem(r, event.key.code, false, time);
            if (event.type == sf::Event::KeyReleased) {
                keySystem(r, event.key.code, true, time);
                MidSpriteSystem(r);
            }
        }
        window.clear(sf::Color::White);
        Text::system(r, window);
        hitSys.system(r);
        AttachModuleSystem::system(r);
        SystemGame.system(r, player, time);
        LoopMoveSystem::system(r, height, width);
        moveSys.system(r, time);
        animSys.system(r, time);
        InvinsibleSystem::system(r, time);
        addDmgSystem.system(r, time);
        ModuleSystem::system(r);
        DmgSystem::system(r);
        ExplosionSystem::system(r);
        DeathSystem::system(r, player);
        drawSys.system(window, r, texture);
        DestoyersSystem::system(r, height, width);
        game.generateRandomsEntitys(r, time, player);
        window.display();
    }
    return 0;
}