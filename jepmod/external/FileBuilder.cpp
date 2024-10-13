/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** FileBuilder
*/

#include <fstream>
#include <iostream>

#include "FileBuilder.hpp"

static std::string const &HEADER =
    "/**\n" \
    " * jepgame generated file (c) 2024\n" \
    "**/\n\n";

static std::string const &INCLUDES =
    "#include \"jepmod/exported.hpp\"\n" \
    "#include \"jepgame/gamemaker/Client.hpp\"\n" \
    "#include \"jepgame/gamemaker/Server.hpp\"\n" \
    "#include \"jepgame/service/Builder.hpp\"\n";

static std::string replaceByUnderscore(std::string const &input)
{
    std::string output = input;
    size_t pos = 0;

    while (true) {
        pos = output.find("::", pos);
        if (pos == std::string::npos)
            break;
        output.replace(pos, 2, "_");
    ++pos;
    }
    return output;
}

void FileBuilder::writeEnum(void)
{
    _stream << "namespace jgo::enums {\n\tenum Components {\n";
    for (std::string const &e : _classes) {
        _stream << "\t\t" + replaceByUnderscore(e) + ",\n";
    }
    _stream << "\t};\n}\n\n";
}

void FileBuilder::writePreprocess(void)
{
    _stream << INCLUDES;
    for (std::string const &f : _files)
        _stream << "#include \"" << f << "\"\n";
    _stream << "\n";
}

static void getGenerationFunction(std::ofstream &stream)
{
    stream << "template <typename T>\n"
        << "static jgo::Builder generateTypeToSend\n"
        << "(jgame::Server &s, jgo::enums::Components c)\n"
        << "{\n"
        << "    jgo::Builder build(jgo::enums::FromServer::ApplyExternal);\n"
        << "    auto &elements = s.ecs.getComp<T>();\n"
        << "    CBuffer<jgo::u8> buf(sizeof(T));\n"
        << "\n"
        << "    build << static_cast<jgo::u8>(c);\n"
        << "    for (std::size_t n = 0; n < elements.size(); ++n) {\n"
        << "        if (not elements[n]) {\n"
        << "            build << static_cast<jgo::u8>(-1);\n"
        << "            continue;\n"
        << "        }\n"
        << "        build << static_cast<jgo::u8>(0);\n"
        << "        buf.fill(&elements[n].value());\n"
        << "        for (jgo::u8 byte : buf.toBytes())\n"
        << "            build << byte;\n"
        << "    }\n"
        << "    return build;\n"
        << "}\n\n";
}

void FileBuilder::writeServer(void)
{
    getGenerationFunction(_stream);
    _stream << "exported(void) entrypoint(jgame::Server &s)\n{\n";
    for (std::string const &s : _classes) {
        _stream << "\ts.sendToAll(generateTypeToSend<" << s
            << ">(\n\t\ts,\n\t\tjgo::enums::Components::"
            << replaceByUnderscore(s)
            << "\n\t));\n";
    }
    _stream << "}\n\n";
}

void FileBuilder::writeClient(void)
{
    /// TODO: later
}

void FileBuilder::writeHeader(void)
{
    _stream << HEADER;
}
