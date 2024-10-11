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

void Game::CreateMainThem(Register &r)
{
    r.creatEntity();
    r.emplace_comp(r.currentEntity, SoundLoop(1));
}

void Game::CreateBackGround(Register &r)
{
    r.creatEntity();
    r.emplace_comp(r.currentEntity, Drawable(3, std::nullopt, std::vector<float>{4, 4}));
    r.emplace_comp(r.currentEntity, Positions(0, 0));
}

void Game::CreatePlanet(Register &r)
{
    r.creatEntity();
    r.emplace_comp(r.currentEntity, Drawable(4, std::nullopt, std::vector<float>{3, 3}));
    r.emplace_comp(r.currentEntity, Positions(800, 200));
    r.emplace_comp(r.currentEntity, Move(Positions(-1, 0)));
    r.emplace_comp(r.currentEntity, LoopMove(Positions(1800, 200)));
}

void Game::CreatPlayer(Register &r, int height, int width)
{
    r.creatEntity();
    r.emplace_comp(r.currentEntity, Positions(100, 100));
    r.emplace_comp(r.currentEntity, Drawable(1, Rectangle{202, 0, 30, 18}, std::vector<float>{1.5, 1.5}));
    r.emplace_comp(r.currentEntity, Velocity({5, 5, 5, 5}));
    r.emplace_comp(r.currentEntity, Colision(30, 18));
    r.emplace_comp(r.currentEntity, Controllable());
    r.emplace_comp(r.currentEntity, Sprite_Status({{UP, 235}, {DOWN, 100}, {MID, 202}, {LEFT, 202}, {RIGHT, 202}}));
    r.emplace_comp(r.currentEntity, ScreenLimit(height * 2, width * 2));
    r.emplace_comp(r.currentEntity, Hitable(100, 40));
    r.emplace_comp(r.currentEntity, Shoot(0.5, RIGHT, 20, 2));
    r.emplace_comp(r.currentEntity, Life(30));
    r.emplace_comp(r.currentEntity, Type(CONTRO));
    r.emplace_comp(r.currentEntity, Exp(0));
    r.emplace_comp(r.currentEntity, Points());
    r.emplace_comp(r.currentEntity, Lvl(1));
    r.emplace_comp(r.currentEntity, DistanceKm());
    r.emplace_comp(r.currentEntity, Explosion(1, 4, -37, 0.2, 10, CONTRO, Rectangle{180, 300, 40, 40}, std::vector<float>{1.5, 1.5}));
}

void Game::CreateBoostModule(Register &r, std::size_t PlayerEntity)
{
    r.creatEntity();
    r.emplace_comp(r.currentEntity, Positions(0, 0));
    r.emplace_comp(r.currentEntity, Drawable(1, Rectangle{235, 20, 30, 30}, std::vector<float>{1.5, 1.5}));
    r.emplace_comp(r.currentEntity, Sprite_Animation(4, -33, 0.1));
    //r.emplace_comp(1, Hitable(17, 18));
    r.emplace_comp(r.currentEntity, Module({{LEFT, 0}, {UP, 7}, {RIGHT, 45}, {DOWN, 0}}, PlayerEntity));
    r.emplace_comp(r.currentEntity, Type(MODULE));
}

void Game::CreateShootModule(Register &r, Positions &&pos)
{
    r.creatEntity();
    r.emplace_comp(r.currentEntity, std::move(pos));
    r.emplace_comp(r.currentEntity, Drawable(2, Rectangle{208, 32, 20, 20}, std::vector<float>{1.5, 1.5}));
    r.emplace_comp(r.currentEntity, Move(Positions(-1, 0)));
    //r.emplace_comp(2, Sprite_Animation(10, 17, 0.05));
    r.emplace_comp(r.currentEntity, Hitable(20, 20));
    r.emplace_comp(r.currentEntity, ModuleShoot({{LEFT, 0}, {UP, 60}, {RIGHT, 0}, {DOWN, 0}}, 0.25));
    r.emplace_comp(r.currentEntity, Type(NEUTRAL));
}

void Game::CreateArmorModule(Register &r, Positions &&pos)
{
    r.creatEntity();
    r.emplace_comp(r.currentEntity, std::move(pos));
    r.emplace_comp(r.currentEntity, Move(Positions(-1, 0)));
    r.emplace_comp(r.currentEntity, Drawable(2, Rectangle{173, 345, 32, 32}, std::vector<float>{1.5, 1.5}));
    r.emplace_comp(r.currentEntity, Sprite_Animation(4, 32, 0.2));
    r.emplace_comp(r.currentEntity, Hitable(64, 64));
    r.emplace_comp(r.currentEntity, ModuleArmor({{LEFT, 100}, {UP, 0}, {RIGHT, 0}, {DOWN, 0}}, Life(1000), 10));
    r.emplace_comp(r.currentEntity, Type(NEUTRAL));
    r.emplace_comp(r.currentEntity, DoDmg(30));
    r.emplace_comp(r.currentEntity, Explosion(1, 4, -37, 0.2, 10, CONTRO, Rectangle{180, 300, 40, 40}, std::vector<float>{1.5, 1.5}));
}

static int randomYPos()
{
    // srand(time(0));
    // return 100 + rand() % (700 - 10 + 1);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(10, 700);
    return dist(mt) + 100;
}

void Game::CreateBomb(Register &r, Positions &&pos, float time, float reset)
{
    r.creatEntity();
    r.emplace_comp(r.currentEntity, MoveToPlayer(2));
    r.emplace_comp(r.currentEntity, std::move(pos));
    r.emplace_comp(r.currentEntity, Drawable(6, Rectangle{185, 140, 15, 15}, std::vector<float>{1, 1}));
    r.emplace_comp(r.currentEntity, MoveToPlayerTime(time, reset));
    r.emplace_comp(r.currentEntity, Short_Animation(4, 16, 1, 185));
    r.emplace_comp(r.currentEntity, Velocity({1, 1, 1, 1}));
    r.emplace_comp(r.currentEntity, Hitable(15, 15, Positions(1, -1)));
    r.emplace_comp(r.currentEntity, Enemy(100, 10));
    //r.emplace_comp(r.currentEntity, Life(30));
    r.emplace_comp(r.currentEntity, DoDmg(10));
    r.emplace_comp(r.currentEntity, Type(BOMB));
    r.emplace_comp(r.currentEntity, Explosion(1, 4, -37, 0.2, 10, BOMB, Rectangle{180, 300, 40, 40}, std::vector<float>{1.5, 1.5}));
}

void Game::CreateAsteroid(Register &r)
{
    r.creatEntity();
    r.emplace_comp(r.currentEntity, Positions(0, 0));
    r.emplace_comp(r.currentEntity, Move(Positions(-2, 0)));
    r.emplace_comp(r.currentEntity, Positions(1700, randomYPos()));
    r.emplace_comp(r.currentEntity, Drawable(0, Rectangle{0, 0, 17, 18}, std::vector<float>{1.5, 1.5}));
    r.emplace_comp(r.currentEntity, Sprite_Animation(10, 17, 0.05));
    r.emplace_comp(r.currentEntity, Velocity({1, 1, 1, 1}));
    r.emplace_comp(r.currentEntity, Hitable(35, 35, Positions(0, -1)));
    r.emplace_comp(r.currentEntity, Enemy(100, 10));
    r.emplace_comp(r.currentEntity, Life(30));
    r.emplace_comp(r.currentEntity, DoDmg(10));
    r.emplace_comp(r.currentEntity, Type(BOMB));
    r.emplace_comp(r.currentEntity, Explosion(1, 4, -37, 0.2, 10, BOMB, Rectangle{180, 300, 40, 40}, std::vector<float>{1.5, 1.5}));
}

void Game::CreateShipShoot(Register &r, Positions &&pos)
{
    r.creatEntity();
    r.emplace_comp(r.currentEntity, Drawable(1, Rectangle{229, 100, 20, 20}, std::vector<float>{1.5, 1.5}));
    r.emplace_comp(r.currentEntity, pos);
    r.emplace_comp(r.currentEntity, Move(Positions(10, 0)));
    r.emplace_comp(r.currentEntity, Hitable(40, 40));
    r.emplace_comp(r.currentEntity, Life(1));
    r.emplace_comp(r.currentEntity, DoDmg(10));
    r.emplace_comp(r.currentEntity, Type(SHIPSHOOT));
    r.emplace_comp(r.currentEntity, Explosion(1, 4, -37, 0.2, 10, SHIPSHOOT, Rectangle{180, 300, 40, 40}, std::vector<float>{1.5, 1.5}));
}

void Game::CreatText(Register &r, Positions &&pos, std::string text)
{
    r.creatEntity();
    r.emplace_comp(r.currentEntity, pos);
    // r.emplace_comp(r.currentEntity, Text(text, font, 30, sf::Color::Black));
}

void Game::CreateMessageTime(Register &r, Positions &&pos, std::string text, float time, float reset)
{
    r.creatEntity();
    r.emplace_comp(r.currentEntity, Message(text, std::move(pos), 20, RED));
    r.emplace_comp(r.currentEntity, MessageTime(time, reset));
}

void Game::CreateMiniBoss1(Register &r, Positions &&pos)
{
    r.creatEntity();
    r.emplace_comp(r.currentEntity, Drawable(5, Rectangle{432, 0, 144, 250}, std::vector<float>{1, 1}));
    r.emplace_comp(r.currentEntity, pos);
    r.emplace_comp(r.currentEntity, Animation2Time(Short_Animation(3, -144, 0.7), Short_Animation(3, 144, 0.7), {2.1, 2.1}, 10));
    //r.emplace_comp(r.currentEntity, Short_Animation(3, 144, 0.7));
    r.emplace_comp(r.currentEntity, DoDmg(20));
    r.emplace_comp(r.currentEntity, Life(2000));
    r.emplace_comp(r.currentEntity, Hitable(44, 64, Positions(0, 220)));
    r.emplace_comp(r.currentEntity, Type(MINIBOSS));
    r.emplace_comp(r.currentEntity, Invincible());
    r.emplace_comp(r.currentEntity, InvincibleTime(0, 5));
    r.emplace_comp(r.currentEntity, Enemy(10000, 100));
    r.emplace_comp(r.currentEntity, Explosion(1, 4, -37, 0.2, 10, MINIBOSS, Rectangle{180, 300, 40, 40}, std::vector<float>{10, 10}));
}
