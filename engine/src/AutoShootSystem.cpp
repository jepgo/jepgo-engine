/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** AutoShootSystem
*/

#include "AutoShootSystem.hpp"

static bool checkTime(float time, float _time, float reset)
{
    if (time - _time < reset)
        return false;
    return true;
}

static void CreateShoot(Register &r, float time, std::size_t entity, AutoShoot &shoot)
{
    auto &type = r.getComp<Type>();
    auto &pos = r.getComp<Positions>();

    if (type[entity].has_value() && type[entity].value().getType() == MODULE_ARM && pos[entity].has_value()) {
        Game::CreateShipShoot(r, Positions(pos[entity].value().x + 10, pos[entity].value().y));   
        shoot.getTime() = time;
    }
}

void AutoShootSystem::system(Register &r, float time)
{
    auto &autoshoot = r.getComp<AutoShoot>();

    for (std::size_t i = 0; i < autoshoot.size(); i++) {
        if (autoshoot[i].has_value() && checkTime(time, autoshoot[i].value().getTime(), autoshoot[i].value().getReset())) {
            CreateShoot(r, time, i, autoshoot[i].value());
        }
    }
}