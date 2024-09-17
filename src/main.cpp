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

void display_drawable(sf::RenderWindow &window, std::map<std::type_index, std::any> &map)
{
    SparseArray<Positions> pos = std::any_cast<SparseArray<Positions>>(map[std::type_index(typeid(Positions))]);
    SparseArray<Drawable> draw = std::any_cast<SparseArray<Drawable>>(map[std::type_index(typeid(Drawable))]);
    sf::RectangleShape rect(sf::Vector2f(0, 0));
    rect.setSize(sf::Vector2f(10, 10));
    rect.setFillColor(sf::Color(sf::Color::Black));

    for (std::size_t i = 0; i < draw.size(); i++) {
        if (draw[i].has_value()) {
            rect.setPosition(pos[i].value()._x, pos[i].value()._y);
            window.draw(rect);
        }
    }
}

int main()
{
    Register r;
    sf::Event event;
    sf::RenderWindow window(sf::VideoMode(800, 600), "R-TYPE");

    r.creatEntity();
    r.add_comp(0, Positions(10, 10));   
    r.add_comp(0, Drawable()); 
    //r.emplace_comp<Positions>(0, 10, 10);   
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);
        display_drawable(window, r.getRegister());
        window.display();
    }
    return 0;    
}