/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Explosion
*/

#pragma once
#include "jepengine/Client.hpp"
#include <optional>
#include <vector>

class Explosion
{
public:
    /**
     * @brief Construct a new Explosion object
     *
     * @param ind The index for the list of Texture
     * @param status The number of the status of the New Sprite
     * @param val The value to be increase for the left Sprite rectangle
     * @param t The time fo the Sprite to be refresh
     * @param r The optional rectangle
     * @param s The optional scale of the Sprite
     */
    Explosion(std::size_t ind, int status, int val, double t, std::size_t dmg, std::optional<jgo::Rectangle> r = std::nullopt, std::vector<float> s = {})
    : _dmg(dmg), index(ind), rect(r), stat(status), time(t), value(val) {
        if (s.empty())
            return;
        scale[0] = s[0];
        scale[1] = s[1];
        return;
    }
    ~Explosion() {};
    std::size_t _dmg;
    std::size_t index;
    std::optional<jgo::Rectangle> rect;
    float scale[2] = {1, 1};
    int stat;
    double time;
    int value;
private:
};