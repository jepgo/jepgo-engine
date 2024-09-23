/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** HitSystem
*/

#include "HitSystem.hpp"

HitSystem::HitSystem()
{
}

HitSystem::~HitSystem()
{
}

/**
 * @brief The Hitable Compare
 * 
 * @param list List of Hitable
 * @param me The current who's hit
 * @param where The second who's hit
 * @param m My Position
 * @param him The Position of the other who are hit
 * @return true 
 * @return false 
 */
bool HitSystem::compareHitable(std::map<std::size_t, Hitable*> &list, std::map<size_t, Hitable*>::iterator &me, std::map<size_t, Hitable*>::iterator &where, Positions &m, Positions &him, std::vector<sf::Texture> &texture, Register &re)
{
    for (auto &it = where; it != list.end(); it++) {
        if (me->second->isHit(*(it->second), him, m)) {
            me->second->Whenhit(me->first, re, texture);
            it->second->Whenhit(it->first, re, texture);
        }
    }
    return true;
}

/**
 * @brief The Hitable System
 * 
 * @param r The Registry
 */
void HitSystem::system(Register &r, std::vector<sf::Texture> &texture)
{
    auto &hit = r.getComp<Hitable>();
    auto &pos = r.getComp<Positions>();
    std::map<std::size_t, Hitable *> list;

    for (std::size_t i = 0; i < hit.size(); i++) {
        if (hit[i].has_value() && pos[i].has_value())
            list.insert(std::make_pair(i, &hit[i].value()));
    }
    if (list.size() == 0)
        return;
    for (auto it = list.begin(); std::next(it) != list.end(); it++) {
        auto next = std::next(it);
        if (HitSystem::compareHitable(list, it, next, pos[it->first].value(), pos[next->first].value(), texture, r)) {
            it->second->Whenhit(it->first, r, texture);
        }    
    }
}