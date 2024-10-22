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

auto jgo::Game::loadNetwork(std::string const &lib) -> void
{
    std::string realLib = jmod::EasyLife(argv[0])/"jepgo.network." + lib;

    _libs["network"] = jmod::DLLoader(realLib);
}

auto jgo::Game::loadGraphic(std::string const &lib) -> void
{
    std::string realLib = jmod::EasyLife(argv[0])/"jepgo.graphic." + lib;

    _libs["graphic"] = jmod::DLLoader(realLib);
}

template <typename T>
auto jgo::Game::useComponent(std::string const &str) -> bool
{
    
}

auto jgo::Game::getTime(void) -> float
{
    return static_cast<float>(_clock());
}
