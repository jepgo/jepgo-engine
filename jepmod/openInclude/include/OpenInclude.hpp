/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** OpenInclude
*/

#pragma once
#include "Error.hpp"
#include <vector>

class OpenInclude {
    public:
        OpenInclude(std::string file);
        ~OpenInclude();

    private:
        std::string _file;
        std::vector<std::string> _allFile;
        std::vector<std::string> _allClass;
};
