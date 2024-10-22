/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Random
*/

#pragma once

#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <limits>

class Random {
    public:
        inline Random() {
            std::time_t t = std::time(nullptr);

            if (t == -1)
                throw std::runtime_error("std::time failed.");
            std::srand(t);
        }

        template <typename T>
        T getBetween(T const &lo, T const &hi) const {
            return (std::rand() % (hi - lo)) + lo;
        }
};
