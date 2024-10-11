/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Rotation3D
*/

#pragma once

class RotationTime {
    public:
        RotationTime(Vector3 rotation, float base, float time, float reset) : _rotation(rotation), _base(base), _val(base), _time(time), _reset(reset) {};
        ~RotationTime() {};
        Vector3 &getRotation() {return _rotation;};
        float &getBase() {return _base;};
        float &getVal() {return _val;};
        float &getTime() {return _time;};
        float &getReset() {return _reset;};
    private:
        Vector3 _rotation;
        float _base;
        float _val;
        float _time;
        float _reset;
};

class Rotation3D {
    public:
        Rotation3D(float rotation, float time, float reset) : _rotation(rotation), _time(time), _reset(reset) {};
        ~Rotation3D() {};
        float &getRotation() {return _rotation;};
        float &getTime(){return _time;};
        float &getReset() {return _reset;};
    private:
        float _rotation;
        float _time;
        float _reset;
};
