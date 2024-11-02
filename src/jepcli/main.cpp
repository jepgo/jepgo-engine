/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main
*/

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

/**
 * Commands:
 *      new name(@type)
 *      run (name)
 */

static void displayHelp(std::string const &bin)
{
    std::cout << "USAGE:" << std::endl
        << "    " << bin << " [command] ... (-- arg1 arg2)" << std::endl
        << std::endl
        << "COMMANDS:" << std::endl
        << "    new <projectName>(@<spefier>)   "
        << "creates a new jepgo project." << std::endl
        << "It will generate a cmake and a"
        << std::endl;
}

static void cmdNew(std::vector<std::string> const &commands)
{
    std::size_t n = 0;
    std::string a, b;

    if (commands.size() == 1)
        throw std::runtime_error("expected an argument.");
    n = commands[1].find_first_of('@');
    if (n != std::string::npos) {
        a = commands[1].substr(0, n);
        b = commands[1].substr(n + 1);
    } else {
        a = commands[1];
        b = "game";
    }
    std::cout << a << ", " << b << std::endl;
}

static void cmdRun(std::vector<std::string> const &commands)
{
    return;
}

static void run(std::vector<std::string> const &commands)
{
    if (commands.empty())
        return;
    if (commands[0] == "new")
        return cmdNew(commands);
    else if (commands[1] == "run")
        return cmdRun(commands);
    throw std::runtime_error("no such command.");
}

int main(int argc, char const *argv[])
{
    if (argc > 2 and argv[1] == "-h")
        displayHelp(argv[0]);
    run(std::vector<std::string>(argv + 1, argv + argc));
    return 0;
}
