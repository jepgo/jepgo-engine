/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Game
*/

#include <iostream>
#include "jepmod/DLLoader.hpp"
#include "jepmod/Clock++.hpp"
#include "jepmod/EasyLife.hpp"
#include "jepengine/Game.hpp"

jgo::Game::Game(int ac, char const *const av[]): argv(av, av + ac)
{
    return;
}

auto jgo::Game::compile(void) -> bool
{
    return true;
}

auto jgo::Game::loadGraphic(std::string const &lib) -> void
{
    std::string realLib = jmod::EasyLife()/"jepgo.graphic." + lib;
    jmod::DLLoader loader(realLib);

    _graphicLib = loader.getFunc<std::unique_ptr<jgo::IGraphic>>("createLibrary")();
}

auto jgo::Game::loadLevel(std::string const &lib) -> void
{
    std::string realLib = jmod::EasyLife()/"jepgo.levels." + lib;
    std::cout << "Loading level " << lib << std::endl;
    jmod::DLLoader loader(realLib);

    /* _levels[lib] =  */loader.getFunc<std::unique_ptr<jgo::ILevels>>("createLevel")();
    std::cout << "Level " << lib << " loaded" << std::endl;
}

auto jgo::Game::getTime(void) -> double
{
    return _clock().get();
}

auto jgo::Game::callSystems(void) -> void
{
    for (auto &e : _systems)
        if (e.second) {
            auto f = e.second->first.get()->getFunc<int, jgo::Game &, float &>("jepgoSystem");
            f(*this, e.second->second);
        }
}
