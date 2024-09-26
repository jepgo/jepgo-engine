/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Module
*/

#pragma once
#include "Register.hpp"
#include "SparseArray.hpp"
#include "Components.hpp"

class Module {
    public:
        Module(std::map<Direction, int> space, int entity);
        ~Module();
        int getEntityToModule();
        void update(std::optional<Positions> &me, SparseArray<Positions> &pos);
        int _entity;
    private:
        std::map<Direction, int> _space;
};

class ModuleArmor
{
    public:
        ModuleArmor(std::map<Direction, int> space, Life &&life) : _space(space), _life(life) {};
        ~ModuleArmor() {};
        Module attach(int entity) {
            return Module(_space, entity);
        };
        Life &getLife() {
            return _life;
        };
    private:
        std::map<Direction, int> _space;
        Life _life;

};

class ModuleShoot
{
    public:
        ModuleShoot(std::map<Direction, int> space, float fireRate) : _space(space), _fireRate(fireRate) {};
        ~ModuleShoot() {};
        Module attach(int entity) {
            return Module(_space, entity);
        };
        void changeShoot(std::optional<Shoot> &shoot) { 
            if (shoot.has_value()) {
                std::cout << "shoot changed" << std::endl;
                shoot.value()._fireRate = _fireRate;
            } else {
                std::cout << "not change" << std::endl;
                shoot = std::make_optional(Shoot(_fireRate, RIGHT, 10));
            }
        };
    private:
        std::map<Direction, int> _space;
        float _fireRate;

};
