/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** types
*/

#ifndef TYPES_HPP_
    #define TYPES_HPP_

    #include <cstdint>

namespace jgo {
    using u8 = std::uint8_t;
    using s8 = std::int8_t;
    using u16 = std::uint16_t;
    using s16 = std::int16_t;
    using u32 = std::uint32_t;
    using s32 = std::int32_t;
    using u64 = std::uint64_t;
    using s64 = std::int64_t;

    /**
     * A Rectangle that have x, y width and height.
     */
    struct Rectangle {
        Rectangle(float xA, float yA, float wA, float hA)
        : x(xA), y(yA), width(wA), height(hA) {
            return;
        };
        float x;
        float y;
        float width;
        float height;
    };

    /**
     * Just a vector with 3 float positions.
     */
    struct Vector3 {
        float x, y, z;
    };

    /**
     * Just a vector with 2 floats.
     */
    struct Vector2 {
        float x, y;
    };

    /**
     * Same as rectangle, but in 3D so it have a pos and size.
     */
    struct HitBox {
        Vector3 pos;
        Vector3 size;
        Vector3 rotation;
    };
}

#endif /* !TYPES_HPP_ */
