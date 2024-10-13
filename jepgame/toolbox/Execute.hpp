/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Excecute
*/

#pragma once

#include <cstdlib>
#include <string>
#include <stdexcept>

class Execute {
    public:
        Execute(std::string const &command) {
            FILE *pipe = popen(command.c_str(), "r");
            int res;

            if (not pipe)
                throw std::runtime_error("popen() failed!");
            res = pclose(pipe);
            status = WEXITSTATUS(res);
        };
        int status;

    protected:
    private:
};
