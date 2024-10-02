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
#include <dlfcn.h>

namespace jmod {
    class DLLoader {
        public:
            DLLoader(std::string const &);
            ~DLLoader();

            template <typename A, typename... B>
            inline auto getFunc(std::string const &sym) -> A(*)(B...) {
                auto access =
                    reinterpret_cast<A(*)(B...)>(dlsym(_ptr, sym.c_str()));

                if (access == nullptr)
                    throw std::runtime_error(dlerror());
                return access;
            }

        private:
            void *_ptr;
    };
}
