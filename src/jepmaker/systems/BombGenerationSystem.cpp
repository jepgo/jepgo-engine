/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** BombGenerationSystem
*/

#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"
#include "jepmaker/components/BombGeneration.hpp"
#include "jepmaker/components/Game.hpp"

static void generatBomb(BombGeneration &bomb, float time, jgo::Game &game)
{
    if (time - bomb.getTime() < bomb.getReset())
        return;
    Game::CreateBomb(game, std::move(bomb.getPos()), time, bomb.getTrac());
}

exported(void) jepgoSystem(jgo::Game &game, float &time)
{
    auto &bomb = game.ecs.getComp<BombGeneration>();

    for (std::size_t i = 0; i < bomb.size(); i++)
    {
        if (bomb[i].has_value())
        {
            if (time - bomb[i].value().getTime() >= bomb[i].value().getReset()) {
                Game::CreateBomb(game, std::move(bomb[i].value().getPos()), game.getTime(), bomb[i].value().getTrac());
                bomb[i].value().getTime() = game.getTime();
            }
        }
    }
}