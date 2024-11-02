
/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** RebornSystem
*/

#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"
#include "jepmaker/components/Game.hpp"
#include "jepmaker/components/Reborn.hpp"
#include "jepmaker/components/Controllable.hpp"
#include "jepmaker/components/Message.hpp"
#include "jepmaker/components/Invincible.hpp"
#include "jepmaker/components/InvincibleTime.hpp"

static bool SearchKey(int key, std::vector<jgo::u32> &tmp)
{
    for (auto &t : tmp) {
        if (key == t)
            return true;
    }
    return false;
}

exported(void) jepgoSystem(jgo::Game &game, float &time)
{
    int playerEntity = -1;
    auto &reborn = game.ecs.getComp<Reborn>();
    auto &contro = game.ecs.getComp<Controllable>();
    auto &mess = game.ecs.getComp<Message>();
    auto &type = game.ecs.getComp<Type>();
    auto &life = game.ecs.getComp<Life>();
    std::vector<jgo::u32> &key = std::any_cast<std::vector<jgo::u32>&>(game.storage["keys"]);

    for (std::size_t i = 0; i < type.size(); i++) {
        if (type[i].has_value() && type[i].value().getType() == CONTRO)
            playerEntity = i;
    }
    if (playerEntity == -1) {
        return;
    }
    for (std::size_t i = 0; i < reborn.size(); i++){
        if (SearchKey(32, key) && reborn[i].has_value() && reborn[i].value().getLive() > 0 && life[i].has_value() && life[i].value()._life <= 0){
            //std::cout << "rebornnnnnnnnnnnnnnnnnn" << std::endl;
            reborn[i].value().getLive() -= 1;
            game.ecs.removeComponent<Sprite_Animation>(i);
            game.ecs.emplaceComp(i, Controllable());
            game.ecs.emplaceComp(i, Positions(100, 100));
            game.ecs.emplaceComp(i, Sprite_Status({{UP, 235}, {DOWN, 100}, {MID, 202}, {LEFT, 202}, {RIGHT, 202}}));
            game.ecs.emplaceComp(i, Drawable("sprites/r-typesheet1.gif", jgo::Rectangle{202, 0, 30, 18}, std::vector<float>{1.5, 1.5}));
            game.ecs.emplaceComp(i, Hitable(100, 40));
            game.ecs.emplaceComp(i, Life(1));
            game.ecs.emplaceComp(i, Type(CONTRO));
            game.ecs.emplaceComp(i, Shoot(0.5, RIGHT, 20, 2));
            game.ecs.emplaceComp(i, Invincible());
            game.ecs.emplaceComp(i, InvincibleTime(game.getTime(), 2));
            game.ecs.emplaceComp(i, Explosion("sprites/r-typesheet1.gif", 4, -37, 0.2, 10, jgo::Rectangle{180, 300, 40, 40}, std::vector<float>{1.5, 1.5}));
            Game::CreateBoostModule(game, i);
            for (std::size_t a = 0; a < mess.size(); a++) {
                if (mess[a].has_value())
                    game.ecs.removeComponent<Message>(a);
            }
        }
    }
};