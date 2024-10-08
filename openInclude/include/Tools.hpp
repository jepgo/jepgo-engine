/*
** EPITECH PROJECT, 2024
** ImageTranslation [WSL: Fedora]
** File description:
** Tools
*/

#pragma once
#include <vector>
#include <string>

class Tools {
    public:
    /**
     * @brief A function who transform double pointer of char to a std::vector<std::string>
     * 
     * @param ac the number of elements
     * @param av the char ** tab who need to be transformed
     * @return std::vector<std::string> 
     */
    static std::vector<std::string> ToVector(int ac, char **av) {
        std::vector<std::string> res;
        for (int i = 0; i < ac; i++)
            res.push_back(av[i]);
        return res;
    };
    private:
};
