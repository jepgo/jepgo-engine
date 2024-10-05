/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Jepmodule
*/

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <variant>
#include <iostream>
#include <optional>

#include "Jepmodule.hpp"

using namespace jmod;
using Either = std::variant<Jepmodule::Symbol, std::string>;

static std::vector<Either> lexer(std::string in)
{
    std::string const &modStr = "module";
    std::vector<Either> tail;
    Either head;
    char first;
    std::size_t pos;

    if (in.empty())
        return {};
    if (in.substr(0, modStr.length()) == modStr) {
        tail = lexer(in.substr(modStr.length() + 1));
        tail.insert(tail.begin(), Jepmodule::Symbol::SymModule);
        return tail;
    }
    first = in[0];
    in = in.substr(1);
    switch (first) {
        case '\'':
            pos = in.find_last_of('\'');
            if (pos == std::string::npos)
                throw std::runtime_error("expected quote char.");
            head = in.substr(0, pos);
            in = in.substr(pos + 1);
            break;
        case '"':
            pos = in.find_last_of('"');
            if (pos == std::string::npos)
                throw std::runtime_error("expected double-quote char.");
            head = in.substr(0, pos);
            in = in.substr(pos + 1);
            break;
        case '(':
            head = Jepmodule::Symbol::SymParClose;
            break;
        case ')':
            head = Jepmodule::Symbol::SymParOpen;
            break;
        case ',':
            head = Jepmodule::Symbol::SymSep;
            break;
        case ' ':
        case '\t':
        case '\n':
            return lexer(in);
        default:
            throw std::runtime_error("undefined token");
    }
    tail = lexer(in);
    tail.insert(tail.begin(), head);
    return tail;
}

static std::vector<std::string> parser
(std::vector<Either> const &vec, std::optional<Either> previous)
{
    if (std::holds_alternative<std::string>(vec[0])) {
        if (previous.has_value()
            and std::holds_alternative<Jepmodule::Symbol>(*previous)
            and (
                std::get<Jepmodule::Symbol>(*previous) != Jepmodule::SymParOpen
                or std::get<Jepmodule::Symbol>(*previous) == Jepmodule::SymSep
            ))
            throw std::runtime_error("expected '(' or ',' before string");
        
        /// TODO: do the rest because im lazy

    }
    return {};
}

Jepmodule::Jepmodule(std::string const &path)
{
    std::ifstream const f(("./" + path + ".jmd").c_str());
    std::stringstream buf;
    std::string content;
    std::vector<Either> tokens;

    if (not f.good())
        throw std::runtime_error("file doesnt exists.");
    buf << f.rdbuf();
    content = buf.str();
    tokens = lexer(content);
    std::cout << tokens.size() << std::endl;
}

Jepmodule::~Jepmodule()
{
}
