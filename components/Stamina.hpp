/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** StaminaComponent
*/

#pragma once

class StaminaComponent {
    public:
        StaminaComponent(int n) noexcept : _n(n) {
            return;
        };
        inline auto getStamina(void) const noexcept -> int {
            return _n;
        }
    protected:
    private:
        int _n;
};
