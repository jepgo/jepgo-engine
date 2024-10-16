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
static void retrieveSomething(jgame::Client *client, jgo::Builder &builder)
{
    CBuffer<jgo::u8> buf(sizeof(T));
    jgo::s8 num;

	// builder.display();
    for (std::size_t n = 0; not builder.empty(); ++n) {
        if (n >= client->ecs.entityNbr())
            client->ecs.creatEntity();
        builder.restore<jgo::s8>(num);
        if (num == -1)
            continue;
        buf.fill(builder.toBytes().data());
        client->ecs.emplace_comp(n, buf.cast<T>());
        builder.popFront(sizeof(T));
    }
}
exported(void) receiver(jgame::Client *c, jgo::Builder &b)
{
	jgo::enums::ExternalComponents op;
	b.restore<jgo::u8>(op);

	switch (op) {
		// case jgo::enums::ExternalComponents::Stage:
		// 	retrieveSomething<Stage>(c, b);
		// 	break;
		// case jgo::enums::ExternalComponents::DistanceKm:
		// 	retrieveSomething<DistanceKm>(c, b);
		// 	break;
		// case jgo::enums::ExternalComponents::Exp:
		// 	retrieveSomething<Exp>(c, b);
		// 	break;
		// case jgo::enums::ExternalComponents::Points:
		// 	retrieveSomething<Points>(c, b);
		// 	break;
		// case jgo::enums::ExternalComponents::Lvl:
		// 	retrieveSomething<Lvl>(c, b);
		// 	break;
		// case jgo::enums::ExternalComponents::Life:
		// 	retrieveSomething<Life>(c, b);
		// 	break;
		// case jgo::enums::ExternalComponents::SoundEffect:
		// 	retrieveSomething<SoundEffect>(c, b);
		// 	break;
		// case jgo::enums::ExternalComponents::SoundLoop:
		// 	retrieveSomething<SoundLoop>(c, b);
		// 	break;
		case jgo::enums::ExternalComponents::Positions:
			retrieveSomething<Positions>(c, b);
			break;
		// case jgo::enums::ExternalComponents::Move:
		// 	retrieveSomething<Move>(c, b);
		// 	break;
		// case jgo::enums::ExternalComponents::LoopMove:
		// 	retrieveSomething<LoopMove>(c, b);
		// 	break;
		// case jgo::enums::ExternalComponents::MoveToPlayer:
		// 	retrieveSomething<MoveToPlayer>(c, b);
		// 	break;
		// case jgo::enums::ExternalComponents::BombGeneration:
		// 	retrieveSomething<BombGeneration>(c, b);
		// 	break;
		// case jgo::enums::ExternalComponents::BombGenerationTime:
		// 	retrieveSomething<BombGenerationTime>(c, b);
		// 	break;
		// case jgo::enums::ExternalComponents::MoveToPlayerTime:
		// 	retrieveSomething<MoveToPlayerTime>(c, b);
		// 	break;
		// case jgo::enums::ExternalComponents::Velocity:
		// 	retrieveSomething<Velocity>(c, b);
		// 	break;
		// case jgo::enums::ExternalComponents::ScreenLimit:
		// 	retrieveSomething<ScreenLimit>(c, b);
		// 	break;
		case jgo::enums::ExternalComponents::Drawable:
			retrieveSomething<Drawable>(c, b);
			break;
		// case jgo::enums::ExternalComponents::Sprite_Animation:
		// 	retrieveSomething<Sprite_Animation>(c, b);
		// 	break;
		// case jgo::enums::ExternalComponents::Short_Animation:
		// 	retrieveSomething<Short_Animation>(c, b);
		// 	break;
		// case jgo::enums::ExternalComponents::Animation2Time:
		// 	retrieveSomething<Animation2Time>(c, b);
		// 	break;
		// case jgo::enums::ExternalComponents::Sprite_Status:
		// 	retrieveSomething<Sprite_Status>(c, b);
		// 	break;
		// case jgo::enums::ExternalComponents::Shoot:
		// 	retrieveSomething<Shoot>(c, b);
		// 	break;
		// case jgo::enums::ExternalComponents::Hit:
		// 	retrieveSomething<Hit>(c, b);
		// 	break;
		// case jgo::enums::ExternalComponents::Type:
		// 	retrieveSomething<Type>(c, b);
		// 	break;
		// case jgo::enums::ExternalComponents::Explosion:
		// 	retrieveSomething<Explosion>(c, b);
		// 	break;
		// case jgo::enums::ExternalComponents::Death:
		// 	retrieveSomething<Death>(c, b);
		// 	break;
		// case jgo::enums::ExternalComponents::Dmg:
		// 	retrieveSomething<Dmg>(c, b);
		// 	break;
		// case jgo::enums::ExternalComponents::Hitable:
		// 	retrieveSomething<Hitable>(c, b);
		// 	break;
		// case jgo::enums::ExternalComponents::DoDmg:
		// 	retrieveSomething<DoDmg>(c, b);
		// 	break;
		// case jgo::enums::ExternalComponents::Colision:
		// 	retrieveSomething<Colision>(c, b);
		// 	break;
		// case jgo::enums::ExternalComponents::Controllable:
		// 	retrieveSomething<Controllable>(c, b);
		// 	break;
		// case jgo::enums::ExternalComponents::Invincible:
		// 	retrieveSomething<Invincible>(c, b);
		// 	break;
		// case jgo::enums::ExternalComponents::LvLUp:
		// 	retrieveSomething<LvLUp>(c, b);
		// 	break;
		// case jgo::enums::ExternalComponents::InvincibleTime:
		// 	retrieveSomething<InvincibleTime>(c, b);
		// 	break;
		// default:
		// 	break;
	}
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

