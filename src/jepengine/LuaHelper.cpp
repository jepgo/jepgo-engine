/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** LuaHelper
*/

#include "jeplua/Lua.hpp"

std::string lua::State::PATH = "";

int game_tostring(lua_State *l)
{
    lua::State L(l);
    L.push("zizi");
    return 1;
}

jgo::LuaHelper::LuaHelper(std::string const &where): State(where) {
    push(static_cast<lua::userdata>(nullptr));
    newTable();
    push(game_tostring);
    setField("__tostring");
    setMetatable();
    _gameIndex = ref();
    // pop();
}

jgo::LuaHelper::~LuaHelper() {
    for (int const &n : _refs)
        unref(n);
    unref(_gameIndex);
}

void jgo::LuaHelper::callAllSystems()
{
    for (int const &r : _refs) {
        rawgeti(r);
        rawgeti(_gameIndex);
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