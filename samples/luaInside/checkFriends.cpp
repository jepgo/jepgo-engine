/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** checkFriends
*/

#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

class Burnable {
    public:
        std::vector<int> luaFriend(int n) {
            return {n + 2, 2, 3};
        }
};

template <typename T>
concept LuaFriend = requires(T a) {
    { a.luaFriend(std::declval<int>()) } -> std::same_as<std::vector<int>>;
};

template <LuaFriend T>
void loadLuafriendlyComponent(int n) {
    T element;
    auto result = element.luaFriend(n);
    std::cout << result[0] << std::endl;
}

int main() {
    loadLuafriendlyComponent<Burnable>(3);
    return 0;
}