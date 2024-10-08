/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** OpenInclude
*/

#include "OpenInclude.hpp"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <regex>

void getFiles(const std::string& code, std::vector<std::string> &tmp) {
    std::regex includePattern(R"#(#include\s*<([^>]+)>|#include\s*"([^"]+)")#");
    std::smatch match;

    std::string::const_iterator searchStart(code.cbegin());
    while (std::regex_search(searchStart, code.cend(), match, includePattern)) {
        if (match[1].matched) {
            tmp.push_back(match[1]);
        } else if (match[2].matched) {
            tmp.push_back(match[2]);
        }
        searchStart = match.suffix().first;
    }
}

static void getAllFiles(std::string &f, std::vector<std::string> &tmp)
{
    std::string Line;
    std::string final;
    std::ifstream file(f);

    if (file.is_open()) {
        while (getline(file, Line)) {
            final += Line + "\n";
        }
    } else {
        throw Error("File doesn't exist !");
    }
    file.close();
    getFiles(final, tmp);
}

OpenInclude::OpenInclude(std::string file) : _file(file)
{
    getAllFiles(file, _allFile);
    for (std::size_t i = 0; i < _allFile.size(); i++) {
        std::cout << _allFile[i] << std::endl;
    }
}

OpenInclude::~OpenInclude()
{
}
