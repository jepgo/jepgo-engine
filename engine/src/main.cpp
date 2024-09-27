/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** main
*/

#include <iostream>
#include <SFML/Audio.hpp>
#include "AddDmgSystem.hpp"
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

int main()
{
    std::size_t height = 800;
    std::size_t width = 600;
    Register r;
    sf::Clock clock;
    sf::Time time;
    sf::Event event;
    std::vector<sf::Texture> texture = getAllTexture({ "sprites/r-typesheet3.gif", "sprites/r-typesheet1.gif", "sprites/r-typesheet2.gif", "sprites/parallax-space-backgound.png", "sprites/parallax-space-big-planet.png"});
    sf::RenderWindow window(sf::VideoMode(height, width), "R-TYPE");
    Game player = Game();
    AddDmgSystem addDmgSystem = AddDmgSystem(1);
    TestGame game = TestGame(1);
    MoveSystem moveSys = MoveSystem(10);
    HitSystem hitSys = HitSystem();
    DrawSystem drawSys = DrawSystem();
    AnimationSpriteSystem animSys = AnimationSpriteSystem();

    sf::Font font;
    font.loadFromFile(".font/arial.ttf");
    sf::SoundBuffer buffer;
    sf::Sound sound;
    buffer.loadFromFile("sprites/test.ogg");
    sound.setBuffer(buffer);
    r.creatEntity();
    r.emplace_comp(r.entity_nbr, Drawable(3, std::nullopt, std::vector<float>{3, 4}));
    r.emplace_comp(r.entity_nbr, Positions(0, 0));
    r.creatEntity();
    r.emplace_comp(r.entity_nbr, Drawable(4, std::nullopt, std::vector<float>{1, 1}));
    r.emplace_comp(r.entity_nbr, Positions(800, 200));
    r.emplace_comp(r.entity_nbr, Move(Positions(-1, 0)));
    Game::CreatPlayer(r, height, width);
    Game::CreateArmorModule(r, Positions(1000, 300));
    Game::CreateBoostModule(r);
    Game::CreateShootModule(r, Positions(200, 200));
    Game::CreatText(r, Positions(350, 0), "R-TYPE", font);
    sound.setLoop(true);
    sound.setVolume(50.f);
    sound.play();
    while (window.isOpen()) {
        //std::cout << "lvl = " << player.getLvl() << " exp = " << player.getExp() << " point = " << player.getPoint() << std::endl; 
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
        moveSys.system(r, time);
        animSys.system(r, time);
        addDmgSystem.system(r, time);
        ModuleSystem::system(r);
        DmgSystem::system(r);
        ExplosionSystem::system(r);
        DeathSystem::system(r, player);
        drawSys.system(window, r, texture);
        game.generateRandomsEntitys(r, time);
        window.display();
    }
    return 0;
}