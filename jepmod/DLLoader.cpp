/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** DLLoader
*/

#ifdef WINDOWS
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif

#include "DLLoader.hpp"

using namespace jmod;

DLLoader::DLLoader(std::string const &filename)
{
    #ifdef WINDOWS
    _ptr = LoadLibrary(TEXT(filename.c_str()));
    #else
    _ptr = dlopen(filename.c_str(), RTLD_LAZY);
    #endif
    if (_ptr == nullptr)
        #ifdef WINDOWS
        throw WindowsRuntimeError(GetLastError());
        #else
        throw std::runtime_error(dlerror());
        #endif
}

DLLoader::~DLLoader()
{
    #ifdef WINDOWS
    FreeLibrary(_ptr);
    #else
    dlclose(_ptr);
    #endif
}
