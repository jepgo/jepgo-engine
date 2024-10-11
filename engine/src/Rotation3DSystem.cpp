/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Rotation3DSystem
*/

#include "Rotation3DSystem.hpp"

void Rotation3DSystem::system(Register &r, float time, std::vector<Model> &mod)
{
    auto &model = r.getComp<Model3D>();
    auto &rotate = r.getComp<RotationTime>();

    for (std::size_t i = 0; i < rotate.size(); i++) {
        if (rotate[i].has_value() && model[i].has_value()) {
            RotationTime &rot = rotate[i].value();
            if (time - rot.getTime() >= rot.getReset()) {
                rot.getVal() += 2;
                if (rot.getVal() > rot.getBase() + 360)
                    rot.getVal() = rot.getBase();
            }

        }
    }
}