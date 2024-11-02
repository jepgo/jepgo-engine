/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** HitSystem
*/

#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"
#include "jepmaker/components/Hitable2D.hpp"
#include "jepmaker/components/SpriteAnimation.hpp"
#include "jepmaker/components/Explosion.hpp"
#include "jepmaker/components/Drawable2D.hpp"
#include "jepmaker/components/Move.hpp"
#include "jepmaker/components/Hit.hpp"

static void explose(jgo::Game &game, std::size_t entity, Explosion &exp)
{
    if (exp.rect.has_value()) {
        game.ecs.emplaceComp(entity, Drawable(exp.index, std::move(exp.rect.value()), std::vector<float>{exp.scale[0], exp.scale[1]}));
        game.ecs.emplaceComp(entity, Sprite_Animation(exp.stat, exp.value, exp.time, true));
    }
    else if (exp.rect.has_value()) {
        game.ecs.emplaceComp(entity, Drawable(exp.index, std::move(exp.rect)));
        game.ecs.emplaceComp(entity, Sprite_Animation(exp.stat, exp.value, exp.time, true));
    } else
        game.ecs.emplaceComp(entity, Drawable(exp.index));

    game.ecs.removeComponent<Hitable>(entity);
    game.ecs.removeComponent<Move>(entity);
}

static void Whenhit(std::size_t entity, jgo::Game &game)
{
    auto &explo = game.ecs.getComp<Explosion>();

    if (!explo[entity].has_value())
        return;
    explose(game, entity, explo[entity].value());
}

/**
     * @brief Methode to know if 2 hitable object touch each others
     *
     * @param hit the other Hitable object
     * @param him The position of the second Hitable
     * @param me The Position of this Hitable
     * @return true
     * @return false
     */
static bool isHit(Hitable &hit, Position2D &him, Position2D &me, std::optional<Position2D> &himDecal, std::optional<Position2D> &_pos, int &width, int &height)
    {
        if (_pos.has_value() && himDecal.has_value()) {
            Position2D &tmp = _pos.value();
            Position2D &tmp2 = himDecal.value();
            return !(me.x + width + tmp.x < him.x + tmp2.x || me.x + tmp.x > him.x + hit.width + tmp2.x || me.y + height + tmp.y < him.y + tmp2.y || me.y + tmp.y > him.y + hit.height + tmp2.y);
        }
        else if (himDecal.has_value()) {
            Position2D &tmp2 = himDecal.value();
            return !(me.x + width < him.x + tmp2.x || me.x > him.x + hit.width + tmp2.x || me.y + height < him.y + tmp2.y || me.y > him.y + hit.height + tmp2.y);
        }
        else if (_pos.has_value()) {
            Position2D &tmp = _pos.value();
            return !(me.x + width + tmp.x < him.x || me.x + tmp.x > him.x + hit.width || me.y + height + tmp.y < him.y || me.y + tmp.y > him.y + hit.height);
        }
         return !(me.x + width < him.x || me.x > him.x + hit.width || me.y + height < him.y || me.y > him.y + hit.height);
    };

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
int compareHitable(std::map<std::size_t, Hitable*> &list, Hitable &me, Position2D &m, SparseArray<Position2D> &pos, int ind)
{
    int i = -1;

    for (auto it = list.begin(); it != list.end(); it++) {
        i++;
        if (i != ind && (isHit(*(it->second), pos[it->first].value(), m, (it->second)->_pos, me._pos, me.width, me.height))) {
            return it->first;
        }
    }
    return -1;
}

/**
 * @brief The Hitable System
 * 
 * @param r The Registry
 */
exported(void) jepgoSystem(jgo::Game &game, float time)
{
    int tmp = 0;
    std::size_t nbr = 0;
    auto &hit = game.ecs.getComp<Hitable>();
    auto &pos = game.ecs.getComp<Position2D>();
    auto &h = game.ecs.getComp<Hit>();
    std::map<std::size_t, Hitable *> list;

    for (std::size_t i = 0; i < hit.size(); i++) {
        if (hit[i].has_value() && pos[i].has_value() && !(h[i].has_value())) {
            list.insert(std::make_pair(i, &hit[i].value()));
        }
    }
    if (list.size() == 0 || list.size() == 1)
        return;
    for (auto it = list.begin(); it != list.end(); it++) {
        tmp = compareHitable(list, *(it->second), pos[it->first].value(), pos, nbr);
        if (tmp != -1) {
            //if (type[it->first].has_value() && type[it->first].value().getType() == SHIPSHOOT && type[tmp].value().getType() == MINIBOSS)
            game.ecs.emplaceComp(it->first, Hit(tmp));
        }    
        nbr++;
    }
}