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

#include "DLLoader.hpp"
#include <iostream>

using namespace jmod;

DLLoader::DLLoader(std::string const &filename)
{
    #if defined(WINDOWS) || defined(_WIN32)
    _ptr = LoadLibrary((LPCSTR)(filename.c_str()));
    #else
    _ptr = dlopen(filename.c_str(), RTLD_LAZY);
    #endif
    std::cout << (LPCSTR)(filename.c_str()) << std::endl;
    if (_ptr == nullptr) {
        #if defined(WINDOWS) || defined(_WIN32)
        throw WindowsRuntimeError(GetLastError());
        #else
        throw std::runtime_error(dlerror());
        #endif
    }
}

DLLoader::~DLLoader()
{
    #if defined(WINDOWS) || defined(_WIN32)
    FreeLibrary(_ptr);
    #else
    dlclose(_ptr);
    #endif
}
