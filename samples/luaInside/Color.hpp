/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Color
*/

#pragma once

#include <map>
#include <string>
#include "jeplua/Lua.hpp"
#include "jepengine/types.hpp"

class Color {
    public:
        Color();
        ~Color();
        inline auto luaFriend() -> std::map<std::string, lua_CFunction> {
            return {
                { "setColor", Color::_luaSetColor },
                { "getColor", Color::_luaSetColor },
            };
        }

    private:
        jgo::u8 r, g, b;

        static auto _luaSetColor(lua_State *L) -> int {
            Color *color = *(Color **)lua_touserdata(L, 1);
            jgo::u8 nums[3] = {
                luaL_checkinteger(L, 2),
                luaL_checkinteger(L, 3),
                luaL_checkinteger(L, 4),
            };
            color->r = nums[0];
            color->g = nums[1];
            color->b = nums[2];
            return 0;
        }

        static auto _luaGetColor(lua_State *L) -> int {
            Color *color = *(Color **)lua_touserdata(L, 1);
            lua_pushinteger(L, color->r);
            lua_pushinteger(L, color->g);
            lua_pushinteger(L, color->b);
            return 3;
        }
};
