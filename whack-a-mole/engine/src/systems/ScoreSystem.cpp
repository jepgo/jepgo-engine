/*
** EPITECH PROJECT, 2024
** whack-a-mole
** File description:
** ScoreSystem
*/

#include <raylib.h>
#include "Score.hpp"
#include "ScoreSystem.hpp"

void Systems::ScoreSystem::system(Register &r)
{
    auto &score = r.getComp<Components::Score>();

    for (std::size_t i = 0; i < score.size(); ++i) {
        if (score[i].has_value()) {
            DrawText(score[i].value().getTitle().c_str(), score[i].value().getPosition().x, score[i].value().getPosition().y, 20, BLACK);
            DrawText(std::to_string(score[i].value().getScore()).c_str(), score[i].value().getPosition().x + 100, score[i].value().getPosition().y, 20, BLACK);
        }
    }
}
