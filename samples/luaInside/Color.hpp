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
        Color() {
            return;
        };
        ~Color() {
            return;
        };
        static inline auto luaName() -> std::string {
            return "Color";
        }

        static inline auto luaFunctions() -> std::map<std::string, lua::cfunction> {
            return {
                { "setColor", Color::_luaSetColor },
                { "getColor", Color::_luaSetColor },
            };
        }

    private:
        jgo::u8 r, g, b;

        static auto _luaSetColor(lua_State *l) -> int {
            lua::State L(l);
            Color *color = *(Color **)L.get<lua::userdata>(1);
            jgo::u8 nums[3] = {
                static_cast<jgo::u8>(L.get<lua::integer>(2)),
                static_cast<jgo::u8>(L.get<lua::integer>(3)),
                static_cast<jgo::u8>(L.get<lua::integer>(4)),
            };

            color->r = nums[0];
            color->g = nums[1];
            color->b = nums[2];
            return 0;
        }

        static auto _luaGetColor(lua_State *l) -> int {
            lua::State L(l);
            Color *color = *(Color **)L.get<lua::userdata>(1);

            L.push(static_cast<lua::integer>(color->r));
            L.push(static_cast<lua::integer>(color->g));
            L.push(static_cast<lua::integer>(color->b));
            return 3;
        }
};
