/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** OpenInclude
*/

#include <cstdio>
#include <iostream>
#include <fstream>
#include <regex>

#include "OpenInclude.hpp"

static void getFiles(std::string const &code, std::vector<std::string> &tmp) {
    std::regex includePattern(R"#(#include\s*<([^>]+)>|#include\s*"([^"]+)")#");
    std::smatch match;
    std::string::const_iterator searchStart(code.cbegin());

    while (std::regex_search(searchStart, code.cend(), match, includePattern)) {
        if (match[1].matched)
            tmp.push_back("include/" + match[1].str());
        else if (match[2].matched)
            tmp.push_back("include/" + match[2].str());
        searchStart = match.suffix().first;
    }
}

static void getAllFiles(std::string const &f, std::vector<std::string> &tmp)
{
    std::string line;
    std::string final;
    std::ifstream file(f);

    if (not file.is_open())
        throw OpenInclude::Error("File doesn't exist !");
    while (std::getline(file, line))
        final += line + "\n";
    file.close();
    tmp.push_back(f);
    getFiles(final, tmp);
}

static void extractClassNames(std::string const &filename, std::vector<std::string> &tmp) {
    std::ifstream file(filename);
    std::vector<std::string> res;
    std::string line, classname, realname, fullnamespace;
    std::regex classRegex(R"(\bclass\s+([A-Za-z_][A-Za-z0-9_]*)\b)");
    std::regex namespaceRegex(R"(\bnamespace\s+([A-Za-z_][A-Za-z0-9_]*)\b)");
    std::smatch match;
    std::stack<std::string> context;
    std::size_t braces = 0;

    if (not file.is_open())
        throw OpenInclude::Error("cant open file " + filename);
    while (std::getline(file, line)) {
        while (std::regex_search(line, match, namespaceRegex)) {
            context.push(match[1].str());
            line = match.suffix().str();
        }
        while (std::regex_search(line, match, classRegex)) {
            classname = match[1].str();
            realname = classname;
            if (not context.empty()) {
                while (not context.empty()) {
                    fullnamespace = context.top() + "::" + fullnamespace;
                    context.pop();
                }
                realname = fullnamespace + classname;
            }
            res.push_back(realname);
            line = match.suffix().str();
        }
        braces = std::count(line.begin(), line.end(), '}');
        for (size_t i = 0; i < braces; ++i)
            if (not context.empty())
                context.pop();
    }
    file.close();
    for (auto const &name : res) {
        tmp.push_back(name);
    }
}

OpenInclude::OpenInclude(std::string const &file): _file(file)
{
    getAllFiles(file, _allFile);
    for (auto const &file : _allFile)
        extractClassNames(file, _allClasses);
}
