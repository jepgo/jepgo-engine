/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** exceptions
*/

#pragma once

#include <stdexcept>
#include <string>

namespace jgo::errors {

    class BaseException: public std::exception {
        public:
            BaseException(std::string const &err) {
                _final = "Jepgo " + error + " → " + error + ".";
            }
            char const *what() const noexcept override {
                return _final.c_str();
            }
        protected:
            std::string error = "BaseExeption";
        private:
            std::string _final;
    };

    class NoGraphic: BaseException {
        public:
            NoGraphic(): BaseException("no graphic library loaded") {
                error = "NoGraphicLibrary";
            };
    };

    class NetworkError: BaseException {
        public:
            NetworkError(std::string const &lib, std::string const &err)
            : BaseException(err) {
                error = "Network" + lib;
            }
    };

}

