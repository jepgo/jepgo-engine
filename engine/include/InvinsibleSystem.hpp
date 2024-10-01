/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** InvinsibleSystem
*/

#pragma once
#include "Register.hpp"

class InvinsibleSystem {
    public:
        static bool check_time(InvincibleTime &inv, float time){
            if (time - inv._time < inv._reset)
                return false;
            return true;
        };
        static void system(Register &r, float time){
            auto &inv = r.getComp<InvincibleTime>();

            for (std::size_t i = 0; i < inv.size(); i++) {
                if (inv[i].has_value() && check_time(inv[i].value(), time)) {
                    r.removeComponent<Invincible>(i);
                    r.removeComponent<InvincibleTime>(i);
                }
            }
        };
    protected:
    private:
};
