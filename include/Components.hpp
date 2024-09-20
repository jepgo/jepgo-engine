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
    MID,
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
    Drawable(std::size_t ind, std::optional<sf::IntRect> r = std::nullopt, std::optional<std::vector<float>> s = std::nullopt)
    {
        rect = r;
        index = ind;
        if (s.has_value())
            scale = s.value();
        else {
            scale.push_back(1);
            scale.push_back(1);
        }
        sprite.setScale(scale[0], scale[1]);
    };
    ~Drawable() {};
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
    std::vector<float> scale;
    std::optional<sf::IntRect> rect;
};

class Sprite_Animation
{
public:
    Sprite_Animation(int sta, int value, double res)
    {
        status = sta;
        val = value;
        reset = res;
        t = 0;
    };
    ~Sprite_Animation() {};
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

class Sprite_Status {
    public:
        Sprite_Status(std::map<SPEED, int> s) : stat(s) {};
        ~Sprite_Status() {};
        int status(SPEED s) {
            return stat.at(s);
        };
        int mid() {return stat.at(MID);};
    private:
        std::map<SPEED, int> stat;
};

class Hitable
{
    public:
        /**
         * @brief Construct a new Hitable object
         * 
         * @param w the width of the object
         * @param h the hight of the object
         */
        Hitable(int w, int h) : width(w), height(h) {};
        ~Hitable() {};
        
        /**
         * @brief Methode to know if 2 hitable object touch each others
         * 
         * @param hit the other Hitable object
         * @param him The position of the second Hitable
         * @param me The Position of this Hitable
         * @return true 
         * @return false 
         */
        bool isHit(Hitable &hit, Positions &him, Positions &me) {
            if (me._x + width < him._x || me._x > him._x + hit.width || me._y + height < him._y || me._y > him._y + hit.height)
                return false;
            return true;
        };
    private:
        int width;
        int height;
};

class Controllable
{
public:
    Controllable() {};
    ~Controllable() {};
    void move(sf::Keyboard::Key key, Velocity &vel, Positions &pos, std::optional<Sprite_Status> &stat, std::optional<Drawable> &draw) {
        if (key != sf::Keyboard::Up && key != sf::Keyboard::Down && key != sf::Keyboard::Right && key != sf::Keyboard::Left)
            return;
        if (stat.has_value() && draw.has_value() && draw.value().getRect().has_value())
            draw.value().getRect().value().left = stat.value().status(ASSOCIATIVE_KEYS.at(key));
        return vel.move(ASSOCIATIVE_KEYS.at(key), pos);
    };

private:
};
