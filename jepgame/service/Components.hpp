/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Components
*/

#pragma once

namespace jgo::enums {
    enum Components {
        End,
        Position,       // u16 u16
        Drawable,       // u8  u16 u16 u16 u16 f32 f32
        Controllable,
        Collision,      // u16 u16
        Velocity,       // u8  u8  u8  u8
        SpriteStatus,   // u16 u16 u16 u16 u16
    };
}
