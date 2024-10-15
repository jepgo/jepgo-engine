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
    "#include \"jepgame/toolbox/CBuf.hpp\"\n" \
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
    _stream << "namespace jgo::enums {\n\tenum ExternalComponents {\n";
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
        << "(jgame::Server *s, void *ptr, jgo::enums::ExternalComponents c)\n"
        << "{\n"
        << "    std::size_t diff = reinterpret_cast<std::uintptr_t>(ptr)\n"
        << "        - reinterpret_cast<std::uintptr_t>(&s->ecs);\n"
	    << "    Register *reg = (Register *)"
        << "(reinterpret_cast<char *>(&s->ecs) + diff);\n"
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
    _stream << "exported(void) sender(jgame::Server *s, void *ptr)\n{\n";
    for (std::string const &s : _classes) {
        _stream << "\ts->sendToAll(generateTypeToSend<" << s
            << ">(\n\t\ts, ptr,\n\t\tjgo::enums::ExternalComponents::"
            << replaceByUnderscore(s)
            << "\n\t));\n";
    }
    _stream << "}" << std::endl << std::endl;
}

static void getReceiverFunction(std::ofstream &stream)
{
    stream << "template <typename T>\n"
        << "static void retrieveSomething"
        << "(jgame::Client *client, jgo::Builder &builder)\n"
        << "{\n"
        << "    CBuffer<jgo::u8> buf(sizeof(T));\n"
        << "    jgo::s8 num;\n"
        << "\n"
        << "    for (std::size_t n = 0; not builder.empty(); ++n) {\n"
        << "        if (n >= client->ecs.entityNbr())\n"
        << "            client->ecs.creatEntity();\n"
        << "        builder.restore<jgo::s8>(num);\n"
        << "        if (num == -1)\n"
        << "            continue;\n"
        << "        buf.fill(builder.toBytes().data());\n"
        << "        client->ecs.emplace_comp(n, buf.cast<T>());\n"
        << "        builder.popFront(sizeof(T));\n"
        << "    }\n"
        << "}\n";
}

void FileBuilder::writeClientReceiver(void)
{
    getReceiverFunction(_stream);
    _stream << "exported(void) receiver"
        << "(jgame::Client *c, jgo::Builder &b)\n{\n";
    _stream << "\tjgo::enums::ExternalComponents op;\n"
        << "\tb.restore<jgo::u8>(op);\n\n";
    _stream << "\tswitch (op) {\n";
    for (std::string const c : _classes)
        _stream << "\t\tcase jgo::enums::ExternalComponents::"
            << replaceByUnderscore(c) << ":\n"
            << "\t\t\tretrieveSomething<" << c << ">(c, b);\n"
            << "\t\t\tbreak;\n";
    _stream << "\t\tdefault:\n"
        << "\t\t\tbreak;\n\t}\n}" << std::endl << std::endl;
}

void FileBuilder::writeBuilder(void)
{
    _stream << "exported(void) builder(jgame::Server *s, void *ptr)\n{\n"
        << "\tstd::size_t diff = reinterpret_cast<std::uintptr_t>(ptr)\n"
        << "\t\t- reinterpret_cast<std::uintptr_t>(&s->ecs);\n"
        << "\tRegister *reg = (Register *)"
        << "(reinterpret_cast<char *>(&s->ecs) + diff);\n\n";
    _stream << std::endl;
    for (std::string const s : _classes) {
        _stream << "\treg->runTimeInsert<" << s << ">();\n";
        _stream << "\treg->addRule([](Register::RuleMap &r) {\n"
            "\t\tstd::any_cast<SparseArray<" << s << ">&>(\n"
            "\t\t\tr[std::type_index(typeid(" << s << "))]).add();\n"
            "\t});\n";
        _stream << std::endl;
    }
    _stream << "}" << std::endl << std::endl;
}

void FileBuilder::writeHeader(void)
{
    _stream << HEADER;
}
