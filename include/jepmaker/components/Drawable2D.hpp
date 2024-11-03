/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Drawable2D
*/

#pragma once
#include "jepengine/types.hpp"
#include <optional>
#include <array>
#include <vector>
#include <string>
#include <cstring>

class Drawable {
public:
    /**
     * @brief Construct a new Drawable object
     *
     * @param ind The index of the texture in the List of all the texture
     * @param r optional rectangle for The Sprite to Draw
     * @param s A Optional Vector of 2 float for the Scale
     */
    Drawable(std::string path = "", std::optional<jgo::Rectangle> r = std::nullopt, std::vector<float> s = {1, 1})
    : rect(r)
    {
        std::strcpy(index, path.c_str());
        if (r.has_value())
            start = r.value().x;
        scale[0] = s[0];
        scale[1] = s[1];
    };
    ~Drawable() = default;
    std::string getIndex() {
        return std::string(index);
    };
    std::optional<jgo::Rectangle> &getRect() { return rect; };
    std::array<float, 2> getScale() {return {scale[0], scale[1]};}
    int start;

private:
    char index[2048] = {0};
    float scale[2] = { 1, 1 };
    std::optional<jgo::Rectangle> rect;
};