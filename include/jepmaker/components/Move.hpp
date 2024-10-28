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
    Move(Positions const &pos) : _pos(pos) {};
    inline auto getPos() const noexcept -> Positions const &
    {
        return _pos;
    }

private:
    Positions _pos;
};