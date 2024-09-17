/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Components
*/

#pragma once
#include <SFML/Graphics.hpp>

class Positions {
    public:
        Positions(int x, int y) {
            _x = x;
            _y = y;
        }
        ~Positions() {};
        int _x;
        int _y;
};

// class Velocity : public IComponents {
//     public:
//         Velocity();
//         ~Velocity();

//     protected:
//     private:
// }; 

class Drawable
{
    public:
        Drawable(std::string file) {
            texture.loadFromFile(file.c_str());
            texture.setSmooth(true);
            sprite.setTexture(texture);
            //sprite.setTextureRect();
        };
        ~Drawable() {};
        void draw(sf::RenderWindow &window, Positions pos)
        {
            sprite.setPosition(sf::Vector2f());
            window.draw(sprite);
        }

    private:
        sf::Sprite sprite;
        sf::Texture texture;
};

// class Controllable : public IComponents
// {
//     public:
//         Controllable();
//         ~Controllable();

//     protected:
//     private:
// };
