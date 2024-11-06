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
#include <filesystem>
#include <fstream>
#include <memory>

#include "jepengine/Client.hpp"
#include "jepengine/Server.hpp"
#include "jepmod/EasyLife.hpp"

#define safeRun(...) \
    try { __VA_ARGS__ ; } catch(jgo::errors::DLError const &) { }

/**
 * Commands:
 *      new name(@type)
 *      run (name)
 */

template <typename ...Args>
static std::string format(std::string const &format, Args ...args)
{
    int sizeInt = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1;
    if (sizeInt <= 0)
        throw jgo::errors::BaseException("cant format");
    std::size_t size = static_cast<std::size_t>(sizeInt);
    std::unique_ptr<char[]> buf(new char[size]);
    std::snprintf(buf.get(), size, format.c_str(), args ...);
    return std::string(buf.get(), buf.get() + size - 1);
}

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

static void runServer(jmod::DLLoader &loader, int ac, char const *const av[])
{
    jgo::Server game(ac, av);

    safeRun(loader.getFunc<void, jgo::Server &>("onStart")(game));
    if (game.hasNetwork()) game.host(4242);
    if (game.hasGraphicLib())
        game.getGraphicLib()->openWindow("RTYpe", {0, 0, 800, 600});
    safeRun(loader.getFunc<void, jgo::Server &>("onBegin")(game));
    while (game.hasGraphicLib() ? game.getGraphicLib()->isWindowOpen() : true) {
        if (game.hasNetwork()) {
            if (game.hasNetwork()) for (auto const &msg : game.getMessages())
                safeRun(loader.getFunc<
                    void,
                    jgo::Server &,
                    jgo::NetMessage const &
                >("onMessage")(game, msg));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        safeRun(loader.getFunc<void, jgo::Server &>("onUpdate")(game));
        if (game.hasGraphicLib()) game.getGraphicLib()->update();
        game.callSystems();
        if (game.lua) game.lua->callAllSystems();
    }
    if (game.hasGraphicLib()) game.getGraphicLib()->closeWindow();
}

static void runClient(jmod::DLLoader &loader, int ac, char const *const av[])
{
    jgo::Client game(ac, av);

    safeRun(loader.getFunc<void, jgo::Client &>("onStart")(game));
    if (game.hasNetwork()) game.connect("localhost", 4242);
    if (game.hasGraphicLib())
        game.getGraphicLib()->openWindow("RTYpe", {0, 0, 800, 600});
    safeRun(loader.getFunc<void, jgo::Client &>("onBegin")(game));
    while (game.hasGraphicLib() ? game.getGraphicLib()->isWindowOpen() : true) {
        if (game.hasNetwork()) {
            auto const &msg = game.getServerMessage();
            if (not msg.empty())
                safeRun(loader.getFunc<
                    void,
                    jgo::Client &,
                    std::vector<jgo::u8> const &
                >("onServerMessage")(game, msg));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        safeRun(loader.getFunc<void, jgo::Client &>("onUpdate")(game));
        if (game.hasGraphicLib()) game.getGraphicLib()->update();
        game.callSystems();
        if (game.lua) game.lua->callAllSystems();
    }
    if (game.hasGraphicLib()) game.getGraphicLib()->closeWindow();
}

static void createProject(std::string const &name, std::string const &type)
{
    std::filesystem::path const here = std::filesystem::current_path();
    char const *jepgoBuildEnv = std::getenv("JEPGO_BUILD");
    if (jepgoBuildEnv == nullptr)
        throw jgo::errors::EnvNotFound("JEPGO_BUILD not found");
    std::filesystem::path const helper = std::filesystem::path(jepgoBuildEnv)/"helper";
    std::filesystem::path helperFile, helperCMake;
    std::string const fileName = "game." + type + ".cpp";

    if (not std::filesystem::exists(helper))
        throw jgo::errors::NotExists("helper folder doesnt exists (its not your fault)");
    helperFile = helper/fileName;
    if (not std::filesystem::exists(helperFile))
        throw jgo::errors::NotExists("invalid type");
    helperCMake = helper/"CMakeLists.txt";
    if (not std::filesystem::exists(helperCMake))
        throw jgo::errors::NotExists("our cmake was not found (not your fault)");

    {
        std::ifstream src(helperFile.string(), std::ios::binary);
        std::string const content(
            (std::istreambuf_iterator<char>(src)),
            (std::istreambuf_iterator<char>())
        );
        std::fstream dst(here/fileName, std::ios::in | std::ios::out | std::ios::trunc | std::ios::binary);
        std::string const fmt = format(content, name.c_str());
        dst << fmt;
        src.close();
        dst.close();
    }

    {
        std::ifstream src(helperCMake.string(), std::ios::binary);
        std::string const content(
            (std::istreambuf_iterator<char>(src)),
            (std::istreambuf_iterator<char>())
        );
        std::fstream dst(here/"CMakeLists.txt", std::ios::in | std::ios::out | std::ios::trunc | std::ios::binary);
        std::string const fmt = format(content, name.c_str());
        dst << fmt;
        src.close();
        dst.close();
    }
}

static void cmdNew(std::vector<std::string> const &commands)
{
    std::size_t n = 0;
    std::string a, b;

    if (commands.size() == 2)
        throw std::runtime_error("expected an argument.");
    n = commands[2].find_first_of('@');
    if (n != std::string::npos) {
        a = commands[2].substr(0, n);
        b = commands[2].substr(n + 1);
    } else {
        a = commands[2];
        b = "client";
    }
    createProject(a, b);
}

static char const **vec2acAv(std::vector<std::string> const &vec, int &ac)
{
    ac = vec.size();
    char const **av = new const char *[ac + 1];

    for (int n = 0; n < ac; ++n)
        av[n] = vec[n].c_str();
    av[ac] = nullptr;
    return av;
}

static void runSomething(std::string const &what, int ac, char const *const av[])
{
    std::filesystem::path const here = std::filesystem::current_path();
    std::filesystem::path const build = here/"build";
    std::optional<jmod::DLLoader> loader;

    try {
        loader.emplace((here/what).string());
    } catch (std::exception const &) {
        loader.emplace((build/what).string());
    }
    if (what == "client")
        runClient(*loader, ac, av);
    else if (what == "server")
        runServer(*loader, ac, av);
    else
        throw jgo::errors::BaseException("invalid argument:" + what);
}

static void cmdRun(std::vector<std::string> const &commands)
{
    std::string what = "client";
    int less = 0;
    int ac = 0;
    char const *const *av = vec2acAv(commands, ac);

    if (commands.size() >= 3)
        what = commands[2];
    while (less < ac and std::string(av[less]) != "--")
        ++less;
    runSomething(what, ac - less, av + (ac - less));
    delete av;
}

static void treatCommand(std::vector<std::string> const &commands)
{
    if (commands.size() <= 1)
        return;
    if (commands[1] == "new")
        return cmdNew(commands);
    else if (commands[1] == "run")
        return cmdRun(commands);
    throw std::runtime_error("no such command.");
}

int main(int argc, char const *argv[])
{
    if (argc > 2 and argv[1] == "-h")
        displayHelp(argv[0]);
    try {
        treatCommand(std::vector<std::string>(argv, argv + argc));
    } catch (jgo::errors::NotExists const &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
