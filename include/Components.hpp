/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Components
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Positions
{
public:
    Positions(int x, int y)
    {
        _x = x;
        _y = y;
    }
    ~Positions() {};
    int _x;
    int _y;
};

struct Speed
{
    std::size_t up;
    std::size_t down;
    std::size_t left;
    std::size_t right;
};

enum SPEED
{
    UP,
    DOWN,
    RIGHT,
    LEFT,
};

class Velocity
{
public:
    Velocity(std::vector<double> s)
    {
        speed = s;
    };
    ~Velocity() {};
    void move(SPEED s, Positions &pos)
    {
        if (s == UP)
            pos._y -= 1 * speed[UP];
        if (s == DOWN)
            pos._y += 1 * speed[DOWN];
        if (s == LEFT)
            pos._x -= 1 * speed[LEFT];
        if (s == RIGHT)
            pos._x += 1 * speed[RIGHT];
    };

private:
    std::vector<double> speed;
};

class Drawable
{
public:
    Drawable(std::size_t ind, std::optional<sf::IntRect> r = std::nullopt)
    {
        rect = r;
        index = ind;
    };
    ~Drawable() {
    };
    void draw(sf::RenderWindow &window, sf::Texture &texture, Positions &pos)
    {
        sprite.setTexture(texture);
        if (rect.has_value())
            sprite.setTextureRect(rect.value());
        sprite.setPosition(sf::Vector2f(pos._x, pos._y));
        window.draw(sprite);
    }
    void change_ind(std::size_t ind) { index = ind; };
    std::size_t getIndex() { return index; };
    std::optional<sf::IntRect> &getRect() { return rect; };

private:
    sf::Sprite sprite;
    std::size_t index;
    std::optional<sf::IntRect> rect;
};

class Sprite_Status
{
public:
    Sprite_Status(int sta, int value, double res)
    {
        status = sta;
        val = value;
        reset = res;
        t = 0;
    };
    ~Sprite_Status() {};
    void setTime(sf::Time time)
    {
        t = time.asSeconds();
    };
    int status;
    int val;
    double reset;
    double t;
};

static std::map<sf::Keyboard::Key, SPEED> const ASSOCIATIVE_KEYS = {
    {sf::Keyboard::Up, UP},
    {sf::Keyboard::Down, DOWN},
    {sf::Keyboard::Left, LEFT},
    {sf::Keyboard::Right, RIGHT},
};

class Controllable
{
public:
    Controllable() {};
    ~Controllable() {};
    void move(sf::Keyboard::Key key, Velocity &vel, Positions &pos) {
        return vel.move(ASSOCIATIVE_KEYS.at(key), pos);
    };

private:
};
