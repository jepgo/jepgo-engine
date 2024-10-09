/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** DLLoader
*/

#pragma once

#include <string>
#include <stdexcept>
#include <memory>
#ifdef WINDOWS
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif

namespace jmod {
    class DLLoader {
        public:
            DLLoader(std::string const &);
            ~DLLoader();

            template <typename A, typename... B>
            inline auto getFunc(std::string const &sym) -> A(*)(B...) {
                auto access = reinterpret_cast<A(*)(B...)>(
                    #ifdef WINDOWS
                    GetProcAddress(_ptr, sym.c_str())
                    #else
                    dlsym(_ptr, sym.c_str())
                    #endif
                );

                if (access == nullptr)
                    #ifdef WINDOWS
                    throw std::runtime_error(FormatMessage(
                        FORMAT_MESSAGE_FROM_SYSTEM,
                        NULL, GetLastError(),
                        0, NULL, 0, NULL
                    ));
                    #else
                    throw std::runtime_error(dlerror());
                    #endif
                return access;
            }

        private:
            #ifdef WINDOWS
            HINSTANCE _ptr;
            #else
            void *_ptr;
            #endif
    };
}
