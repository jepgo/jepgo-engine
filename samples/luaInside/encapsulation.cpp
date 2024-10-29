#include <iostream>
#include <string>
#include "jeplua/Lua.hpp"

int cfunc(lua_State *l)
{
    lua::State L(l);
    L.dostring("print(42)");
}

int foo_tostring(lua_State *l)
{
    lua::State L(l);
    L.push("zizi");
    return 1;
}

int main(void)
{
    lua::State L("/home/pol/Documents/tek3/cpp/rtype/build/sharedlua");
   
    L.dostring("print(84)");

    L.push(cfunc);
    L.pcall();
    
    L.push(static_cast<lua::userdata>(nullptr));
    L.newTable();
    L.push(foo_tostring);
    L.setField("__tostring");
    L.setMetatable();

    int r = L.ref();
    L.unref(r);

    return 0;
}
