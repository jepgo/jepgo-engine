/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** SpaceArray
*/

#pragma once
#include <any>
#include <vector>
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
    using container_t = std ::vector<std::optional<T>>; // optionally add your allocator template here.
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

    template <class... Params>
    T &emplace_at(size_type pos, Params &&...par)
    {
        list[pos] = std::vector<std::optional<T>>::allocator_type::allocate(par...);
    }

private:
    std::vector<std::optional<T>> list;
};
