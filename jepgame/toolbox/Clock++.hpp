/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Time++
*/

#pragma once

#include <ctime>

class ClockPP {
    public:
        ClockPP(void) noexcept : _clock(std::clock()) {
            return;
        }
        ClockPP(std::clock_t c) noexcept : _clock(c) {
            return;
        }
        constexpr inline explicit operator float(void) const noexcept {
            return (float)_clock / (float)CLOCKS_PER_SEC;
        }
        inline auto operator-(ClockPP const &other) const noexcept -> ClockPP {
            return ClockPP(this->_clock - other._clock);
        }
        inline auto operator+(ClockPP const &other) const noexcept -> ClockPP {
            return ClockPP(this->_clock + other._clock);
        }
        inline auto operator-=(ClockPP const &other) noexcept -> ClockPP & {
            this->_clock -= other._clock;
            return *this;
        }
        inline auto operator+=(ClockPP const &other) noexcept -> ClockPP & {
            this->_clock += other._clock;
            return *this;
        }
        inline auto operator()(void) noexcept(1) -> ClockPP & {
            this->_clock = std::clock();
            return *this;
        }
    private:
        std::clock_t _clock;
};
