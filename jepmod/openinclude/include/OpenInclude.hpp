/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** OpenInclude
*/

#pragma once

#include <string>
#include <stdexcept>
#include <vector>

class OpenInclude {
    public:
        OpenInclude(std::string const &file);

        inline auto getClasses(void) const noexcept -> std::vector<std::string> {
            return _allClasses;
        }

        inline auto getFiles(void) const noexcept -> std::vector<std::string> {
            return _allFile;
        }

        class Error : public std::exception {
            public:
                Error(std::string const &msg) : _msg(msg) {
                    return;
                };
                inline const char *what() const noexcept override {
                    return _msg.c_str();
                }
            private:
                std::string _msg;
        };

    private:
        std::string _file;
        std::vector<std::string> _allFile;
        std::vector<std::string> _allClasses;
};
