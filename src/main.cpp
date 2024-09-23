/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** main
*/

#include "HitSystem.hpp"
#include "DrawSystem.hpp"
#include <iostream>
#include "Register.hpp"
#include "Components.hpp"
#include <SFML/Graphics.hpp>
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
void keySystem(Register &r, sf::Keyboard::Key key, bool keyUp)
{
    auto &control = r.getComp<Controllable>();
    auto &vel = r.getComp<Velocity>();
    auto &pos = r.getComp<Positions>();
    auto &stat = r.getComp<Sprite_Status>();
    auto &draw = r.getComp<Drawable>();

    for (std::size_t i = 0; i < control.size(); i++) {
        if (!control[i].has_value() or !vel[i].has_value() or !pos[i].has_value())
            continue;
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
    Register r;
    sf::Clock clock;
    sf::Time time;
    sf::Event event;
    std::vector<sf::Texture> texture = getAllTexture({ "sprites/r-typesheet3.gif", "sprites/r-typesheet1.gif" });
    sf::RenderWindow window(sf::VideoMode(800, 600), "R-TYPE");
    // Drawable test("sprites/r-typesheet3.gif", "caca");
    // Positions ok(100, 100);
    MoveSystem moveSys = MoveSystem(10);
    HitSystem hitSys = HitSystem();
    DrawSystem drawSys = DrawSystem();
    AnimationSpriteSystem animSys = AnimationSpriteSystem();

    r.creatEntity();
    r.emplace_comp(0, Positions(100, 100));
    r.emplace_comp(0, Drawable(1, sf::IntRect(202, 0, 30, 18), std::vector<float>{1.5, 1.5}));
    //   r.emplace_comp(0, Sprite_Animation(10, 17, 0.05));
    r.emplace_comp(0, Velocity({2, 2, 2, 2}));
    r.emplace_comp(0, Colision(30, 18));
    r.emplace_comp(0, Controllable());
    r.emplace_comp(0, Sprite_Status({{UP, 235}, {DOWN, 100}, {MID, 202}, {LEFT, 202}, {RIGHT, 202}}));
    r.emplace_comp(0, Hitable(30, 18));
    r.creatEntity();
    r.emplace_comp(1, Positions(250, 250));
    r.emplace_comp(1, Drawable(0, sf::IntRect(0, 0, 17, 18), std::vector<float>{1.5, 1.5}));
    r.emplace_comp(1, Sprite_Animation(10, 17, 0.05));
    //r.emplace_comp(1, Hitable(17, 18));
    //r.emplace_comp(1, Explosion(1, 4, -37, 0.2, sf::IntRect(180, 300, 40, 40), std::vector<float>{1.5, 1.5}));
    r.emplace_comp(1, Colision(17, 18));
     r.creatEntity();
    r.emplace_comp(2, Positions(400, 350));
    r.emplace_comp(2, Drawable(0, sf::IntRect(0, 0, 17, 18), std::vector<float>{1.5, 1.5}));
    r.emplace_comp(2, Sprite_Animation(10, 17, 0.05));
    r.emplace_comp(2, Hitable(17, 18));
    r.emplace_comp(2, Explosion(1, 4, -37, 0.2, sf::IntRect(180, 300, 40, 40), std::vector<float>{1.5, 1.5}));
    //r.removeComponent<Drawable>(1);
    // r.creatEntity();
    // r.emplace_comp(1, Positions(300, 300));
    // r.emplace_comp(1, Drawable(0, sf::IntRect(0, 0, 17, 18)));
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                keySystem(r, event.key.code, false);
            if (event.type == sf::Event::KeyReleased) {
                keySystem(r, event.key.code, true);
                MidSpriteSystem(r);
            }
        }
        window.clear(sf::Color::White);
        time = clock.getElapsedTime();
        hitSys.system(r, texture);
        moveSys.system(r, time);
        animSys.system(r, time);
        drawSys.system(window, r, texture);
        window.display();
    }
    return 0;
}