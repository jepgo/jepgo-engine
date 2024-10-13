/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** test
*/

#include <string>
#include <iostream>
#include <filesystem>

#include "jepmod/exported.hpp"
#include "OpenInclude.hpp"
#include "FileBuilder.hpp"
#include "external.hpp"

std::string jgame::generateServerModule(std::string const &hppFile)
{
    std::string base("external.server");
    std::string command, sharedFilePath;
    std::filesystem::path here = std::filesystem::current_path();
    OpenInclude includes = OpenInclude(hppFile);
    FileBuilder fb(includes, base + ".cpp");

    std::cout << here.string() << __FILE__ << std::endl;
    for (auto const &e : includes.getClasses())
        std::cout << "class found: " << e << std::endl;
    for (auto const &f : includes.getFiles())
        std::cout << "file found: " << f << std::endl;
    fb.writeHeader();
    fb.writePreprocess();
    fb.writeEnum();
    fb.writeServer();

    #if defined(WINDOWS) || defined(_WIN32)
    sharedFilePath = base + ".dll";
    #else
    sharedFilePath = "lib" + base + ".so";
    #endif
    command = "g++ -shared -fpic " + base + ".cpp -o " + sharedFilePath;
    std::system(command.c_str());
    // std::remove((base + ".cpp").c_str());
    return base;
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