/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Direction
*/

#pragma once

class Direction {
    public:
        enum Enum {
            Left = 0,
            Right = 1,
        };

        Direction() = default;

        void change() {
            if (dir == Enum::Right)
                dir = Enum::Left;
            else
                dir = Enum::Right;
        }

        Enum dir = Enum::Right;

};
