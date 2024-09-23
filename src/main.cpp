/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** main
*/

#include <iostream>
#include "Register.hpp"
#include "Components.hpp"
#include <SFML/Graphics.hpp>
#include "SparseArray.hpp"

/**
 * @brief The drawable System
 * 
 * @param window The window of the screen
 * @param r The Registry
 * @param texture The list of texture for all the sprite
 */
void display_drawable(sf::RenderWindow &window, Register &r, std::vector<sf::Texture> &texture)
{
    auto &pos = r.getComp<Positions>();
    auto &draw = r.getComp<Drawable>();

    for (std::size_t i = 0; i < draw.size(); i++)
    {
        if (draw[i].has_value() && pos[i].has_value())
        {
            draw[i].value().draw(window, texture[draw[i].value().getIndex()], pos[i].value());
        }
    }
}

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
 * @brief Function who check the Sprite Animations
 * 
 * @param r The Registry
 * @param time The current time
 */
void checkSprite(Register &r, sf::Time &time)
{
    //sf::Time time = clock.getElapsedTime();
    auto &rec = r.getComp<Sprite_Animation>();
    auto &draw = r.getComp<Drawable>();

    for (std::size_t i = 0; i < rec.size(); i++) {
        if (rec[i].has_value() && draw[i].has_value() && time.asSeconds() - rec[i].value().t >= rec[i].value().reset)
        {
            draw[i].value().getRect().value().left += rec[i].value().val;
            if ((rec[i].value().isneg == false) && draw[i].value().getRect().value().left >= (rec[i].value().status) * rec[i].value().val) {
                if (rec[i].value().deadAnimation == true) {
                    r.removeComponent<Drawable>(i);
                    r.removeComponent<Sprite_Animation>(i);
                } else
                    draw[i].value().getRect().value().left = draw[i].value().start;
            }
            else if ((rec[i].value().isneg == true) && draw[i].value().getRect().value().left <= (rec[i].value().status) * rec[i].value().val) {
                if (rec[i].value().deadAnimation == true) {
                    r.removeComponent<Drawable>(i);
                    r.removeComponent<Sprite_Animation>(i);
                } else
                draw[i].value().getRect().value().left = draw[i].value().start;
            }
            if (rec[i].has_value()) {
                rec[i].value().t = time.asSeconds();
            }
        }
    }
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
    // auto &col = r.getComp<Colision>();

    for (std::size_t i = 0; i < control.size(); i++) {
        if (!control[i].has_value() or !vel[i].has_value() or !pos[i].has_value())
            continue;
        if (stat[i].has_value() and draw[i].has_value())
            control[i].value().moveStatus(stat[i], draw[i], key);
        if (keyUp)
            control[i].value().onKeyUp(key, vel[i].value(), pos[i].value());
        else
            control[i].value().onKeyDown(key, vel[i].value(), pos[i].value());
        r.emplace_comp(i, Move(vel[i].value().getVel()));
    }
}

/**
 * @brief The Hitable Compare
 * 
 * @param list List of Hitable
 * @param me The current who's hit
 * @param where The second who's hit
 * @param m My Position
 * @param him The Position of the other who are hit
 * @return true 
 * @return false 
 */
static bool compareHitable(std::map<std::size_t, Hitable*> &list, std::map<size_t, Hitable*>::iterator &me, std::map<size_t, Hitable*>::iterator &where, Positions &m, Positions &him, std::vector<sf::Texture> &texture, Register &re)
{
    for (auto &it = where; it != list.end(); it++) {
        if (me->second->isHit(*(it->second), him, m)) {
            me->second->Whenhit(me->first, re, texture);
            it->second->Whenhit(it->first, re, texture);
        }
    }
    return true;
}

/**
 * @brief The Hitable System
 * 
 * @param r The Registry
 */
void HitSystem(Register &r, std::vector<sf::Texture> &texture)
{
    auto &hit = r.getComp<Hitable>();
    auto &pos = r.getComp<Positions>();
    std::map<std::size_t, Hitable *> list;

    for (std::size_t i = 0; i < hit.size(); i++) {
        if (hit[i].has_value() && pos[i].has_value())
            list.insert(std::make_pair(i, &hit[i].value()));
    }
    if (list.size() == 0)
        return;
    for (auto it = list.begin(); std::next(it) != list.end(); it++) {
        auto next = std::next(it);
        if (compareHitable(list, it, next, pos[it->first].value(), pos[next->first].value(), texture, r)) {
            it->second->Whenhit(it->first, r, texture);
        }    
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

bool checkMovement(Register &r, std::size_t &entity, Positions const &Newpos)
{
    auto &Col = r.getComp<Colision>();
    auto &pos = r.getComp<Positions>();
    
    std::map<std::size_t, Colision *> list;

    for (std::size_t i = 0; i < Col.size(); i++) {
        if (Col[i].has_value() && i != entity)
            list.insert(std::make_pair(i, &Col[i].value()));
    }
    if (list.size() == 0)
        return true;
    for (auto it = list.begin(); std::next(it) != list.end(); it++) {
        if (Col[entity].value().isCol(*(it->second), pos[it->first].value(), Newpos) == false)
            return false;
    }
    return true;
}

void MoveSystem(Register &r)
{
    auto &move = r.getComp<Move>();

    for (std::size_t i = 0; i < move.size(); i++) {
        if (move[i].has_value() && checkMovement(r, i, move[i].value().getPos()))
            r.emplace_comp(i, std::move(Positions(move[i].value().getPos())));
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

    r.creatEntity();
    r.emplace_comp(0, Positions(100, 100));
    r.emplace_comp(0, Drawable(1, sf::IntRect(202, 0, 30, 18), std::vector<float>{1.5, 1.5}));
    //   r.emplace_comp(0, Sprite_Animation(10, 17, 0.05));
    r.emplace_comp(0, Velocity({5, 5, 5, 5}));
    r.emplace_comp(0, Controllable());
    r.emplace_comp(0, Sprite_Status({{UP, 235}, {DOWN, 100}, {MID, 202}, {LEFT, 202}, {RIGHT, 202}}));
    r.emplace_comp(0, Hitable(30, 18));
    r.creatEntity();
    r.emplace_comp(1, Positions(250, 250));
    r.emplace_comp(1, Drawable(0, sf::IntRect(0, 0, 17, 18), std::vector<float>{1.5, 1.5}));
    r.emplace_comp(1, Sprite_Animation(10, 17, 0.05));
    r.emplace_comp(1, Hitable(17, 18));
    r.emplace_comp(1, Explosion(1, 4, -37, 0.2, sf::IntRect(180, 300, 40, 40), std::vector<float>{1.5, 1.5}));
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
        HitSystem(r, texture);
        MoveSystem(r);
        checkSprite(r, time);
        display_drawable(window, r, texture);
        window.display();
    }
    return 0;
}