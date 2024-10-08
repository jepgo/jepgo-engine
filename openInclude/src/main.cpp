/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** test
*/

#include <string>
#include "OpenInclude.hpp"
#include "Tools.hpp"
#include "Error.hpp"

static void VerifArgs(std::vector<std::string> &args)
{
    if (args.size() != 2)
        throw Error("bad argument numbers");
}

int main(int ac, char **av)
{
    std::vector<std::string> args = Tools::ToVector(ac, av);

    try {
        VerifArgs(args);
        OpenInclude tmp = OpenInclude(args[1]);
    } catch(const Error &e) {
        std::cerr << "failure: " << e.what() << std::endl;
    }
    return 0;
}