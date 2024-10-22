/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** SubVec
*/

#pragma once

#include <vector>
#include <functional>
#include <cstddef>

template <typename T>
class VecPP {
    public:
        inline VecPP(std::vector<T> const &v) : _v(v) {}

        inline auto subVec(
            std::size_t drop = 0,
            std::size_t tail = npos
        ) const -> std::vector<T> {
            if (drop >= _v.size())
                return {};
            if (tail == npos)
                tail = 0;
            else if (tail > _v.size() - drop)
                tail = _v.size() - drop;
            return std::vector<T>(_v.begin() + drop, _v.end() - tail);
        }

        template<typename N>
        inline auto cast(void) const -> std::vector<N> {
            static_assert(std::is_integral<T>::value);
            static_assert(std::is_integral<N>::value);
            static_assert(sizeof(N) > 0 && sizeof(N) <= 8);
            std::vector<N> res;
            std::size_t size = sizeof(N);
            N tmp;

            for (std::size_t i = 0; i < _v.size(); i += size) {
                if (i + size - 1 >= _v.size())
                    continue;
                for (std::size_t j = 0; j < size; ++j)
                    tmp |= static_cast<N>(_v[i + j]) << ((size - 1 - j) * 8);
                res.push_back(tmp);
            }
            return res;
        }

        inline auto map(std::function<void(T &)> f) -> VecPP & {
            for (T &e : _v)
                f(e);
            return *this;
        }

        inline explicit operator std::vector<T>(void) const {
            return _v;
        }

        inline auto join(std::string const &sep = "") const -> std::string {
            auto it = _v.begin();
            std::string res;

            if (it != _v.end())
                res += *it++;
            for (; it != _v.end(); ++it) {
                if (it->empty())
                    continue;
                res += sep + *it;
            }
            return res;
        }

        inline auto extend(std::vector<T> const &other) -> std::vector<T> {
            std::vector<T> res(_v);

            res.insert(res.end(), other.begin(), other.end());
            return res;
        }

        inline auto operator+(std::vector<T> const &other) -> std::vector<T> {
            return extend(other);
        }

    private:
        static std::size_t const npos = static_cast<std::size_t>(-1);
        std::vector<T> _v;
};

