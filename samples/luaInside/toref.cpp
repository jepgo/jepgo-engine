#include <lua5.4/lua.h>
#include <lua5.4/lualib.h>
#include <lua5.4/lauxlib.h>

int game_tostring(lua_State *L)
{
    lua_pushstring(L, "zizi");
    return 1;
}

class Foo {
    public:
        int n = 0;
};

int main() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    Foo *ptr = (Foo *)lua_newuserdata(L, sizeof(Foo));
    ptr->n = 3;
    lua_close(L);
}