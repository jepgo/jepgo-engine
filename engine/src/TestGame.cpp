/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** TestGame
*/

#include "TestGame.hpp"
#include <cstdlib>
#include <ctime> 

TestGame::TestGame(float reset) : _reset(reset)
{
    _time = 0;
}

TestGame::~TestGame()
{
}

static int randomYPos()
{
    srand(time(0));

    return 100 + rand() % (700 - 10 + 1);
}

void TestGame::generateRandomsEntitys(Register &r, sf::Time &time)
{
    if (time.asSeconds() - _time <= _reset)
        return;
    r.creatEntity();
    r.emplace_comp(r.entity_nbr, Positions(0, 0));
    r.emplace_comp(r.entity_nbr, Move(Positions(-1, 0)));
    r.emplace_comp(r.entity_nbr, Positions(1000, randomYPos()));
    r.emplace_comp(r.entity_nbr, Drawable(0, sf::IntRect(0, 0, 17, 18), std::vector<float>{1.5, 1.5}));
    r.emplace_comp(r.entity_nbr, Sprite_Animation(10, 17, 0.05));
    r.emplace_comp(r.entity_nbr, Velocity({1, 1, 1, 1}));
    r.emplace_comp(r.entity_nbr, Hitable(17, 18));
    r.emplace_comp(r.entity_nbr, Explosion(1, 4, -37, 0.2, sf::IntRect(180, 300, 40, 40), std::vector<float>{1.5, 1.5}));
    _time = time.asSeconds();
}
