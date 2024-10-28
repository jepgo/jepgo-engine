/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ILua
*/

#pragma once

#include <string>

extern "C" {
    #include "./lua.h"
    #include "./lualib.h"
    #include "./lauxlib.h"
}

namespace lua {

    using number = lua_Number;
    using string = std::string;
    using integer = lua_Integer;
    using function = lua_CFunction;
    using boolean = bool;
    using userdata = void *;

    class IState {
        public:
            IState() {
                return;
            };
            inline IState(lua_State *st) {
                return;
            }
            inline ~IState() {
                return;
            }

            /* push */
            virtual void push(integer arg) = 0;
            virtual void push(string arg) = 0;
            virtual void push(number arg) = 0;
            virtual void push(boolean arg) = 0;
            virtual void push(userdata arg) = 0;
            virtual void push(function arg) = 0;
            virtual void push(char const *arg) = 0;

            /* Create a new empty table */
            virtual void newTable() = 0;

            /* Set a table field */
            virtual void setField(std::string const &name, int index = -2) = 0;

            /* Set the metatable */
            virtual void setMetatable(int index = -2) = 0;

            /* Execute a string */
            virtual void execute(std::string const &str) = 0;

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
    };
}

