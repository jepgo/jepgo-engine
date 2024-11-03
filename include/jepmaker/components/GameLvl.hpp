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
        GameLvl(std::size_t gameLvl, std::map<std::size_t, std::shared_ptr<jgo::ILevels>> levels) : _gameLvl(gameLvl), _levels(levels) {};
        ~GameLvl() {};
        std::size_t _gameLvl;
        std::map<std::size_t, std::shared_ptr<jgo::ILevels>> _levels;
};

#endif /* !GAMELVL_HPP_ */
