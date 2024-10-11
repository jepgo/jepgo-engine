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

void Draw3DSystem::system(Register &r, float &time, std::vector<Model> &mod)
{
    auto &draw = r.getComp<Model3D>();
    auto &pos = r.getComp<Positions>();
    auto &rot = r.getComp<RotationTime>();

    for (std::size_t i = 0; i < draw.size(); i++) {
        if (draw[i].has_value() && pos[i].has_value()) {
            Model3D &model = draw[i].value();
            Positions &p = pos[i].value();
            if (model.getAngle().has_value() && model.getRotate() == false) {
                Matrix rotation = MatrixRotateY(model.getAngle().value());
                mod[model.getInd()].transform = MatrixMultiply(mod[model.getInd()].transform, rotation);
                model.getRotate() = true;
            }
            if (rot[i].has_value()) {
                RotationTime &tmp = rot[i].value();
                DrawModelEx(mod[model.getInd()], (Vector3){p.x / 2 + model.getWidth(), 600 - p.y / 2 - model.getHeight(), 0}, tmp.getRotation(), tmp.getVal(), {model.getScale(), model.getScale(), model.getScale()}, WHITE);
            } else {
                DrawModel(mod[model.getInd()], (Vector3){p.x / 2 + model.getWidth(), 600 - p.y / 2 - model.getHeight(), 0}, model.getScale(), WHITE);
            }
        }
    }
};
