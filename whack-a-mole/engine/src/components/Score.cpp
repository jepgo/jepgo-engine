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

void Components::Score::setScore(std::size_t const &score)
{
    _score = score;
}

std::size_t const &Components::Score::getScore() const
{
    return _score;
}


void Components::Score::setPos(Positions &&pos)
{
    _pos = std::move(pos);
}

Components::Positions const &Components::Score::getPosition() const
{
    return _pos;
}
