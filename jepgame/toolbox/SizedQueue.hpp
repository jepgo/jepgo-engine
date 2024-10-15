/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** SizedQueue
*/

#pragma once

#include <queue>
#include <cstddef>
#include <stdexcept>

template <typename T>
class SizedQueue {
    public:
        SizedQueue(std::size_t maxSize): _maxSize(maxSize) {
            if (not maxSize)
                throw std::invalid_argument("expected more than 0");
        }

        inline auto push(T const &item) -> void {
            if (_q.size() == _maxSize)
                _q.pop();
            _q.push(item);
        }

        inline auto pop(void) -> void {
            if (_q.empty())
                throw std::out_of_range("queue is empty");
            _q.pop();
        }

        inline auto front(void) const -> T const & {
            if (_q.empty())
                throw std::out_of_range("queue is empty");
            return _q.front();
        }

        inline auto empty(void) const -> bool {
            return _q.empty();
        }

        inline auto size(void) const -> std::size_t {
            return _q.size();
        }

        inline auto max_size(void) const -> std::size_t {
            return _maxSize;
        }

    private:
        std::queue<T> _q;
        std::size_t _maxSize;
};
