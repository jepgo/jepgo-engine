#pragma once

#include "lua.hpp"
#include <string>
#include <stdexcept>

namespace lua {
    using number = lua_Number;
    using string = std::string;
    using integer = lua_Integer;
    using function = lua_CFunction;
    using boolean = bool;
    using userdata = void *;

    class State {
        public:
            inline State(): L(luaL_newstate()) {
                luaL_openlibs(L);
            }
            inline State(lua_State *st): L(st), _isCopy(true) {
                return;
            }
            inline ~State() {
                if (!_isCopy)
                    lua_close(L);
            }

            /* push */
            template <typename T>
            void push(T arg) {
                if constexpr (std::is_same<T, integer>()) {
                    lua_pushinteger(L, arg);
                } else if constexpr (std::is_same<T, string>()) {
                    lua_pushstring(L, arg.c_str());
                } else if constexpr (std::is_same<T, number>()) {
                    lua_pushnumber(L, arg);
                } else if constexpr (std::is_same<T, boolean>()) {
                    lua_pushboolean(L, arg);
                } else if constexpr (std::is_same<T, userdata>()) {
                    lua_pushlightuserdata(L, arg);
                } else if constexpr (std::is_same<T, function>()) {
                    lua_pushcfunction(L, arg);
                } else if constexpr (std::is_same<T, const char*>()) {
                    lua_pushstring(L, arg);
                } else {
                    throw std::runtime_error("invalid type");
                }
            }

            /* Create a new empty table */
            void newTable() {
                lua_newtable(L);
            }

            /* Set a table field */
            void setField(std::string const &name, int index = -2) {
                lua_setfield(L, index, name.c_str());
            }

            /* Set the metatable */
            void setMetatable(int index = -2) {
                lua_setmetatable(L, index);
            }

            /* Execute a string */
            void execute(std::string const &str) {
                luaL_dostring(L, str.c_str());
            }

            /* get */
            template <typename T>
            T get(int arg) {
                if constexpr (std::is_same<T, integer>()) {
                    return lua_tointeger(L, arg);
                } else if constexpr (std::is_same<T, string>()) {
                    return std::string(lua_tostring(L, arg));
                } else if constexpr (std::is_same<T, number>()) {
                    return lua_tonumber(L, arg);
                } else if constexpr (std::is_same<T, boolean>()) {
                    return lua_toboolean(L, arg);
                } else if constexpr (std::is_same<T, userdata>()) {
                    return lua_touserdata(L, arg);
                } else if constexpr (std::is_same<T, function>()) {
                    return lua_tocfunction(L, arg);
                } else {
                    throw std::runtime_error("invalid type");
                }
            }

        private:
            bool _isCopy = false;
            lua_State *L;
    };
}
