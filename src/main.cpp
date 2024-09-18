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

void display_drawable(sf::RenderWindow &window, Register &r, std::vector<sf::Texture> &texture)
{

    // SparseArray<Positions> &pos = std::any_cast<SparseArray<Positions> &>(map[std::type_index(typeid(Positions))]);
    // SparseArray<Drawable> &draw = std::any_cast<SparseArray<Drawable> &>(map[std::type_index(typeid(Drawable))]);
    auto &pos = r.getComp<Positions>();
    auto &draw = r.getComp<Drawable>();

    sf::RectangleShape rect(sf::Vector2f(0, 0));
    rect.setSize(sf::Vector2f(10, 10));
    rect.setFillColor(sf::Color(sf::Color::Black));
    // Positions a(200, 200);
    // Drawable test("sprites/r-typesheet3.gif", "test");

    for (std::size_t i = 0; i < draw.size(); i++)
    {
        if (draw[i].has_value() && pos[i].has_value())
        {
            draw[i].value().draw(window, texture[draw[i].value().getIndex()], pos[i].value());
        }
    }
}

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

void checkSprite(Register &r, sf::Time &time)
{
    //sf::Time time = clock.getElapsedTime();
    auto &rec = r.getComp<Sprite_Status>();
    auto &draw = r.getComp<Drawable>();

    for (std::size_t i = 0; i < rec.size(); i++)
    {
        if (rec[i].has_value() && draw[i].has_value() && time.asSeconds() - rec[i].value().t >= rec[i].value().reset)
        {
            draw[i].value().getRect().value().left += rec[i].value().val;
            if (draw[i].value().getRect().value().left >= (rec[i].value().status) * rec[i].value().val)
                draw[i].value().getRect().value().left = 0;
            rec[i].value().setTime(time);
        }
    }
}

void keySystem(Register &r, sf::Keyboard::Key key)
{
    auto &control = r.getComp<Controllable>();
    auto &vel = r.getComp<Velocity>();
    auto &pos = r.getComp<Positions>();

    for (std::size_t i = 0; i < control.size(); i++) {
        if (control[i].has_value() && vel[i].has_value() && pos[i].has_value()) {
            control[i].value().move(key, vel[i].value(), pos[i].value());
        }
    }
}

int main()
{
    Register r;
    sf::Clock clock;
    sf::Time time;
    sf::Event event;
    std::vector<std::string> data = {"sprites/r-typesheet3.gif"};
    std::vector<sf::Texture> texture = getAllTexture(data);
    sf::RenderWindow window(sf::VideoMode(800, 600), "R-TYPE");
    // Drawable test("sprites/r-typesheet3.gif", "caca");
    // Positions ok(100, 100);

    r.creatEntity();
    r.emplace_comp(0, Positions(100, 100));
    r.emplace_comp(0, Drawable(0, sf::IntRect(0, 0, 17, 18)));
    r.emplace_comp(0, Sprite_Status(10, 17, 0.5));
    r.emplace_comp(0, Velocity({2, 2, 5, 2}));
    r.emplace_comp(0, Controllable());
    r.creatEntity();
    r.emplace_comp(1, Positions(300, 300));
    r.emplace_comp(1, Drawable(0, sf::IntRect(0, 0, 17, 18)));
    r.emplace_comp(1, Sprite_Status(10, 17, 0.5));
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                keySystem(r, event.key.code);
        }
        window.clear(sf::Color::White);
        time = clock.getElapsedTime();
        checkSprite(r, time);
        display_drawable(window, r, texture);
        window.display();
    }
    return 0;
}