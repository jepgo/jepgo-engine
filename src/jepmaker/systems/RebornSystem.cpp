
/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** RebornSystem
*/

#pragma once
#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"
#include "jepmaker/components/Game.hpp"
#include "jepmaker/components/Reborn.hpp"
#include "jepmaker/components/Controllable.hpp"
#include "jepmaker/components/Message.hpp"

static bool SearchKey(int key, std::vector<jgo::u32> tmp)
{
    for (auto &t : tmp) {
        if (key == t)
            return true;
    }
    return false;
}

exported(void) jepgoSystem(jgo::Game &game, float &time)
{
    std::vector<jgo::u32> key;
    std::size_t playerEntity = 0;
    auto &reborn = game.ecs.getComp<Reborn>();
    auto &contro = game.ecs.getComp<Controllable>();
    auto &mess = game.ecs.getComp<Message>();

    for (std::size_t i = 0; i < contro.size(); i++)
        if (contro[i].has_value())
            playerEntity = i;
    
    key = game.getGraphicLib()->getKeyPressed();
    for (std::size_t i = 0; i < reborn.size(); i++){
        if (SearchKey(32, key) && reborn[i].has_value() && reborn[i].value().getLive() > 0){
            reborn[i].value().getLive() -= 1;
            game.ecs.removeComponent<Sprite_Animation>(i);
            game.ecs.emplaceComp(playerEntity, Controllable());
            game.ecs.emplaceComp(playerEntity, Positions(100, 100));
            game.ecs.emplaceComp(playerEntity, Drawable("sprites/r-typesheet1.gif", jgo::Rectangle{202, 0, 30, 18}, std::vector<float>{1.5, 1.5}));
            game.ecs.emplaceComp(playerEntity, Hitable(100, 40));
            game.ecs.emplaceComp(playerEntity, Life(30));
            game.ecs.emplaceComp(playerEntity, Type(CONTRO));
            game.ecs.emplaceComp(playerEntity, Shoot(0.5, RIGHT, 20, 2));
            game.ecs.emplaceComp(playerEntity, Invincible());
            game.ecs.emplaceComp(playerEntity, InvincibleTime(time, 2));
            game.ecs.emplaceComp(playerEntity, Explosion("sprites/r-typesheet1.gif", 4, -37, 0.2, 10, jgo::Rectangle{180, 300, 40, 40}, std::vector<float>{1.5, 1.5}));
            Game::CreateBoostModule(game, playerEntity);
            for (std::size_t a = 0; a < mess.size(); a++)
            {
                if (mess[a].has_value())
                    game.ecs.removeComponent<Message>(a);
            }
        }
    }
};
