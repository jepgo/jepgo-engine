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
#include <filesystem>

#include "OpenInclude.hpp"
#include "jepgame/toolbox/Vec++.hpp"

static void getFiles
(std::string const &filename, std::string const &code, std::vector<std::string> &tmp)
{
    std::regex includePattern(R"#(#include\s*<([^>]+)>|#include\s*"([^"]+)")#");
    std::smatch match;
    std::filesystem::path dir(filename);
    std::string::const_iterator searchStart(code.cbegin());

    dir = dir.parent_path();
    while (std::regex_search(searchStart, code.cend(), match, includePattern)) {
        if (match[1].matched)
            tmp.push_back(dir.string() + "/" + match[1].str());
        else if (match[2].matched)
            tmp.push_back(dir.string() + "/" + match[2].str());
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
    getFiles(f, final, tmp);
}

static std::string striptease(std::string const &str)
{
    auto start = std::find_if_not(str.begin(), str.end(), isspace);
    auto end = std::find_if_not(str.rbegin(), str.rend(), isspace).base();
    
    return (start < end) ? std::string(start, end) : "";
}

static std::string readFileContent(std::string const &filename)
{
    std::ifstream file(filename);
    std::ostringstream oss;
    
    if (not file.is_open())
        throw std::runtime_error("cant open file " + filename);
    oss << file.rdbuf();
    return oss.str();
}

static std::vector<std::string> extractClasses(std::string const &filename)
{
    // std::regex pattern(R"((namespace\s+([^{}:]+)\s*\{)|(class\s+([^:{]+)\s*\{)|(\{)|(\}))");
    // std::regex pattern(R"((namespace\s+([^{}:\s]+)\s*\{)|(class\s+([a-zA-Z_][\w]*)(?:\s*:\s*[^{}]*|)\s*\{)|(\{)|(\}))");
    // std::regex pattern(R"((namespace\s+([^{}:\s]+)\s*\{)|(class\s+([a-zA-Z_][\w]*)\s*(?:::[\w:]+)?\s*\{)|(\{)|(\}))");
    // std::regex pattern(R"((namespace\s+([^{}]+)\s*\{)|(class\s+([^;{}]+)\s*\{)|(class\s+([^{}]+);\s*)|(\{)|(\}))");
    std::regex pattern(R"((namespace\s+([^{}]+)\s*\{)|(class\s+([^{}]+)\s*\{)|(\{)|(\}))");
    std::regex classRegex(R"(\bclass\s+(\w+))");
    std::smatch miniMatch;
    std::string input;
    try {
        input = readFileContent(filename);
    } catch (std::exception const &) {
        return {};
    }
    std::smatch matches;
    std::string::const_iterator searchStart(input.cbegin());
    std::vector<std::string> context;
    std::vector<std::string> res;
    std::string tmp;
    std::size_t index;

    while (std::regex_search(searchStart, input.cend(), matches, pattern)) {

        if (matches[2].matched) { // namespace
            context.push_back(striptease(matches[2]));

        } else if (matches[4].matched) { // class
            tmp = matches[4];
            index = tmp.find_first_of(':');
            if (index != std::string::npos)
                tmp = tmp.substr(0, index);
            index = tmp.find_last_of(';');
            if (index != std::string::npos) {
                tmp = tmp.substr(index + 1);
                if (std::regex_search(tmp, miniMatch, classRegex))
                    tmp = miniMatch[1];
            }
            context.push_back(striptease(tmp));
            res.push_back(VecPP(context).join("::"));

        } else if (matches[5].matched) { // lbra
            context.push_back("");

        } else if (matches[6].matched) { // rbra
            context.pop_back();

        }
        std::cout << "num " << context.size() << ", " << VecPP(context).join("::") << std::endl;
        searchStart = matches.suffix().first;
    }
    return res;
}

OpenInclude::OpenInclude(std::string const &file): _file(file)
{
    // getAllFiles(file, _allFile);
    // for (auto const &file : _allFile)
    _allClasses = VecPP(_allClasses) + extractClasses(file);
    // extractClassNames(file, _allClasses);
}
