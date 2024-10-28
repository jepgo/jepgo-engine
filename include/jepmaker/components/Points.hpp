/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Points
*/

#pragma once
#include <string>

class Points {
    public:
        Points() {
            _point = 0;
        };
        ~Points() {};
        std::size_t _point;
};