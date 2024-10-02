/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** DLLoader
*/

#include <dlfcn.h>

#include "DLLoader.hpp"

using namespace jmod;

DLLoader::DLLoader(std::string const &filename)
{
    _ptr = dlopen(filename.c_str(), RTLD_LAZY);
    if (_ptr == nullptr)
        throw std::runtime_error(dlerror());
}

DLLoader::~DLLoader()
{
    dlclose(_ptr);
}
