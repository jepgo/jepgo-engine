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

void Draw3DSystem::system(Register &r, float time, std::vector<Model> &mod)
{
    auto &draw = r.getComp<Model3D>();
    auto &pos = r.getComp<Positions>();
    auto &rot = r.getComp<RotationTime>();
    auto &staticRot = r.getComp<Rotation3D>();

    for (std::size_t i = 0; i < draw.size(); i++) {
        if (draw[i].has_value() && pos[i].has_value()) {
            Model3D &model = draw[i].value();
            Positions &p = pos[i].value();

            if (rot[i].has_value()) {
                std::cout << "a" << std::endl;
                RotationTime &tmp = rot[i].value();
                DrawModelEx(mod[model.getInd()], (Vector3){p.x / 2 + model.getWidth(), 600 - p.y / 2 - model.getHeight(), 0}, tmp.getRotation(), tmp.getVal(), {model.getScale(), model.getScale(), model.getScale()}, WHITE);
            } else if (staticRot[i].has_value()) {
                std::cout << "b" << std::endl;
                Rotation3D &tmp = staticRot[i].value();
                DrawModelEx(mod[model.getInd()], (Vector3){p.x / 2 + model.getWidth(), 600 - p.y / 2 - model.getHeight(), 0}, tmp.getRotation(), tmp.getAngle(), {model.getScale(), model.getScale(), model.getScale()}, WHITE); 
            } 
            else {
                std::cout << "c" << std::endl;
                DrawModel(mod[model.getInd()], (Vector3){p.x / 2 + model.getWidth(), 600 - p.y / 2 - model.getHeight(), 0}, model.getScale(), WHITE);
            }
        }
    }
};
