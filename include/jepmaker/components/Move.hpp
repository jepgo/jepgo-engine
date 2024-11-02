/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Move
*/

#pragma once
#include "jepmaker/components/Position.hpp"

class Move {
public:
    /**
     * @brief Construct a new Move object
     *
     * @param pos The Nex Position of the Object
     */
    Move(Position2D const &pos) : _pos(pos) {};
    inline auto getPos() const noexcept -> Position2D const &
    {
        return _pos;
    }

private:
    Position2D _pos;
};