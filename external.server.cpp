/**
 * jepgame generated file (c) 2024
**/

#include <iostream>
#include "jepmod/exported.hpp"
#include "jepgame/gamemaker/Client.hpp"
#include "jepgame/gamemaker/Server.hpp"
#include "jepgame/service/Builder.hpp"
#include "/home/pol/Documents/tek3/cpp/rtype/./build/components/Stamina.hpp"

namespace jgo::enums {
	enum Components {
		StaminaComponent,
	};
}

template <typename T>
static jgo::Builder generateTypeToSend
(jgame::Server *s, jgo::enums::Components c)
{
    Register *reg = (Register *)(reinterpret_cast<char *>(&s->ecs) + 40);
    jgo::Builder build(jgo::enums::FromServer::ApplyExternal);
    auto &elements = reg->getComp<T>();
    CBuffer<jgo::u8> buf(sizeof(T));

    build << static_cast<jgo::u8>(c);
    for (std::size_t n = 0; n < elements.size(); ++n) {
        if (not elements[n]) {
            build << static_cast<jgo::u8>(-1);
            continue;
        }
        build << static_cast<jgo::u8>(0);
        buf.fill(&elements[n].value());
        for (jgo::u8 byte : buf.toBytes())
            build << byte;
    }
    return build;
}

exported(void) sender(jgame::Server *s)
{
	s->sendToAll(generateTypeToSend<StaminaComponent>(
		s,
		jgo::enums::Components::StaminaComponent
	));
}
exported(void) builder(jgame::Server *s)
{
	Register *reg = (Register *)(reinterpret_cast<char *>(&s->ecs) + 40);
	reg->runTimeInsert<StaminaComponent>();
	reg->addRule([](Register::RuleMap &r) {
		std::any_cast<SparseArray<StaminaComponent>&>(
			r[std::type_index(typeid(StaminaComponent))]).add();
	});

}
