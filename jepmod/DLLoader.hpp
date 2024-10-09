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
#if defined(WINDOWS) || defined(_WIN32)
    #include <windows.h>

    class WindowsRuntimeError : public std::runtime_error {
        public:
        WindowsRuntimeError(DWORD errorCode) : std::runtime_error(GetErrorMessage(errorCode)) {
            return;
        }

        private: static std::string GetErrorMessage(DWORD errorCode) {
            char buffer[256];
            FormatMessageA(
                FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL, errorCode, 0, buffer, sizeof(buffer), NULL
            );
            return buffer;
        }
    };
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
                    #if defined(WINDOWS) || defined(_WIN32)
                    GetProcAddress(_ptr, sym.c_str())
                    #else
                    dlsym(_ptr, sym.c_str())
                    #endif
                );

                if (access == nullptr)
                    #if defined(WINDOWS) || defined(_WIN32)
                    throw WindowsRuntimeError(GetLastError());
                    #else
                    throw std::runtime_error(dlerror());
                    #endif
                return access;
            }

        private:
            #if defined(WINDOWS) || defined(_WIN32)
            HINSTANCE _ptr;
            #else
            void *_ptr;
            #endif
    };
}
