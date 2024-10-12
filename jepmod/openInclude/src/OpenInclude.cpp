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
#include <set>

void getFiles(const std::string& code, std::vector<std::string> &tmp) {
    std::regex includePattern(R"#(#include\s*<([^>]+)>|#include\s*"([^"]+)")#");
    std::smatch match;

    std::string::const_iterator searchStart(code.cbegin());
    while (std::regex_search(searchStart, code.cend(), match, includePattern)) {
        if (match[1].matched) {
            tmp.push_back("include/" + match[1].str());
        } else if (match[2].matched) {
            tmp.push_back("include/" + match[2].str());
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

static void extractClassNames(const std::string& filename, std::vector<std::string> &tmp) {
    std::ifstream file(filename);
    std::vector<std::string> classNames;

    if (!file.is_open()) {
        throw std::runtime_error("Erreur : impossible d'ouvrir le fichier " + filename);
    }

    std::string line;
    std::regex classRegex(R"(\bclass\s+([A-Za-z_][A-Za-z0-9_]*)\b)");

    while (std::getline(file, line)) {
        std::smatch match;
        while (std::regex_search(line, match, classRegex)) {
            classNames.push_back(match[1]);
            line = match.suffix();
        }
    }

    file.close();
    for (const auto& className : classNames) {
        tmp.push_back(className);
        //std::cout << className << std::endl;
    }
}

OpenInclude::OpenInclude(std::string file) : _file(file)
{
    getAllFiles(file, _allFile);
    std::cout << "yes" << std::endl;
    for (std::size_t i = 0; i < _allFile.size(); i++) {
        extractClassNames(_allFile[i], _allClass);
    }
    for (std::size_t i = 0; i < _allClass.size(); i++) {
        std::cout << "val = " << _allClass[i] << std::endl;
    }
}

OpenInclude::~OpenInclude()
{
}
