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
        throw std::runtime_error(dlerror());
}

DLLoader::~DLLoader()
{
    dlclose(_ptr);
}
