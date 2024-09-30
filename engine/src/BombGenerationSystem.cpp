/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** BombGenerationSystem
*/

#include "BombGenerationSystem.hpp"

static void generatBomb(BombGeneration &bomb, sf::Time &time, Register &r)
{
    if (time.asSeconds() - bomb.getTime() < bomb.getReset())
        return;
    Game::CreateBomb(r, std::move(bomb.getPos()), time.asSeconds(), bomb.getTrac());
}

void BombGenerationSystem::system(Register &r, sf::Time &time)
{
    auto &bomb = r.getComp<BombGeneration>();

    for (std::size_t i = 0; i < bomb.size(); i++)
    {
        if (bomb[i].has_value())
        {
            if (time.asSeconds() - bomb[i].value().getTime() >= bomb[i].value().getReset()) {
                Game::CreateBomb(r, std::move(bomb[i].value().getPos()), time.asSeconds(), bomb[i].value().getTrac());
                bomb[i].value().getTime() = time.asSeconds();
            }
        }
    }
}