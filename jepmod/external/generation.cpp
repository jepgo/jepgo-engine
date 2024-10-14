/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** test
*/

#include <string>
#include <iostream>
#include <filesystem>

#include "jepgame/toolbox/EasyLife.hpp"
#include "jepgame/toolbox/Execute.hpp"
#include "jepmod/exported.hpp"
#include "OpenInclude.hpp"
#include "FileBuilder.hpp"
#include "external.hpp"

std::string jgame::generateServerModule
(std::string const &firstArg, std::string const &hppFile)
{
    std::string base("external.server");
    std::string command, destFile;
    std::string sourceFile = EasyLife(firstArg) / base + ".cpp";
    OpenInclude includes = OpenInclude(EasyLife(firstArg) / hppFile);
    FileBuilder fb(includes, sourceFile);

    for (auto const &e : includes.getClasses())
        std::cout << "class found: " << e << std::endl;
    for (auto const &f : includes.getFiles())
        std::cout << "file found: " << f << std::endl;
    fb.writeHeader();
    fb.writePreprocess();
    fb.writeEnum();
    fb.writeServerSender();
    fb.writeServerBuilder();

    #if defined(WINDOWS) || defined(_WIN32)
    destFile = EasyLife(firstArg) / base + ".dll";
    #else
    destFile = EasyLife(firstArg) / "lib" + base + ".so";
    #endif
    command = "g++ -shared -fpic " + sourceFile + \
        " -o " + destFile + " -iquote" + EasyLife(firstArg) / "..";
    std::cout << command << std::endl;
    // std::cout << Execute(command).status << std::endl;
    // std::cout << std::system(command.c_str()) << std::endl;
    // std::remove((base + ".cpp").c_str());
    return EasyLife(firstArg) / base;
}

// int main(int ac, char **av)
// {
//     std::vector<std::string> args(av + 1, av + ac);

//     try {
//         if (args.empty())
//             throw OpenInclude::Error("bad argument numbers");
//         generateServerModule(args[0]);
//     } catch(OpenInclude::Error const &e) {
//         std::cerr << "failure: " << e.what() << std::endl;
//     }
//     return 0;
// }