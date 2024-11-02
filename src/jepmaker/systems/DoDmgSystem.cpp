/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** DoDmgSystem
*/

#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"
#include "jepmaker/components/Dmg.hpp"
#include "jepmaker/components/DoDmg.hpp"
#include "jepmaker/components/Type.hpp"
#include "jepmaker/components/Hit.hpp"

static Dmg addDmg(std::optional<Dmg> &dmg, std::size_t damage)
{
    if (dmg.has_value() == false)
        return Dmg(damage);
    else
        return Dmg(dmg.value()._dmg + damage);
};

static bool checkValue(jgo::Game &game, std::size_t him, std::size_t me)
{
    auto &doDmg = game.ecs.getComp<DoDmg>();
    auto &type = game.ecs.getComp<Type>();

    if (doDmg[him].has_value() == false)
    {
        return false;
    }
    if (type[me].has_value() == false || type[him].has_value() == false)
        return true;
    if (type[me].value().getType() == NEUTRAL || type[him].value().getType() == NEUTRAL)
        return false;
    if (type[me].value().getType() == MINIBOSS && type[him].value().getType() != BOMB)
        return true;
    if (type[me].value().getType() == CONTRO && type[him].value().getType() != SHIPSHOOT && type[him].value().getType() != MODULE && type[him].value().getType() != MODULE_ARM)
    {
        return true;
    }
    if (type[me].value().getType() == BOMB && type[him].value().getType() != BOMB && type[him].value().getType() != MINIBOSS)
    {
        return true;
    }
    if (type[me].value().getType() == SHIPSHOOT && type[him].value().getType() != CONTRO && type[him].value().getType() != MODULE && type[him].value().getType() != MODULE_ARM && type[him].value().getType() != SHIPSHOOT)
        return true;
    if (type[me].value().getType() == MODULE && type[him].value().getType() != CONTRO && type[him].value().getType() != SHIPSHOOT)
        return true;
    return false;
};

exported(void) jepgoSystem(jgo::Game &game, float time)
{
    auto &hit = game.ecs.getComp<Hit>();
    auto &dmg = game.ecs.getComp<Dmg>();
    auto &doDmg = game.ecs.getComp<DoDmg>();
    auto &type = game.ecs.getComp<Type>();

    for (std::size_t i = 0; i < hit.size(); i++) {
        if (hit[i].has_value() && checkValue(game, hit[i].value().GetEntity(), i)) {
            std::cout << "damageddd" << std::endl;
            game.ecs.emplaceComp<Dmg>(i, addDmg(dmg[i], doDmg[hit[i].value().GetEntity()].value().getDmg()));
        }
        game.ecs.removeComponent<Hit>(i);
    }
};