/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** DetachModulesSystem
*/

#include "DetachModulesSystem.hpp"

static void SetModuleArm(Register &r, std::size_t entity, float time)
{
    auto &pos = r.getComp<Positions>();
    pos[entity].value().x += 10;
    r.removeComponent<Module>(entity);
    //r.removeComponent<Life>(entity);
    r.removeComponent<Move>(entity);
    r.emplace_comp(entity, MoveTo(Positions(pos[entity].value().x + 100, pos[entity].value().y), 2));
    r.emplace_comp(entity, Drawable(2, Rectangle{173, 345, 32, 32}, std::vector<float>{1.5, 1.5}));
    r.emplace_comp(entity, Sprite_Animation(4, 32, 0.2));
    r.emplace_comp(entity, Hitable(64, 64));
    r.emplace_comp(entity, ModuleArmor({{LEFT, 120}, {UP, 0}, {RIGHT, 0}, {DOWN, 0}}, Life(1000), 10));
    r.emplace_comp(entity, AutoShoot(Shoot(0.3, RIGHT, 10, 0), Type(SHIPSHOOT), time, 0.7));
    r.emplace_comp(entity, DoDmg(30));
    r.emplace_comp(entity, Explosion(1, 4, -37, 0.2, 10, CONTRO, Rectangle{180, 300, 40, 40}, std::vector<float>{1.5, 1.5}));
}

void DetachModulesSystem::system(Register &r, float time, int key)
{
    auto &type = r.getComp<Type>();

    for (std::size_t i = 0; i < type.size(); i++) {
        if (type[i].has_value() && type[i].value().getType() == MODULE_ARM && key == KeyboardKey::KEY_SPACE) {
            SetModuleArm(r, i, time);
        }
    }
}