/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Utils
*/

#pragma once

#include <utility>

namespace jgo {

    template <typename T>
    concept Comparable = requires(T a, T b) {
        a < b;
    };

    template <Comparable T>
    T const &max(T const &a, T const &b) {
        return (a < b) ? b : a;
    }

    template <Comparable T>
    T const &min(T const &a, T const &b) {
        return (a < b) ? a : b;
    }
}

