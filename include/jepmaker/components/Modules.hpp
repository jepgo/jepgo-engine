/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Module
*/

#pragma once
#include "jepmaker/components/EnumDirection.hpp"
#include "jepmaker/components/Position.hpp"
#include "jepmaker/components/Life.hpp"
#include "jepmaker/components/Shoot.hpp"

class Module {
    public:
        Module(std::map<Direction, int> space, int entity) {};
        ~Module() {};
        int getEntityToModule() {
            return _entity;
        };
        void update(std::optional<Positions> &me, SparseArray<Positions> &pos) {
            if (!(me.has_value()))
                return;
            if (pos[_entity].has_value()) {
                me.value().x = pos[_entity].value().x + _space[LEFT] - _space[RIGHT];
                me.value().y = pos[_entity].value().y - _space[UP] + _space[DOWN];   
            }
        };
        int _entity;
    private:
        std::map<Direction, int> _space;
};

class ModuleArmor
{
    public:
        ModuleArmor(std::map<Direction, int> space, Life &&life, std::size_t dmg) : _space(space), _life(life), _dmg(dmg) {};
        ~ModuleArmor() {};
        Module attach(int entity) {
            return Module(_space, entity);
        };
        Life &getLife() {
            return _life;
        };
        std::size_t &getDmg() {return _dmg;};
    private:
        std::map<Direction, int> _space;
        Life _life;
        std::size_t _dmg;

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
                shoot.value()._fireRate = _fireRate;
            } else {
                shoot = std::make_optional(Shoot(_fireRate, RIGHT, 10, 2));
            }
        };
    private:
        std::map<Direction, int> _space;
        float _fireRate;

};