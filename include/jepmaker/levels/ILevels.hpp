/*
** EPITECH PROJECT, 2024
** R-Type [WSL : Fedora]
** File description:
** ILevels
*/

#pragma once

#ifndef ILEVELS_HPP_
    #define ILEVELS_HPP_
    
namespace jgo {

    class Game;

    class ILevels {
    public:
        virtual ~ILevels() = default;
        virtual void launch(jgo::Game &game, float time) = 0;

    };

}

#endif /* !ILEVELS_HPP_ */