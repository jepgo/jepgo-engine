/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Utils
*/

#pragma once

#include <utility>

namespace jgo {

    template <typename X>
    concept Comparable = requires(X a, X b) {
        a < b;
    };

    template <Comparable T>
    constexpr T const &max(T const &a, T const &b) {
        return (a < b) ? b : a;
    }

    template <Comparable T>
    constexpr T const &min(T const &a, T const &b) {
        return (a < b) ? a : b;
    }
}

