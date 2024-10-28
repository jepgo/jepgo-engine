/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Lua
*/

#pragma once

#include <string>
#include <stdexcept>
#include <optional>
#include "jepmod/DLLoader.hpp"
#include "jepmod/EasyLife.hpp"

extern "C" {
    #include "./lua.h"
    #include "./lualib.h"
    #include "./lauxlib.h"
}

#define my_lua_dostring(L, ldr, str) \
    ldr.getFunc<int, lua_State *, char const *>("luaL_loadstring")(L, str) \
    || \
    ldr.getFunc<int, lua_State *, int, int, int, lua_KContext, lua_KFunction>("lua_pcallk")(L, 0, LUA_MULTRET, 0, 0, NULL)

#define my_lua_openlibs(L, ldr) \
    ldr.getFunc<void, lua_State *, int, int>("luaL_openselectedlibs")(L, (~0), 0)

namespace lua {
    using number = lua_Number;
    using string = std::string;
    using integer = lua_Integer;
    using function = lua_CFunction;
    using boolean = bool;
    using userdata = void *;

    class State {
        public:
            inline State(std::string const &str)
            : _loader(str) {
                L = _loader.getFunc<lua_State *>("luaL_newstate")();
                my_lua_openlibs(L, _loader);
            }
            // inline State(lua_State *st): L(st), _isCopy(true) {
            //     return;
            // }
            inline ~State() {
                if (not _isCopy)
                    _loader.getFunc<void, lua_State *>("lua_close")(L);
            }

            /* push */

            void push(integer arg) {
                _loader.getFunc<void, lua_State *, integer>("lua_pushinteger")(L, arg);
            }

            void push(string arg) {
                _loader.getFunc<void, lua_State *, string>("lua_pushstring")(L, arg.c_str());
            }

            void push(number arg) {
                _loader.getFunc<void, lua_State *, number>("lua_pushnumber")(L, arg);
            }

            void push(boolean arg) {
                _loader.getFunc<void, lua_State *, boolean>("lua_pushboolean")(L, arg);
            }

            void push(userdata arg) {
                _loader.getFunc<void, lua_State *, userdata>("lua_pushlightuserdata")(L, arg);
            }

            void push(function arg) {
                _loader.getFunc<void, lua_State *, function>("lua_pushcfunction")(L, arg);
            }

            void push(char const *arg) {
                _loader.getFunc<void, lua_State *, char const *>("lua_pushstring")(L, arg);
            }

            /* Create a new empty table */
            void newTable() {
                _loader.getFunc<void, lua_State *>("lua_newtable")(L);
            }

            /* Set a table field */
            void setField(std::string const &name, int index = -2) {
                _loader.getFunc<void, lua_State *, int, char const *>("lua_setfield")(L, index, name.c_str());
            }

            /* Set the metatable */
            void setMetatable(int index = -2) {
                _loader.getFunc<void, lua_State *, int>("lua_setmetatable")(L, index);
            }

            /* Execute a string */
            void execute(std::string const &str) {
                my_lua_dostring(L, _loader, str.c_str());
            }

            /* get */
            template <typename T>
            T get(int arg) {
                if constexpr (std::is_same<T, integer>()) {
                    return _loader.getFunc<T, lua_State *, int>("lua_tointeger")(L, arg);
                } else if constexpr (std::is_same<T, string>()) {
                    return std::string(_loader.getFunc<T, lua_State *, int>("lua_tostring")(L, arg));
                } else if constexpr (std::is_same<T, number>()) {
                    return _loader.getFunc<T, lua_State *, int>("lua_tonumber")(L, arg);
                } else if constexpr (std::is_same<T, boolean>()) {
                    return _loader.getFunc<T, lua_State *, int>("lua_toboolean")(L, arg);
                } else if constexpr (std::is_same<T, userdata>()) {
                    return _loader.getFunc<T, lua_State *, int>("lua_touserdata")(L, arg);
                } else if constexpr (std::is_same<T, function>()) {
                    return _loader.getFunc<T, lua_State *, int>("lua_tocfunction")(L, arg);
                } else {
                    throw std::runtime_error("invalid type");
                }
            }

        private:
            bool _isCopy = false;
            lua_State *L = nullptr;
            jmod::DLLoader _loader;
    };
}
