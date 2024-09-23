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
bool HitSystem::compareHitable(std::map<std::size_t, Hitable*> &list, Hitable &me, Positions &m, SparseArray<Positions> &pos, std::size_t ind)
{
    std::size_t i = 0;
    bool res = false;

    for (auto it = list.begin(); it != list.end(); it++) {
        if (i != ind && (me.isHit(*(it->second), pos[it->first].value(), m))) {
            return true;
        }
        i++;
    }
    return res;
}

/**
 * @brief The Hitable System
 * 
 * @param r The Registry
 */
void HitSystem::system(Register &r, std::vector<sf::Texture> &texture)
{
    std::size_t nbr = 0;
    auto &hit = r.getComp<Hitable>();
    auto &pos = r.getComp<Positions>();
    std::map<std::size_t, Hitable *> list;

    for (std::size_t i = 0; i < hit.size(); i++) {
        if (hit[i].has_value() && pos[i].has_value())
            list.insert(std::make_pair(i, &hit[i].value()));
    }
    if (list.size() == 0 || list.size() == 1)
        return;
    for (auto it = list.begin(); it != list.end(); it++) {
        if (HitSystem::compareHitable(list, *(it->second), pos[it->first].value(), pos, nbr)) {
            it->second->Whenhit(it->first, r, texture);
        }    
        nbr++;
    }
}