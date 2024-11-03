/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Level1
*/

#pragma once

#ifndef LEVEL1_HPP_
    #define LEVEL1_HPP_

    #include "ILevels.hpp"

namespace jgo {
    class Game;
}

class Level1 : public jgo::ILevels {
    public:
        Level1() {};
        ~Level1() {};
        void launch(jgo::Game &game, float &time);
        
        private:
            float _reset;
};


#endif /* !LEVEL1_HPP_ */
