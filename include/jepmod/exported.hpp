/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** export
*/

#pragma once

#if defined(WINDOWS) || defined(_WIN32)
    /**
     * Use exported if you want your function to be exported in a shared
     * library.
     * 
     * Its better to use exported rather than `extern "C"` because exported
     * is cross platform, so dont worry about compatibility.
     */
    #define exported(type) extern "C" __declspec(dllexport) type __cdecl
#else
    /**
     * Use exported if you want your function to be exported in a shared
     * library.
     * 
     * Its better to use exported rather than `extern "C"` directly because
     * the exported macro is cross platform, so dont worry about compatibility.
     */
    #define exported(type) extern "C" type
#endif

