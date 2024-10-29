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

#define my_luadostring(this, str) (\
    this->_loader.getFunc<int, lua_State *, char const *>("luaL_loadstring")(this->L, str) \
    || \
    this->pcall() \
)

#define my_luaopenlibs(this) \
    this->_loader.getFunc<void, lua_State *, int, int> \
    ("luaL_openselectedlibs")(this->L, (~0), 0)

#define my_luadofile(this, str) ( \
    this->_loader.getFunc<int, lua_State *, char const *, char const *>("luaL_loadfilex")(this->L, str, nullptr) \
    || \
    this->pcall() \
)

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
                my_luaopenlibs(this);
            }
            // inline State(lua_State *st): L(st), _isCopy(true) {
            //     return;
            // }
            inline ~State() {
                if (not _isCopy)
                    _loader.getFunc<void, lua_State *>("lua_close")(L);
            }

            /* Push */

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

            /* Execute a file */
            void execute(std::string const &str) {
                my_luadostring(this, str.c_str());
            }

            /* Use a file */
            void useFile(std::string const &filename) {
                if (my_luadofile(this, filename.c_str()) != LUA_OK) {
                    pop();
                    throw std::runtime_error(get<char const *>(-1));
                }
                push(static_cast<lua::number>(3));
                pcall(1, 1);
                lua::number n = get<lua::number>(-1);
                std::cout << "got " << n << std::endl;
                pop();
            }

            /* Call a function */
            int pcall(int args = 0, int results = LUA_MULTRET, int errfunc = 0) {
                return _loader.getFunc<int, lua_State *, int, int, int, lua_KContext, lua_KFunction>
                    ("lua_pcallk")(L, args, results, errfunc, 0, nullptr);
            }

            /* Remove the n's argument */
            void pop(int n = 1) {
                _loader.getFunc<void, lua_State *, int>("lua_settop")(L, -(n)-1);
            }

            /* Get a value */
            template <typename T>
            T get(int arg) {
                if constexpr (std::is_same<T, integer>()) {
                    return _loader.getFunc<T, lua_State *, int>("lua_tointeger")(L, arg);
                } else if constexpr (std::is_same<T, char const *>()) {
                    auto ptr = _loader.getFunc<T, lua_State *, int, size_t *>("lua_tolstring")(L, arg, nullptr);
                    std::cout << arg << ", " << (void *)ptr << std::endl;
                    return (ptr == nullptr) ? "null" : ptr;
                } else if constexpr (std::is_same<T, number>()) {
                    return _loader.getFunc<T, lua_State *, int, size_t *>("lua_tonumberx")(L, arg, nullptr);
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
