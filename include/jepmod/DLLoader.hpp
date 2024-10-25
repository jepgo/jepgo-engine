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
#include <functional>

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
    /**
     * Load your shared library using DLLoader class.
     * 
     * You will first have to give the shared library path, then you can use
     * the `getFunc` method to retrieve your functions.
     */
    class DLLoader {
        public:
            /**
             * This is the DLLoader constructor.
             * 
             * ### Arguments
             * `filePath` - The path to your library.
             * 
             * ### Throws
             * `std::runtime_error` - If the file can not be opened.
             */
            DLLoader(std::string filePath);

            /**
             * This is the DLLoader destroyer. Nothing to say about it...
             */
            ~DLLoader();

            /**
             * Get a function in a shared library.
             * 
             * Please note that you have to know what your function returns
             * and what arguments it takes.
             * 
             * ### Templates
             * `A` - The return type.
             * `B...` - The argument types.
             * 
             * ### Arguments
             * `sym` - The symbol, aka your function name
             * 
             * ### Returns
             * A function pointer to what you asked
             * 
             * ### Example
             * `lib.getFunc<int, int, int>("add");`
             * 
             * This will get a function named "add" that returns a int, and
             * takes 2 ints in parametter.
             */
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

    /**
     * The DLLoader reference.
     */
    using DLLoaderPtr = std::shared_ptr<DLLoader>;

}
