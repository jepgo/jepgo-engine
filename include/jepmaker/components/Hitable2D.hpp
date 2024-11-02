/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Hitable2D
*/

#pragma once
#include <optional>
#include "jepmaker/components/Position.hpp"
#include "jepmaker/components/EnumDirection.hpp"

class Hitable
{
public:
    /**
     * @brief Construct a new Hitable object
     *
     * @param w the width of the object
     * @param h the hight of the object
     */
    Hitable(int w, int h, std::optional<Position2D> &&pos = std::nullopt) : width(w), height(h), _pos(pos) {};
    ~Hitable() {};
    /**
     * @brief
     *
     * @param entity The entity to be found
     * @param r The Registry
     * @param list The list of all the texture
     */
    int width;
    int height;
    std::optional<Position2D> _pos;
    Direction _dir;
private:
};