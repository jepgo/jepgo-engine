/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** GameLvl
*/


#ifndef GAMELVL_HPP_
    #define GAMELVL_HPP_

    #include <iostream>
    #include <map>
    #include <memory>
    #include "jepmaker/levels/ILevels.hpp"

class GameLvl {
    public:
        GameLvl(std::size_t gameLvl) : _gameLvl(gameLvl) {};
        ~GameLvl() {};
        std::size_t _gameLvl;
};

#endif /* !GAMELVL_HPP_ */
