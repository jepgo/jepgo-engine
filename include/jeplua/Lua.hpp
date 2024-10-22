/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Lua
*/

#pragma once

#include <lua5.4/lua.hpp>
#include <string>
#include <stdexcept>

namespace lua {
    using number = lua_Number;
    using string = std::string;
    using integer = lua_Integer;
    using function = lua_CFunction;
    using boolean = bool;
    using userdata = void *;

    /**
     * The lua state
     */
    class State {
        public:
            inline State(): L(luaL_newstate()) {
                luaL_openlibs(L);
            }
            inline State(lua_State *st): L(st), _isCopy(true) {
                return;
            }
            inline ~State() {
                if (not _isCopy)
                    lua_close(L);
            }

            /* push */
            template <typename T>
            void push(T arg) {
                if constexpr (std::is_same<T, integer>) {
                    return lua_pushinteger(L, arg);
                } else if constexpr (std::is_same<T, string>) {
                    return lua_pushstring(L, arg.c_str());
                } else if constexpr (std::is_same<T, number>) {
                    return lua_pushnumber(L, arg);
                } else if constexpr (std::is_same<T, boolean>) {
                    return lua_pushstring(L, boolean);
                } else if constexpr (std::is_same<T, userdata>) {
                    return lua_pushlightuserdata(L, arg);
                } else if constexpr (std::is_same<T, function>) {
                    return lua_pushcfunction(L, arg);
                } else if constexpr (std::is_same<T, char const *>) {
                    return lua_pushstring(L, arg);
                }
                throw std::runtime_error("invalid type");
            }

            /**
             * Create a new empty table
             */
            void newTable() {
                lua_newtable(L);
            }

            /**
             * Set a table field.
             */
            void setField(std::string const &name, int index = -2) {
                lua_setfield(L, index, name.c_str());
            }

            /**
             * Set the metatable to.
             */
            void setMetatable(int index = -2) {
                lua_setmetatable(L, index);
            }

            /* get */
            template <typename T>
            T get(int arg) {
                if constexpr (std::is_same<T, integer>) {
                    return lua_tointeger(L, arg);
                } else if constexpr (std::is_same<T, string>) {
                    return std::string(lua_tostring(L, arg));
                } else if constexpr (std::is_same<T, number>) {
                    return lua_tonumber(L, arg);
                } else if constexpr (std::is_same<T, boolean>) {
                    return lua_tostring(L, boolean);
                } else if constexpr (std::is_same<T, userdata>) {
                    return lua_touserdata(L, arg);
                } else if constexpr (std::is_same<T, function>) {
                    return lua_tocfunction(L, arg);
                }
                throw std::runtime_error("invalid type");
            }
        private:
            bool _isCopy = false;
            lua_State *L;
    };
}

