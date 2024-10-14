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
    "#include <iostream>\n" \
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
        << "(jgame::Server *s, jgo::enums::Components c)\n"
        << "{\n"
        << "    Register *reg = (Register *)(reinterpret_cast<char *>(&s->ecs) + 40);\n"
        << "    jgo::Builder build(jgo::enums::FromServer::ApplyExternal);\n"
        << "    auto &elements = reg->getComp<T>();\n"
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

// std::cout << "inside" << std::endl;
// std::cout << "pointer is " << s << std::endl;
// std::cout << "pointer of ecs is " << &s->ecs << std::endl;
// std::cout << "pointer of ecs + 40 is " << (void *)(reinterpret_cast<char *>(&s->ecs) + 40) << std::endl;
// std::cout << "num is " << ((Register *)(reinterpret_cast<char *>(&s->ecs) + 40))->currentEntity << std::endl;
// std::cout << "size is " << sizeof(jgame::Server) << std::endl;
// std::cout << ((Register *)(reinterpret_cast<char *>(&s->ecs) + 40))->entityNbr() << std::endl;

void FileBuilder::writeServerSender(void)
{
    getGenerationFunction(_stream);
    _stream << "exported(void) sender(jgame::Server *s)\n{\n";
    for (std::string const &s : _classes) {
        _stream << "\ts->sendToAll(generateTypeToSend<" << s
            << ">(\n\t\ts,\n\t\tjgo::enums::Components::"
            << replaceByUnderscore(s)
            << "\n\t));\n";
    }
    _stream << "}" << std::endl << std::endl;
}

void FileBuilder::writeServerBuilder(void)
{
    _stream << "exported(void) builder(jgame::Server *s)\n{\n"
        << "\tRegister *reg = (Register *)"
        << "(reinterpret_cast<char *>(&s->ecs) + 40);\n";
    _stream << std::endl;
    for (std::string const s : _classes) {
        _stream << "\treg->runTimeInsert<" << s << ">();\n";
        _stream << "\treg->addRule([](Register::RuleMap &r) {\n"
            "\t\tstd::any_cast<SparseArray<StaminaComponent>&>(\n"
            "\t\t\tr[std::type_index(typeid(StaminaComponent))]).add();\n"
            "\t});\n";
        _stream << std::endl;
    }
    _stream << "}" << std::endl << std::endl;
}

void FileBuilder::writeClient(void)
{
    /// TODO: later
}

void FileBuilder::writeHeader(void)
{
    _stream << HEADER;
}
