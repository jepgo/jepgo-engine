/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** FileBuilder
*/

#pragma once

#include <vector>
#include <optional>
#include <string>
#include <fstream>

#include "OpenInclude.hpp"

class FileBuilder {
    public:
        FileBuilder(OpenInclude const &in, std::string const &out)
        : _stream(out), _classes(in.getClasses()), _files(in.getFiles()) {
            return;
        }
        void writeHeader(void);
        void writeServerSender(void);
        void writeServerBuilder(void);
        void writeClient(void);
        void writePreprocess(void);
        void writeEnum(void);

        class Exception : public std::exception {
            public:
                Exception(std::string const &msg): _msg(msg) {
                    return;
                };
                inline const char *what(void) const noexcept override {
                    return _msg.c_str();
                }
            private:
                std::string _msg;
        };

    protected:
    private:
        std::ofstream _stream;
        std::vector<std::string> _classes;
        std::vector<std::string> _files;
};
