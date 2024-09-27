/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** AddDmgSystem
*/

#pragma once
#include "Components.hpp"
#include "Register.hpp"

class AddDmgSystem {
    public:
        AddDmgSystem(float reset) : _reset(reset) {_time = 0;};
        ~AddDmgSystem() {};
        static Dmg addDmg(std::optional<Dmg> &dmg, std::size_t damage) {
            if (dmg.has_value() == false)
                return Dmg(damage);
            else
                return Dmg(dmg.value()._dmg + damage);
        };
        static bool checkValue(Register &r, std::size_t him, std::size_t me){
            auto &doDmg = r.getComp<DoDmg>();
            auto &type = r.getComp<Type>();

            if (doDmg[him].has_value() == false)
                return false;
            if (type[me].has_value() == false || type[him].has_value() == false)
                return true;
            if (type[me].value().getType() == MINIBOSS)
                return true;
            if (type[me].value().getType() == CONTRO && type[him].value().getType() != SHIPSHOOT && type[him].value().getType() != MODULE)
                return true;
            if (type[me].value().getType() == BOMB && type[him].value().getType() != BOMB)
                return true;
            if (type[me].value().getType() == SHIPSHOOT && type[him].value().getType() != CONTRO && type[him].value().getType() != MODULE)    
                return true;
            if (type[me].value().getType() == MODULE && type[him].value().getType() != CONTRO && type[him].value().getType() != SHIPSHOOT)
                return true;
            return false;     
        };
        void system(Register &r, sf::Time &time){
            if (time.asSeconds() - _time < _reset)
                return;
            auto &hit = r.getComp<Hit>();
            auto &dmg = r.getComp<Dmg>();
            auto &doDmg = r.getComp<DoDmg>();
            auto &type = r.getComp<Type>();

            for (std::size_t i = 0; i < hit.size(); i++) {
                if (hit[i].has_value() && checkValue(r, hit[i].value().GetEntity(), i)) {
                    std::cout << "take dmg" << std::endl;
                    r.emplace_comp<Dmg>(i ,addDmg(dmg[i], doDmg[hit[i].value().GetEntity()].value().getDmg()));
                }
                r.removeComponent<Hit>(i);
            }
        };
    private:
        float _reset;
        float _time;
};
