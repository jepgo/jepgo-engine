/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Time++
*/

#pragma once

#include <ctime>
#include <chrono>

namespace jmod {
    class ClockPP {
        public:
            ClockPP(void) noexcept : _start(std::chrono::high_resolution_clock::now()), _point(_start) {
                return;
            }
            // ClockPP(std::clock_t c) noexcept : _clock(c) {
            //     return;
            // }
            // inline explicit operator float(void) const noexcept {
            //     return static_cast<float>(std::chrono::steady_clock::to_time_t(this->_clock));
            // }
            inline double get() {
                return std::chrono::duration<double>(_point - _start).count();
            }
            // inline ClockPP operator-(ClockPP const &other) const noexcept {
            //     return ClockPP(this->_clock - other._clock);
            // }
            // inline ClockPP operator+(ClockPP const &other) const noexcept {
            //     return ClockPP(this->_clock + other._clock);
            // }
            // inline ClockPP &operator-=(ClockPP const &other) noexcept {
            //     this->_clock -= other._clock;
            //     return *this;
            // }
            // inline ClockPP &operator+=(ClockPP const &other) noexcept {
            //     this->_clock += other._clock;
            //     return *this;
            // }
            inline ClockPP &operator()(void) noexcept {
                this->_point = std::chrono::high_resolution_clock::now();
                return *this;
            }
        private:
            std::chrono::high_resolution_clock::time_point _start;
            std::chrono::high_resolution_clock::time_point _point;
    };
}
