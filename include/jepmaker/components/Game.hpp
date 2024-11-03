/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Game
*/

#pragma once
#include "jepengine/Client.hpp"
#include "jepmaker/components/Position.hpp"
#include "jepmaker/components/SoundLoop.hpp"
#include "jepmaker/components/Move.hpp"
#include "jepmaker/components/Life.hpp"
#include "jepmaker/components/Hitable2D.hpp"
#include "jepmaker/components/Drawable2D.hpp"
#include "jepmaker/components/SpriteAnimation.hpp"
#include "jepmaker/components/SpriteStatus.hpp"
#include "jepmaker/components/Velocity.hpp"
#include "jepmaker/components/Type.hpp"
#include "jepmaker/components/Enemy.hpp"
#include "jepmaker/components/DoDmg.hpp"
#include "jepmaker/components/Explosion.hpp"
#include "jepmaker/components/MoveToPlayer.hpp"
#include "jepmaker/components/MoveToPlayerTime.hpp"
#include "jepmaker/components/ShortAnimation.hpp"
#include "jepmaker/components/Colision.hpp"
#include "jepmaker/components/ScreenLimit.hpp"
#include "jepmaker/components/Shoot.hpp"
#include "jepmaker/components/LoopMove.hpp"
#include "jepmaker/components/Modules.hpp"
#include "jepmaker/components/Controllable.hpp"
#include "jepmaker/components/Reborn.hpp"
#include "jepmaker/components/DrawReborn.hpp"
#include "jepmaker/components/Exp.hpp"
#include "jepmaker/components/Points.hpp"
#include "jepmaker/components/DrawPoints.hpp"
#include "jepmaker/components/Lvl.hpp"
#include "jepmaker/components/DrawLvl.hpp"
#include "jepmaker/components/DistanceKm.hpp"
#include "jepmaker/components/DrawDistanceKm.hpp"
#include "jepmaker/components/Message.hpp"
#include "jepmaker/components/MessageTime.hpp"
#include "jepmaker/components/GameLvl.hpp"

#include <random>

class Game {
    public:
        static int randomYPos() {
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_real_distribution<double> dist(10, 700);
            return 100 + dist(mt);
            }
        static void CreateMainThem(jgo::Game &game) {
            game.ecs.createEntity();
            game.ecs.emplaceComp(game.ecs.currentEntity, SoundLoop(""));
        };
        static void CreateEasyEnemies(jgo::Game &r) {
            r.ecs.createEntity();
            r.ecs.emplaceComp(r.ecs.currentEntity, Positions(0, 0));
            r.ecs.emplaceComp(r.ecs.currentEntity, Move(Positions(-1, 0)));
            r.ecs.emplaceComp(r.ecs.currentEntity, Positions(1700, randomYPos()));
            r.ecs.emplaceComp(r.ecs.currentEntity, Drawable("sprites/r-typesheet3.gif", jgo::Rectangle{0, 0, 17, 18}, std::vector<float>{1.5, 1.5}));
            r.ecs.emplaceComp(r.ecs.currentEntity, Sprite_Animation(10, 17, 0.5));
            r.ecs.emplaceComp(r.ecs.currentEntity, Velocity({0.5, 0.5}));
            r.ecs.emplaceComp(r.ecs.currentEntity, Hitable(35, 35, Positions(0, -1)));
            r.ecs.emplaceComp(r.ecs.currentEntity, Enemy(100, 10));
            r.ecs.emplaceComp(r.ecs.currentEntity, Life(10));
            r.ecs.emplaceComp(r.ecs.currentEntity, DoDmg(5));
            r.ecs.emplaceComp(r.ecs.currentEntity, Type(BOMB));
            r.ecs.emplaceComp(r.ecs.currentEntity, Explosion("sprites/r-typesheet1.gif", 4, -37, 0.5, 10, jgo::Rectangle{180, 300, 40, 40}, std::vector<float>{1.5, 1.5}));
        };
        static void CreateObstacle(jgo::Game &r) {
            r.ecs.createEntity();
            r.ecs.emplaceComp(r.ecs.currentEntity, Positions(0, 0));
            r.ecs.emplaceComp(r.ecs.currentEntity, Move(Positions(-2, 0)));
            r.ecs.emplaceComp(r.ecs.currentEntity, Positions(1700, randomYPos()));
            r.ecs.emplaceComp(r.ecs.currentEntity, Drawable("sprites/parallax-space-stars.png", jgo::Rectangle{0, 0, 840, 859}, std::vector<float>{0.05, 0.05}));
            r.ecs.emplaceComp(r.ecs.currentEntity, Velocity({2, 2}));
            r.ecs.emplaceComp(r.ecs.currentEntity, Hitable(35, 35, Positions(0, -1)));
            r.ecs.emplaceComp(r.ecs.currentEntity, Enemy(100, 10));
            r.ecs.emplaceComp(r.ecs.currentEntity, Life(10));
            r.ecs.emplaceComp(r.ecs.currentEntity, DoDmg(10));
            r.ecs.emplaceComp(r.ecs.currentEntity, Type(BOMB));
            r.ecs.emplaceComp(r.ecs.currentEntity, Explosion("sprites/r-typesheet1.gif", 4, -37, 0.5, 10, jgo::Rectangle{180, 300, 40, 40}, std::vector<float>{1.5, 1.5}));
        };
        static void CreateBackGround(jgo::Game &r) {
            r.ecs.createEntity();
            r.ecs.emplaceComp(r.ecs.currentEntity, Drawable("sprites/parallax-space-backgound.png", std::nullopt, std::vector<float>{4, 4}));
            r.ecs.emplaceComp(r.ecs.currentEntity, Positions(0, 0));
        };
        static void CreateSpaceShip(jgo::Game &r, float time) {
            r.ecs.createEntity();
            r.ecs.emplaceComp(r.ecs.currentEntity, Positions(0, 0));
            r.ecs.emplaceComp(r.ecs.currentEntity, Move(Positions(-4, 0)));
            r.ecs.emplaceComp(r.ecs.currentEntity, Positions(1700, randomYPos()));
            r.ecs.emplaceComp(r.ecs.currentEntity, Drawable("11", jgo::Rectangle{0, 0, 32, 23}, std::vector<float>{1.5, 1.5}));
            r.ecs.emplaceComp(r.ecs.currentEntity, Sprite_Animation(8, 32, 0.3));
            r.ecs.emplaceComp(r.ecs.currentEntity, Velocity({1, 1}));
            r.ecs.emplaceComp(r.ecs.currentEntity, Hitable(35, 35, Positions(0, -1)));
            r.ecs.emplaceComp(r.ecs.currentEntity, Enemy(100, 10));
            r.ecs.emplaceComp(r.ecs.currentEntity, Life(30));
            r.ecs.emplaceComp(r.ecs.currentEntity, DoDmg(10));
            r.ecs.emplaceComp(r.ecs.currentEntity, Type(BOMB));
            r.ecs.emplaceComp(r.ecs.currentEntity, MoveToPlayer(4));
            r.ecs.emplaceComp(r.ecs.currentEntity, MoveToPlayerTime(time, 6));
            r.ecs.emplaceComp(r.ecs.currentEntity, Explosion("sprites/r-typesheet1.gif", 4, -37, 0.5, 10, jgo::Rectangle{180, 300, 40, 40}, std::vector<float>{1.5, 1.5}));
        };
        static void CreateBomb(jgo::Game &r, Positions &&pos, float time, float reset) {
            r.ecs.createEntity();
            r.ecs.emplaceComp(r.ecs.currentEntity, MoveToPlayer(4));
            r.ecs.emplaceComp(r.ecs.currentEntity, std::move(pos));
            r.ecs.emplaceComp(r.ecs.currentEntity, Drawable("", jgo::Rectangle{185, 140, 15, 15}, std::vector<float>{1, 1}));
            r.ecs.emplaceComp(r.ecs.currentEntity, MoveToPlayerTime(time, reset));
            r.ecs.emplaceComp(r.ecs.currentEntity, Short_Animation(4, 16, 1, 185));
            r.ecs.emplaceComp(r.ecs.currentEntity, Velocity({1, 1}));
            r.ecs.emplaceComp(r.ecs.currentEntity, Hitable(30, 30, Positions(1, -1)));
            r.ecs.emplaceComp(r.ecs.currentEntity, Enemy(100, 10));
            //r.ecs.emplaceComp(r.ecs.currentEntity, Life(30));
            r.ecs.emplaceComp(r.ecs.currentEntity, DoDmg(10));
            r.ecs.emplaceComp(r.ecs.currentEntity, Type(BOMB));
            r.ecs.emplaceComp(r.ecs.currentEntity, Explosion("sprites/r-typesheet1.gif", 4, -37, 0.5, 10, jgo::Rectangle{180, 300, 40, 40}, std::vector<float>{1.5, 1.5}));

        };
        static void CreatePlanet(jgo::Game &r) {
            r.ecs.createEntity();
            r.ecs.emplaceComp(r.ecs.currentEntity, Drawable("", std::nullopt, std::vector<float>{3, 3}));
            r.ecs.emplaceComp(r.ecs.currentEntity, Positions(800, 200));
            r.ecs.emplaceComp(r.ecs.currentEntity, Move(Positions(-1, 0)));
            r.ecs.emplaceComp(r.ecs.currentEntity, LoopMove(Positions(1800, 200)));
        };
        static void CreateFarPlanet(jgo::Game &r) {
            r.ecs.createEntity();
            r.ecs.emplaceComp(r.ecs.currentEntity, Drawable("", std::nullopt, std::vector<float>{3, 3}));
            r.ecs.emplaceComp(r.ecs.currentEntity, Positions(400, 200));
            r.ecs.emplaceComp(r.ecs.currentEntity, Move(Positions(-1, 0)));
            r.ecs.emplaceComp(r.ecs.currentEntity, LoopMove(Positions(100, 100)));
        };
        static void CreateStars(jgo::Game &r) {
            int screenWidth = 600;
            for (int i = 0; i < 2; ++i) {
                r.ecs.createEntity();
                r.ecs.emplaceComp(r.ecs.currentEntity, Drawable("sprites/parallax-space-stars.png", std::nullopt, std::vector<float>{3, 3}));
                r.ecs.emplaceComp(r.ecs.currentEntity, Positions(screenWidth - 400, 0));
                r.ecs.emplaceComp(r.ecs.currentEntity, Move(Positions(-1, 0)));
                r.ecs.emplaceComp(r.ecs.currentEntity, LoopMove(Positions(screenWidth - 400, 0)));
            }
        };
        static void CreateRingPlanet(jgo::Game &r) {
            r.ecs.createEntity();
            r.ecs.emplaceComp(r.ecs.currentEntity, Drawable("", std::nullopt, std::vector<float>{2, 2}));
            r.ecs.emplaceComp(r.ecs.currentEntity, Positions(500, 150));
            r.ecs.emplaceComp(r.ecs.currentEntity, Move(Positions(-1, 0)));
            r.ecs.emplaceComp(r.ecs.currentEntity, LoopMove(Positions(5400, 600)));
        };
        static void CreateShipShoot(jgo::Game &r, Positions &&pos) {
            r.ecs.createEntity();
            r.ecs.emplaceComp(r.ecs.currentEntity, Drawable("sprites/r-typesheet1.gif", jgo::Rectangle{229, 100, 20, 20}, std::vector<float>{1.5, 1.5}));
            r.ecs.emplaceComp(r.ecs.currentEntity, std::move(pos));
            r.ecs.emplaceComp(r.ecs.currentEntity, Move(Positions(10, 0)));
            r.ecs.emplaceComp(r.ecs.currentEntity, Hitable(40, 40));
            r.ecs.emplaceComp(r.ecs.currentEntity, Life(1));
            r.ecs.emplaceComp(r.ecs.currentEntity, DoDmg(10));
            r.ecs.emplaceComp(r.ecs.currentEntity, Type(SHIPSHOOT));
            r.ecs.emplaceComp(r.ecs.currentEntity, Explosion("sprites/r-typesheet1.gif", 4, -37, 0.5, 10, jgo::Rectangle{180, 300, 40, 40}, std::vector<float>{1.5, 1.5}));

        };
        static void CreateMiniBoss1(jgo::Game &r, Positions &&) {

        };
        static void CreateShootModule(jgo::Game &r, Positions &&pos) {
            r.ecs.createEntity();
            r.ecs.emplaceComp(r.ecs.currentEntity, std::move(pos));
            r.ecs.emplaceComp(r.ecs.currentEntity, Drawable("sprites/r-typesheet2.gif", jgo::Rectangle{208, 32, 20, 20}, std::vector<float>{1.5, 1.5}));
            r.ecs.emplaceComp(r.ecs.currentEntity, Move(Positions(1, 0)));
            //r.ecs.emplaceComp(2, Sprite_Animation(10, 17, 0.05));
            r.ecs.emplaceComp(r.ecs.currentEntity, Hitable(20, 20));
            r.ecs.emplaceComp(r.ecs.currentEntity, ModuleShoot({{LEFT, 20}, {UP, 60}, {RIGHT, 0}, {DOWN, 0}}, 0.25));
            r.ecs.emplaceComp(r.ecs.currentEntity, Type(NEUTRAL));

        };
        static void CreateArmorModule(jgo::Game &r, Positions &&pos, float time) {
            r.ecs.createEntity();
            r.ecs.emplaceComp(r.ecs.currentEntity, std::move(pos));
            r.ecs.emplaceComp(r.ecs.currentEntity, Move(Positions(1, 0)));
            r.ecs.emplaceComp(r.ecs.currentEntity, Drawable("sprites/r-typesheet2.gif", jgo::Rectangle{173, 345, 32, 32}, std::vector<float>{1.5, 1.5}));
            //r.ecs.emplaceComp(r.ecs.currentEntity, Model3D(0, 30, 10, 10, 80));
            //r.ecs.emplaceComp(r.ecs.currentEntity, RotationTime((Vector3){1, 0, 0}, 0, time, 0.1));
            r.ecs.emplaceComp(r.ecs.currentEntity, Sprite_Animation(4, 32, 0.5));
            r.ecs.emplaceComp(r.ecs.currentEntity, Hitable(80, 90));
            r.ecs.emplaceComp(r.ecs.currentEntity, ModuleArmor({{LEFT, 170}, {UP, 0}, {RIGHT, 0}, {DOWN, 0}}, Life(1000), 10));
            r.ecs.emplaceComp(r.ecs.currentEntity, Type(NEUTRAL));
            r.ecs.emplaceComp(r.ecs.currentEntity, DoDmg(30));
            r.ecs.emplaceComp(r.ecs.currentEntity, Explosion("sprites/r-typesheet1.gif", 4, -37, 0.5, 10, jgo::Rectangle{180, 300, 40, 40}, std::vector<float>{1.5, 1.5}));
        };
        static void CreatePlayer(jgo::Game &r, int height, int width) {
            r.ecs.createEntity();
            r.ecs.emplaceComp(r.ecs.currentEntity, Positions(200, 200));
            r.ecs.emplaceComp(r.ecs.currentEntity, Drawable("sprites/r-typesheet1.gif", jgo::Rectangle{202, 0, 30, 18}, std::vector<float>{1.5, 1.5}));
            //r.ecs.emplaceComp(r.ecs.currentEntity, Model3D(1, 70, 40, 10));
            r.ecs.emplaceComp(r.ecs.currentEntity, Velocity({3, 3}));
            r.ecs.emplaceComp(r.ecs.currentEntity, Colision(30, 18));
            r.ecs.emplaceComp(r.ecs.currentEntity, Controllable());
            r.ecs.emplaceComp(r.ecs.currentEntity, Sprite_Status({{UP, 235}, {DOWN, 100}, {MID, 202}, {LEFT, 202}, {RIGHT, 202}}));
            r.ecs.emplaceComp(r.ecs.currentEntity, ScreenLimit(height * 2, width * 2));
            r.ecs.emplaceComp(r.ecs.currentEntity, Hitable(100, 40));
            r.ecs.emplaceComp(r.ecs.currentEntity, Life(1));
            r.ecs.emplaceComp(r.ecs.currentEntity, Reborn(3));
            //r.ecs.emplaceComp(r.ecs.currentEntity, DrawReborn(Positions(10, 560), 15, ));
            r.ecs.emplaceComp(r.ecs.currentEntity, Shoot(0.5, RIGHT, 20, 2));
            r.ecs.emplaceComp(r.ecs.currentEntity, Type(CONTRO));
            r.ecs.emplaceComp(r.ecs.currentEntity, Exp(0));
            r.ecs.emplaceComp(r.ecs.currentEntity, Points());
            //r.ecs.emplaceComp(r.ecs.currentEntity, DrawPoints(Positions(10, 500), 20, GREEN));
            r.ecs.emplaceComp(r.ecs.currentEntity, Lvl(1));
            r.ecs.emplaceComp(r.ecs.currentEntity, DoDmg(10));
            //r.ecs.emplaceComp(r.ecs.currentEntity, DrawLvl(Positions(10, 540), 15, RED));
            r.ecs.emplaceComp(r.ecs.currentEntity, DistanceKm());
            //r.ecs.emplaceComp(r.ecs.currentEntity, DrawKm(Positions(650, 20), 30, GREEN));
            r.ecs.emplaceComp(r.ecs.currentEntity, Explosion("sprites/r-typesheet1.gif", 4, -37, 0.5, 10, jgo::Rectangle{180, 300, 40, 40}, std::vector<float>{1.5, 1.5}));
            r.loadLevel("Level1");
            // std::map<std::size_t, std::shared_ptr<jgo::ILevels>> tmp = {{1, std::make_shared<Level1>()}};
            // r.ecs.emplaceComp(r.ecs.currentEntity, GameLvl(1, std::map<std::size_t, std::shared_ptr<jgo::ILevels>>{tmp}));
        };
        static void CreateBoostModule(jgo::Game &r, std::size_t PlayerEntity) {
            r.ecs.createEntity();
            r.ecs.emplaceComp(r.ecs.currentEntity, Positions(0, 0));
            r.ecs.emplaceComp(r.ecs.currentEntity, Drawable("sprites/r-typesheet1.gif", jgo::Rectangle{235, 20, 30, 30}, std::vector<float>{1.5, 1.5}));
            r.ecs.emplaceComp(r.ecs.currentEntity, Sprite_Animation(4, -33, 0.3));
            //r.ecs.emplaceComp(1, Hitable(17, 18));
            r.ecs.emplaceComp(r.ecs.currentEntity, Module({{LEFT, 0}, {UP, 15}, {RIGHT, 65}, {DOWN, 0}}, PlayerEntity));
            r.ecs.emplaceComp(r.ecs.currentEntity, Type(MODULE));
        };
        static void CreateMessageTime(jgo::Game &r, Positions &&pos, std::string text, float time, float reset) {
            r.ecs.createEntity();
            // r.ecs.emplaceComp(r.ecs.currentEntity, Message(text, std::move(pos), 20, RED));
            // r.ecs.emplaceComp(r.ecs.currentEntity, MessageTime(time, reset));
        };
        std::size_t &getExp() {return _exp;};
        std::size_t &getPoint() {return _point;};
        std::size_t &getLvl() {return _lvl;};
        std::size_t &getKm() {return _km;};
        std::map<std::size_t, std::unique_ptr<jgo::ILevels>> &getGameLvls() {return _gameLvls;};
    private:
        std::size_t _exp;
        std::size_t _point;
        std::size_t _lvl;
        std::size_t _km;
        std::map<std::size_t, std::unique_ptr<jgo::ILevels>> _gameLvls;
};