/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** GameLvlSystem
*/

#include "jepengine/Client.hpp"
#include "jepmaker/components/Game.hpp"
#include "jepmod/exported.hpp"
#include "jepmaker/components/GameLvl.hpp"

exported(void) jepgoSystem(jgo::Game &game, float &time)
{
    auto &lvl = game.ecs.getComp<GameLvl>();

    for (std::size_t i = 0; i < lvl.size(); i++)
    {
        if (lvl[i].has_value()) {
            auto currentLevel = lvl[i].value()._gameLvl;
            auto &levels = lvl[i].value()._levels;
            if (levels.find(currentLevel) != levels.end()) {
                levels[currentLevel]->launch(game, time);
            }
        }
    }
}