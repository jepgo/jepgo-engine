/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** test
*/

#include <string>
#include <iostream>

#include "jepmod/exported.hpp"
#include "OpenInclude.hpp"
#include "FileBuilder.hpp"

void generateServerModule(std::string const &hppFile)
{
    OpenInclude includes = OpenInclude(hppFile);
    FileBuilder fb(includes, "out.cpp");

    for (auto const &e : includes.getClasses())
        std::cout << "class found: " << e << std::endl;
    for (auto const &f : includes.getFiles())
        std::cout << "file found: " << f << std::endl;
    fb.writeHeader();
    fb.writePreprocess();
    fb.writeEnum();
    fb.writeServer();
}

int main(int ac, char **av)
{
    std::vector<std::string> args(av + 1, av + ac);

    try {
        if (args.empty())
            throw OpenInclude::Error("bad argument numbers");
        generateServerModule(args[0]);
    } catch(OpenInclude::Error const &e) {
        std::cerr << "failure: " << e.what() << std::endl;
    }
    return 0;
}