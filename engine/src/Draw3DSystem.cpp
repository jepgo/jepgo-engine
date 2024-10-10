/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Draw3DSystem
*/

#include "Draw3DSystem.hpp"

Draw3DSystem::Draw3DSystem(float time, float reset) : _time(time), _reset(reset)
{
}

Draw3DSystem::~Draw3DSystem()
{
}

void Draw3DSystem::system(Register &r, float &time, Model &mod)
{
    auto &draw = r.getComp<Model3D>();
    auto &pos = r.getComp<Positions>();

    for (std::size_t i = 0; i < draw.size(); i++)
    {
        if (draw[i].has_value() && pos[i].has_value())
        {
            // std::cout << "draw" << std::endl;
            Positions &p = pos[i].value();
            //DrawModel(mod, (Vector3){0, 0, 0}, 0.2, WHITE);
            std::cout << "ship2 = " << p.x << " " << p.y << std::endl;
            DrawModel(mod, (Vector3){p.x / 2 + 50, 600 - p.y / 2 - 10, 0}, 100, WHITE);
        }
    }
};
