/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** GameLvlSystem
*/

#include "GameLvlSystem.hpp"
#include "TestGame.hpp"

GameLvlSystem::GameLvlSystem(float time, float reset) : _time(time), _reset(reset)
{

}

GameLvlSystem::~GameLvlSystem()
{

}

void GameLvlSystem::system(Register &r, float time, std::vector<Sound> &sounds)
{
    auto &lvl = r.getComp<GameLvl>();

    for (std::size_t i = 0; i < lvl.size(); i++) {
        if (lvl[i].has_value()) {
            if (lvl[i].value().GetLvl() == 1)
                return TestGame::Stages();
        }
    }
}