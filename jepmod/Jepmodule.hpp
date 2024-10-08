/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Jepmodule
*/

#pragma once

#include <string>
#include <vector>
#include "DLLoader.hpp"

namespace jmod {
    class Jepmodule {
        public:
            Jepmodule(std::string const &path);
            ~Jepmodule();
            enum Symbol {
                SymModule,
                SymParOpen,
                SymParClose,
                SymString,
                SymSep
            };
        private:
            std::vector<DLLoader> _components;
    };
}
