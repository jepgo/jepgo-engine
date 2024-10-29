/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** LuaHelper
*/

#include "jeplua/Lua.hpp"

void jgo::LuaHelper::callAllSystems()
{
    for (int const &r : _refs) {
        rawgeti(r);
        push(static_cast<lua::integer>(42));
        pcall(1, 0);
    }
}

void jgo::LuaHelper::useSystem(std::string const &filename)
{
    if (my_luadofile(this, (filename + ".lua").c_str()) != LUA_OK) {
        pop();
        throw std::runtime_error(get<char const *>(-1));
    }
    pushvalue();
    _refs.push_back(ref());
    pop();
}