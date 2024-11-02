/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ScoreSystem
*/

#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"
#include "components/Score.hpp"
#include "jepmaker/components/Position.hpp"

exported(void) jepgoSystem(jgo::Game &game, float &t)
{
    auto &score = game.ecs.getComp<Score>();
    auto &pos = game.ecs.getComp<Positions>();

    for (std::size_t i = 0; i < score.size(); i++) {
        if (score[i].has_value() && pos[i].has_value()) {
            std::string txt = score[i].value().getTitle() + ": " + std::to_string(score[i].value().getScore());
            std::cout << txt << std::endl;
            game.getGraphicLib()->drawText(txt, jgo::Rectangle(pos[i].value().x, pos[i].value().y, -1, -1), 0xa97a1c00, "", 20);
        }
    }
}
