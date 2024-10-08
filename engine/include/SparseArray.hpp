/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** SpaceArray
*/

#pragma once
#include <any>
#include <vector>
#include <iostream>
#include <optional>

template <typename T>
std::ostream &operator<<(std::ostream &os, std::optional<T> value)
{
    if (value.has_value())
        return os << value.value();
    return os;
}

template <typename T>
class SparseArray
{
    using container_t = std::vector<std::optional<T>>; // optionally add your allocator template here.
    using size_type = typename container_t ::size_type;

public:
    SparseArray() = default;
    ~SparseArray() = default;

    std::optional<T> &operator[](size_t index)
    {
        return list[index];
    };

    SparseArray &operator=(SparseArray const &)
    {
        return this;
    };

    void pop_back()
    {
        list.pop_back();
    }

    std::optional<T> &back()
    {
        return list.back();
    }

    void pop_at(size_t index)
    {
        list.erase(list.begin() + index);
    }

    void add(std::optional<T> &val)
    {
        list.push_back(val);
    }

    void add(std::optional<T> val = std::nullopt)
    {
        if (val.has_value())
            list.push_back(val);
        else
            list.push_back(std::nullopt);
    }

    size_t size()
    {
        return list.size();
    }

    std::vector<std::optional<T>> &getList()
    {
        return list;
    }

    // T &insert_at(size_type pos, T const & comp)
    // {
    //     list[pos] = comp;
    // }

    void insert_at(size_type pos, T &&comp)
    {
        //list.emplace(pos, comp);
        //list.insert(list.cbegin() + pos, std::move(comp));
        //std::cout << "insert" << std::endl;
        list.at(pos) = std::move(comp);
        //return list[pos].value();
    }

    void erase(std::size_t index)
    {
        list.at(index) = std::nullopt;
    }

    /**
     * The sparse array iterator.
     */
    class Iterator {
        using veciter = std::vector<std::optional<T>>::iterator;

        public:
            Iterator(veciter it) noexcept: _it(it) {
                while (not (*_it).has_value())
                    ++_it;
            }
            inline T operator*(void) const {
                return (*_it).value();
            }
            inline Iterator &operator++(void) noexcept {
                while (not (*_it).has_value())
                    ++_it;
                return *this;
            }
            inline bool operator==(Iterator const &other) const noexcept {
                return _it == other._it;
            }
            inline bool operator!=(Iterator const &other) const noexcept {
                return _it != other._it;
            }
            inline Iterator operator++(int) noexcept {
                Iterator tmp = *this;

                ++*this;
                return tmp;
            }
         
        private:
            veciter _it;
    };

    /**
     * The begin iterator.
     */
    inline Iterator begin(void) {
        return Iterator(list.begin());
    }

    /**
     * The end iterator.
     */
    inline Iterator end(void) {
        return Iterator(list.end());
    }

private:
    std::vector<std::optional<T>> list;
};
