/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** DeathSystem
*/

#include "DeathSystem.hpp"

void DeathSystem::ControlDeath(Register &r, std::size_t entity)
{
    //r.removeComponent<Drawable>(entity);
    //r.removeComponent<Positions>(entity);
    r.removeComponent<Model3D>(entity);
    r.removeComponent<Controllable>(entity);
    r.removeComponent<Hitable>(entity);
    r.removeComponent<Shoot>(entity);
    r.creatEntity();
    r.emplace_comp(r.entity_nbr, Message("You are dead...", Positions(200, 200), 50, RED));
}

void DeathSystem::ModulesDeath(Register &r, std::size_t entity)
{
    //r.removeComponent<Drawable>(entity);
    //r.removeComponent<Positions>(entity);
    r.removeComponent<Model3D>(entity);
    r.removeComponent<Controllable>(entity);
    r.removeComponent<Hitable>(entity);
}

void DeathSystem::death(Register &r, std::size_t entity)
{
    auto &type = r.getComp<Type>();

    if (type[entity].has_value() == false)
        return;
    if (type[entity].value().getType() == CONTRO)
        return ControlDeath(r, entity);
    if (type[entity].value().getType() == MODULE || type[entity].value().getType() == MODULE_ARM)
        return ModulesDeath(r, entity);
}

void DeathSystem::system(Register &r, std::size_t playerEntity)
{
    auto &life = r.getComp<Life>();
    auto &enemy = r.getComp<Enemy>();
    auto &death = r.getComp<Death>();
    auto &exp = r.getComp<Exp>();
    auto &points = r.getComp<Points>();

    for (std::size_t i = 0; i < life.size(); i++)
    {
        if (life[i].has_value() && life[i].value()._life <= 0)
        {
            DeathSystem::death(r, i);
            if (enemy[i].has_value() && death[i].has_value())
            {
                exp[playerEntity].value()._exp += enemy[i].value()._exp;
                points[playerEntity].value()._point += enemy[i].value()._point;
            }
            r.removeComponent<Death>(i);
        }
    }
}