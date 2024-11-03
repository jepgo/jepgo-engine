/*
** EPITECH PROJECT, 2024
** whack-a-mole
** File description:
** Score
*/

#include "Score.hpp"

void Components::Score::setTitle(std::string const &title)
{
    _title = title;
}

std::string const &Components::Score::getTitle() const
{
    return _title;
}

void Components::Score::setScore(long int const &score)
{
    _score = score;
}

long int const &Components::Score::getScore() const
{
    return _score;
}


void Components::Score::setPos(Position2D &&pos)
{
    _pos = std::move(pos);
}

Components::Position2D const &Components::Score::getPosition() const
{
    return _pos;
}
