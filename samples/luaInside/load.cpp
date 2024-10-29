#include <lua5.4/lua.hpp>
#include <stdio.h>

#define my_luadofile(L, str) ( \
    luaL_loadfilex(L, str, nullptr) \
    || \
    lua_pcallk(L, 0, LUA_MULTRET, 0, 0, nullptr) \
)

int main(int argc, char const *argv[])
{
    lua_State *L = luaL_newstate();
    
    luaL_openlibs(L);
    if (my_luadofile(L, "caca.lua") != LUA_OK) {
        dprintf(2, "error -> %s\n", lua_tolstring(L, -1, nullptr));
        lua_close(L);
        return 1;
    }
    lua_pushnumber(L, 5);
    if (lua_pcall(L, 1, 1, 0) != LUA_OK) {
        dprintf(2, "error: %s\n", lua_tolstring(L, -1, nullptr));
        lua_close(L);
        return 1;
    }
    lua_Number n = lua_tonumberx(L, -1, nullptr);
    printf("res: %f\n", n);
    lua_close(L);
    return 0;
}
