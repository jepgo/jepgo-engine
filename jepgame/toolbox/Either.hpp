/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Either
*/

#pragma once

#include <variant>
#include <functional>

// en souvenir du glados...
template <typename X, typename Y>
using Either = std::variant<X, Y>;

// en souvenir du glados mais avec des references
template <typename X, typename Y>
using EitherRef = std::variant
    <std::reference_wrapper<X>, std::reference_wrapper<Y>>;
