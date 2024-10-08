/*
** EPITECH PROJECT, 2024
** ImageTranslation [WSL: Fedora]
** File description:
** Error
*/

#pragma once

#include <iostream>
#include <string>

namespace caca::zizi {
    class Error : public std::exception
    {
        public:
            Error(const std::string &msg) : _msg(msg){};
            ~Error();
            const char *what() const noexcept override;
        private:
            std::string _msg;
    };
} // namespace caca::zizi

namespace foo::bar {
    class Error : public std::exception
    {
        public:
            Error(const std::string &msg) : _msg(msg){};
            ~Error();
            const char *what() const noexcept override;
        private:
            std::string _msg;
    };
} // namespace caca::zizi
