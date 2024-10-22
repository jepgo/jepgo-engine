/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Time++
*/

#pragma once

#include <ctime>

namespace jmod {
    class ClockPP {
        public:
            ClockPP(void) noexcept : _clock(std::clock()) {
                return;
            }
            ClockPP(std::clock_t c) noexcept : _clock(c) {
                return;
            }
            constexpr inline explicit operator float(void) const noexcept {
                return static_cast<float>(_clock) /
                    static_cast<float>(CLOCKS_PER_SEC);
            }
            inline ClockPP operator-(ClockPP const &other) const noexcept {
                return ClockPP(this->_clock - other._clock);
            }
            inline ClockPP operator+(ClockPP const &other) const noexcept {
                return ClockPP(this->_clock + other._clock);
            }
            inline ClockPP &operator-=(ClockPP const &other) noexcept {
                this->_clock -= other._clock;
                return *this;
            }
            inline ClockPP &operator+=(ClockPP const &other) noexcept {
                this->_clock += other._clock;
                return *this;
            }
            inline ClockPP &operator()(void) noexcept {
                this->_clock = std::clock();
                return *this;
            }
        private:
            std::clock_t _clock;
    };
}
