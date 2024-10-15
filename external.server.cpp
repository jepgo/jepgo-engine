/**
 * jepgame generated file (c) 2024
**/

#include <iostream>
#include "jepmod/exported.hpp"
#include "jepgame/gamemaker/Client.hpp"
#include "jepgame/toolbox/CBuf.hpp"
#include "jepgame/gamemaker/Server.hpp"
#include "jepgame/service/Builder.hpp"

namespace jgo::enums {
	enum ExternalComponents {
		// Stage,
		// DistanceKm,
		// Exp,
		// Points,
		// Lvl,
		// Life,
		// SoundEffect,
		// SoundLoop,
		Positions,
		// Move,
		// LoopMove,
		// MoveToPlayer,
		// BombGeneration,
		// BombGenerationTime,
		// MoveToPlayerTime,
		// Velocity,
		// ScreenLimit,
		Drawable,
		// Sprite_Animation,
		// Short_Animation,
		// Animation2Time,
		// Sprite_Status,
		// Shoot,
		// Hit,
		// Type,
		// Explosion,
		// Death,
		// Dmg,
		// Hitable,
		// DoDmg,
		// Colision,
		// Controllable,
		// Invincible,
		// LvLUp,
		// InvincibleTime,
	};
}

template <typename T>
static jgo::Builder generateTypeToSend
(jgame::Server *s, void *ptr, jgo::enums::ExternalComponents c)
{
    std::size_t diff = reinterpret_cast<std::uintptr_t>(ptr)
        - reinterpret_cast<std::uintptr_t>(&s->ecs);
    Register *reg = (Register *)(reinterpret_cast<char *>(&s->ecs) + diff);
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
	build.display();
    return build;
}

exported(void) sender(jgame::Server *s, void *ptr)
{
	// s->sendToAll(generateTypeToSend<Stage>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::Stage
	// ));
	// s->sendToAll(generateTypeToSend<DistanceKm>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::DistanceKm
	// ));
	// s->sendToAll(generateTypeToSend<Exp>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::Exp
	// ));
	// s->sendToAll(generateTypeToSend<Points>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::Points
	// ));
	// s->sendToAll(generateTypeToSend<Lvl>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::Lvl
	// ));
	// s->sendToAll(generateTypeToSend<Life>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::Life
	// ));
	// s->sendToAll(generateTypeToSend<SoundEffect>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::SoundEffect
	// ));
	// s->sendToAll(generateTypeToSend<SoundLoop>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::SoundLoop
	// ));
	s->sendToAll(generateTypeToSend<Positions>(
		s, ptr,
		jgo::enums::ExternalComponents::Positions
	));
	// s->sendToAll(generateTypeToSend<Move>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::Move
	// ));
	// s->sendToAll(generateTypeToSend<LoopMove>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::LoopMove
	// ));
	// s->sendToAll(generateTypeToSend<MoveToPlayer>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::MoveToPlayer
	// ));
	// s->sendToAll(generateTypeToSend<BombGeneration>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::BombGeneration
	// ));
	// s->sendToAll(generateTypeToSend<BombGenerationTime>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::BombGenerationTime
	// ));
	// s->sendToAll(generateTypeToSend<MoveToPlayerTime>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::MoveToPlayerTime
	// ));
	// s->sendToAll(generateTypeToSend<Velocity>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::Velocity
	// ));
	// s->sendToAll(generateTypeToSend<ScreenLimit>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::ScreenLimit
	// ));
	s->sendToAll(generateTypeToSend<Drawable>(
		s, ptr,
		jgo::enums::ExternalComponents::Drawable
	));
	// s->sendToAll(generateTypeToSend<Sprite_Animation>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::Sprite_Animation
	// ));
	// s->sendToAll(generateTypeToSend<Short_Animation>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::Short_Animation
	// ));
	// s->sendToAll(generateTypeToSend<Animation2Time>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::Animation2Time
	// ));
	// s->sendToAll(generateTypeToSend<Sprite_Status>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::Sprite_Status
	// ));
	// s->sendToAll(generateTypeToSend<Shoot>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::Shoot
	// ));
	// s->sendToAll(generateTypeToSend<Hit>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::Hit
	// ));
	// s->sendToAll(generateTypeToSend<Type>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::Type
	// ));
	// s->sendToAll(generateTypeToSend<Explosion>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::Explosion
	// ));
	// s->sendToAll(generateTypeToSend<Death>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::Death
	// ));
	// s->sendToAll(generateTypeToSend<Dmg>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::Dmg
	// ));
	// s->sendToAll(generateTypeToSend<Hitable>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::Hitable
	// ));
	// s->sendToAll(generateTypeToSend<DoDmg>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::DoDmg
	// ));
	// s->sendToAll(generateTypeToSend<Colision>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::Colision
	// ));
	// s->sendToAll(generateTypeToSend<Controllable>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::Controllable
	// ));
	// s->sendToAll(generateTypeToSend<Invincible>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::Invincible
	// ));
	// s->sendToAll(generateTypeToSend<LvLUp>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::LvLUp
	// ));
	// s->sendToAll(generateTypeToSend<InvincibleTime>(
	// 	s, ptr,
	// 	jgo::enums::ExternalComponents::InvincibleTime
	// ));
}

exported(void) builder(jgame::Server *s, void *ptr)
{
	std::size_t diff = reinterpret_cast<std::uintptr_t>(ptr)
		- reinterpret_cast<std::uintptr_t>(&s->ecs);
	Register *reg = (Register *)(reinterpret_cast<char *>(&s->ecs) + diff);


	// reg->runTimeInsert<Stage>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<Stage>&>(
	// 		r[std::type_index(typeid(Stage))]).add();
	// });

	// reg->runTimeInsert<DistanceKm>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<DistanceKm>&>(
	// 		r[std::type_index(typeid(DistanceKm))]).add();
	// });

	// reg->runTimeInsert<Exp>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<Exp>&>(
	// 		r[std::type_index(typeid(Exp))]).add();
	// });

	// reg->runTimeInsert<Points>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<Points>&>(
	// 		r[std::type_index(typeid(Points))]).add();
	// });

	// reg->runTimeInsert<Lvl>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<Lvl>&>(
	// 		r[std::type_index(typeid(Lvl))]).add();
	// });

	// reg->runTimeInsert<Life>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<Life>&>(
	// 		r[std::type_index(typeid(Life))]).add();
	// });

	// reg->runTimeInsert<SoundEffect>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<SoundEffect>&>(
	// 		r[std::type_index(typeid(SoundEffect))]).add();
	// });

	// reg->runTimeInsert<SoundLoop>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<SoundLoop>&>(
	// 		r[std::type_index(typeid(SoundLoop))]).add();
	// });

	reg->runTimeInsert<Positions>();
	reg->addRule([](Register::RuleMap &r) {
		std::any_cast<SparseArray<Positions>&>(
			r[std::type_index(typeid(Positions))]).add();
	});

	// reg->runTimeInsert<Move>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<Move>&>(
	// 		r[std::type_index(typeid(Move))]).add();
	// });

	// reg->runTimeInsert<LoopMove>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<LoopMove>&>(
	// 		r[std::type_index(typeid(LoopMove))]).add();
	// });

	// reg->runTimeInsert<MoveToPlayer>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<MoveToPlayer>&>(
	// 		r[std::type_index(typeid(MoveToPlayer))]).add();
	// });

	// reg->runTimeInsert<BombGeneration>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<BombGeneration>&>(
	// 		r[std::type_index(typeid(BombGeneration))]).add();
	// });

	// reg->runTimeInsert<BombGenerationTime>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<BombGenerationTime>&>(
	// 		r[std::type_index(typeid(BombGenerationTime))]).add();
	// });

	// reg->runTimeInsert<MoveToPlayerTime>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<MoveToPlayerTime>&>(
	// 		r[std::type_index(typeid(MoveToPlayerTime))]).add();
	// });

	// reg->runTimeInsert<Velocity>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<Velocity>&>(
	// 		r[std::type_index(typeid(Velocity))]).add();
	// });

	// reg->runTimeInsert<ScreenLimit>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<ScreenLimit>&>(
	// 		r[std::type_index(typeid(ScreenLimit))]).add();
	// });

	reg->runTimeInsert<Drawable>();
	reg->addRule([](Register::RuleMap &r) {
		std::any_cast<SparseArray<Drawable>&>(
			r[std::type_index(typeid(Drawable))]).add();
	});

	// reg->runTimeInsert<Sprite_Animation>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<Sprite_Animation>&>(
	// 		r[std::type_index(typeid(Sprite_Animation))]).add();
	// });

	// reg->runTimeInsert<Short_Animation>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<Short_Animation>&>(
	// 		r[std::type_index(typeid(Short_Animation))]).add();
	// });

	// reg->runTimeInsert<Animation2Time>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<Animation2Time>&>(
	// 		r[std::type_index(typeid(Animation2Time))]).add();
	// });

	// reg->runTimeInsert<Sprite_Status>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<Sprite_Status>&>(
	// 		r[std::type_index(typeid(Sprite_Status))]).add();
	// });

	// reg->runTimeInsert<Shoot>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<Shoot>&>(
	// 		r[std::type_index(typeid(Shoot))]).add();
	// });

	// reg->runTimeInsert<Hit>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<Hit>&>(
	// 		r[std::type_index(typeid(Hit))]).add();
	// });

	// reg->runTimeInsert<Type>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<Type>&>(
	// 		r[std::type_index(typeid(Type))]).add();
	// });

	// reg->runTimeInsert<Explosion>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<Explosion>&>(
	// 		r[std::type_index(typeid(Explosion))]).add();
	// });

	// reg->runTimeInsert<Death>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<Death>&>(
	// 		r[std::type_index(typeid(Death))]).add();
	// });

	// reg->runTimeInsert<Dmg>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<Dmg>&>(
	// 		r[std::type_index(typeid(Dmg))]).add();
	// });

	// reg->runTimeInsert<Hitable>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<Hitable>&>(
	// 		r[std::type_index(typeid(Hitable))]).add();
	// });

	// reg->runTimeInsert<DoDmg>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<DoDmg>&>(
	// 		r[std::type_index(typeid(DoDmg))]).add();
	// });

	// reg->runTimeInsert<Colision>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<Colision>&>(
	// 		r[std::type_index(typeid(Colision))]).add();
	// });

	// reg->runTimeInsert<Controllable>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<Controllable>&>(
	// 		r[std::type_index(typeid(Controllable))]).add();
	// });

	// reg->runTimeInsert<Invincible>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<Invincible>&>(
	// 		r[std::type_index(typeid(Invincible))]).add();
	// });

	// reg->runTimeInsert<LvLUp>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<LvLUp>&>(
	// 		r[std::type_index(typeid(LvLUp))]).add();
	// });

	// reg->runTimeInsert<InvincibleTime>();
	// reg->addRule([](Register::RuleMap &r) {
	// 	std::any_cast<SparseArray<InvincibleTime>&>(
	// 		r[std::type_index(typeid(InvincibleTime))]).add();
	// });

}

