/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** export
*/

#pragma once

#if defined(WINDOWS) || defined(_WIN32)
    #define exported(type) extern "C" __declspec(dllexport) type __cdecl
#else
    #define exported(type) extern "C" type
#endif

