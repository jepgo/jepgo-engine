#include <lua5.4/lua.h>
#include <lua5.4/lualib.h>
#include <lua5.4/lauxlib.h>

int game_tostring(lua_State *L)
{
    lua_pushstring(L, "zizi");
    return 1;
}

int main() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    // Create metatable
    luaL_newmetatable(L, "MyDataMeta");

    // Set __tostring method
    lua_pushcfunction(L, game_tostring);
    lua_setfield(L, -2, "__tostring");

    // Create userdata
    lua_pushlightuserdata(L, nullptr);

    // Set the metatable for the userdata
    lua_setmetatable(L, -2);

    // Store userdata in the registry
    int userdata_ref = luaL_ref(L, LUA_REGISTRYINDEX);

    luaL_unref(L, LUA_REGISTRYINDEX, userdata_ref);
    lua_close(L);
}