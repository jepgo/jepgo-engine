/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Float++
*/

#pragma once

#include <algorithm>
#include <limits>
#include <cmath>

namespace jmod {
    class FloatPP {
        public:
            FloatPP(float f): _f(f) {
                return;
            }
            constexpr inline explicit operator float(void) const noexcept {
                return _f;
            }
            constexpr inline bool isRoughly(float b, float atol = 0.001) const {
                return std::abs(_f - b) < std::min(std::abs(_f), std::abs(b)) \
                    * atol;
            }
            constexpr inline float round() const {
                return floor(_f + 0.5);
            }

        private:
            float _f;
    };
}
