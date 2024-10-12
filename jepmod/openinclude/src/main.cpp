/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** test
*/

#include <string>
#include <iostream>

#include "OpenInclude.hpp"

int main(int ac, char **av)
{
    std::vector<std::string> args(av + 1, av + ac);

    try {
        if (args.empty())
            throw OpenInclude::Error("bad argument numbers");
        OpenInclude tmp = OpenInclude(args[0]);
        for (auto const &e : tmp.getClasses())
            std::cout << "class found: " << e << std::endl;
    } catch(OpenInclude::Error const &e) {
        std::cerr << "failure: " << e.what() << std::endl;
    }
    return 0;
}