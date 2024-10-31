/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** DLLoader
*/

#if defined(WINDOWS) || defined(_WIN32)
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif

#include "jepmod/DLLoader.hpp"
#include <iostream>

using namespace jmod;

DLLoader::DLLoader(std::string fullpath)
{
    std::size_t slashIndex = fullpath.find_last_of('/');
    std::string a, b, filename;

    if (slashIndex == std::string::npos) {
        a = "./";
        b = fullpath;
    } else {
        a = fullpath.substr(0, slashIndex + 1);
        b = fullpath.substr(slashIndex + 1);
    }

    #if defined(WINDOWS) || defined(_WIN32)
    filename = a + b + ".dll";
    _ptr = LoadLibrary((LPCSTR)(filename.c_str()));
    if (_ptr == nullptr)
        throw WindowsRuntimeError(GetLastError());
    #else
    #if defined(__APPLE__)
    filename = a + "lib" + b + ".so";
    #else
    filename = a + "lib" + b + ".so";
    #endif
    _ptr = dlopen(filename.c_str(), RTLD_LAZY);
    if (_ptr == nullptr)
        throw std::runtime_error(dlerror());
    #endif
}

DLLoader::~DLLoader()
{
    if (_ptr)
        #if defined(WINDOWS) || defined(_WIN32)
        FreeLibrary(_ptr);
        #else
        dlclose(_ptr);
        #endif
}
