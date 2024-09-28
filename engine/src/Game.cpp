/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Game
*/

#include "Game.hpp"

Game::Game()
{
    _point = 0;
    _exp = 0;
    _lvl = 1;
    _km = 0;
}

Game::~Game()
{
}

void Game::CreateMainThem(Register &r) {
    r.creatEntity();
    r.emplace_comp(r.entity_nbr, SoundLoop(1, 32));
}

void Game::CreatPlayer(Register &r, int height, int width)
{
    r.creatEntity();
    r.emplace_comp(r.entity_nbr, Positions(100, 100));
    r.emplace_comp(r.entity_nbr, Drawable(1, sf::IntRect(202, 0, 30, 18), std::vector<float>{1.5, 1.5}));
    //   r.emplace_comp(0, Sprite_Animation(10, 17, 0.05));
    r.emplace_comp(r.entity_nbr, Velocity({2, 2, 2, 2}));
    r.emplace_comp(r.entity_nbr, Colision(30, 18));
    r.emplace_comp(r.entity_nbr, Controllable());
    r.emplace_comp(r.entity_nbr, Sprite_Status({{UP, 235}, {DOWN, 100}, {MID, 202}, {LEFT, 202}, {RIGHT, 202}}));
    r.emplace_comp(r.entity_nbr, ScreenLimit(height, width));
    r.emplace_comp(r.entity_nbr, Hitable(30, 18));
    r.emplace_comp(r.entity_nbr, Shoot(0.5, RIGHT, 20));
    r.emplace_comp(r.entity_nbr, Life(30));
    r.emplace_comp(r.entity_nbr, Type(CONTRO));
    r.emplace_comp(r.entity_nbr, Explosion(1, 4, -37, 0.2, 10, CONTRO, sf::IntRect(180, 300, 40, 40), std::vector<float>{1.5, 1.5}));
}

void Game::CreateBoostModule(Register &r) {
    r.creatEntity();
    r.emplace_comp(r.entity_nbr, Positions(0, 0));
    r.emplace_comp(r.entity_nbr, Drawable(1, sf::IntRect(235, 20, 30, 30), std::vector<float>{1.5, 1.5}));
    r.emplace_comp(r.entity_nbr, Sprite_Animation(4, -33, 0.1));
    //r.emplace_comp(1, Hitable(17, 18));
    r.emplace_comp(r.entity_nbr, Module({{LEFT, 0}, {UP, 7}, {RIGHT, 45}, {DOWN, 0}}, 0));
    r.emplace_comp(r.entity_nbr, Type(MODULE));
}

void Game::CreateShootModule(Register &r, Positions &&pos)
{
    r.creatEntity();
    r.emplace_comp(r.entity_nbr, std::move(pos));
    r.emplace_comp(r.entity_nbr, Drawable(2, sf::IntRect(208, 32, 20, 20), std::vector<float>{1.5, 1.5}));
    r.emplace_comp(r.entity_nbr, Move(Positions(-1, 0)));
    //r.emplace_comp(2, Sprite_Animation(10, 17, 0.05));
    r.emplace_comp(r.entity_nbr, Hitable(20, 20));
    r.emplace_comp(r.entity_nbr, ModuleShoot({{LEFT, 0}, {UP, 30}, {RIGHT, 0}, {DOWN, 0}}, 0.25));
    r.emplace_comp(r.entity_nbr, Type(MODULE));
}

void Game::CreateArmorModule(Register &r, Positions &&pos)
{
    r.creatEntity();
    r.emplace_comp(r.entity_nbr, std::move(pos));
    r.emplace_comp(r.entity_nbr, Move(Positions(-1, 0)));
    r.emplace_comp(r.entity_nbr, Drawable(2, sf::IntRect(173, 345, 32, 32), std::vector<float>{1.5, 1.5}));
    r.emplace_comp(r.entity_nbr, Sprite_Animation(4, 32, 0.2));
    r.emplace_comp(r.entity_nbr, Hitable(32, 32));
    r.emplace_comp(r.entity_nbr, ModuleArmor({{LEFT, 50}, {UP, 0}, {RIGHT, 0}, {DOWN, 0}}, Life(100), 10));
    r.emplace_comp(r.entity_nbr, Type(MODULE));
    r.emplace_comp(r.entity_nbr, DoDmg(30));
    r.emplace_comp(r.entity_nbr, Explosion(1, 4, -37, 0.2, 10, CONTRO, sf::IntRect(180, 300, 40, 40), std::vector<float>{1.5, 1.5}));
}

static int randomYPos()
{
    srand(time(0));

    return 100 + rand() % (700 - 10 + 1);
}

void Game::CreateAsteroid(Register &r)
{
    r.creatEntity();
    r.emplace_comp(r.entity_nbr, Positions(0, 0));
    r.emplace_comp(r.entity_nbr, Move(Positions(-1, 0)));
    r.emplace_comp(r.entity_nbr, Positions(1000, randomYPos()));
    r.emplace_comp(r.entity_nbr, Drawable(0, sf::IntRect(0, 0, 17, 18), std::vector<float>{1.5, 1.5}));
    r.emplace_comp(r.entity_nbr, Sprite_Animation(10, 17, 0.05));
    r.emplace_comp(r.entity_nbr, Velocity({1, 1, 1, 1}));
    r.emplace_comp(r.entity_nbr, Hitable(17, 18));
    r.emplace_comp(r.entity_nbr, Enemy(100, 10));
    r.emplace_comp(r.entity_nbr, Life(30));
    r.emplace_comp(r.entity_nbr, DoDmg(10));
    r.emplace_comp(r.entity_nbr, Type(BOMB));
    r.emplace_comp(r.entity_nbr, Explosion(1, 4, -37, 0.2, 10, BOMB, sf::IntRect(180, 300, 40, 40), std::vector<float>{1.5, 1.5}));
}

void Game::CreateShipShoot(Register &r, Positions && pos)
{
    r.creatEntity();
    r.emplace_comp(r.entity_nbr, Drawable(1, sf::IntRect(229, 100, 20, 20), std::vector<float>{1.5, 1.5}));
    r.emplace_comp(r.entity_nbr, pos);
    r.emplace_comp(r.entity_nbr, Move(Positions(4, 0)));
    r.emplace_comp(r.entity_nbr, Hitable(10, 10));
    r.emplace_comp(r.entity_nbr, Life(1));
    r.emplace_comp(r.entity_nbr, DoDmg(10));
    r.emplace_comp(r.entity_nbr, Type(SHIPSHOOT));
    r.emplace_comp(r.entity_nbr, Explosion(1, 4, -37, 0.2, 10, SHIPSHOOT, sf::IntRect(180, 300, 40, 40), std::vector<float>{1.5, 1.5}));
}

void Game::CreatText(Register &r, Positions &&pos, std::string text, sf::Font &font)
{
    r.creatEntity();
    r.emplace_comp(r.entity_nbr, pos);
    r.emplace_comp(r.entity_nbr, Text(text, font, 30, sf::Color::Black));
}

void Game::CreateMiniBoss1(Register &r, Positions &&pos)
{
    r.creatEntity();
    r.emplace_comp(r.entity_nbr, Drawable(5, sf::IntRect(0, 0, 140, 250), std::vector<float>{1, 1}));
    r.emplace_comp(r.entity_nbr, pos);
    r.emplace_comp(r.entity_nbr, DoDmg(20));
    r.emplace_comp(r.entity_nbr, Life(3000));
    r.emplace_comp(r.entity_nbr, Hitable(20, 30, Positions(0, 110)));
    r.emplace_comp(r.entity_nbr, Type(MINIBOSS));
    r.emplace_comp(r.entity_nbr, Invincible());
    r.emplace_comp(r.entity_nbr, InvincibleTime(0, 10));
    r.emplace_comp(r.entity_nbr, Enemy(10000, 100));
    r.emplace_comp(r.entity_nbr, Explosion(1, 4, -37, 0.2, 10, MINIBOSS, sf::IntRect(180, 300, 40, 40), std::vector<float>{10, 10}));
}
