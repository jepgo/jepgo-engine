/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** FreeSystem
*/

#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"

#include "jepmaker/components/Game.hpp"
#include "jepmaker/components/Position.hpp"
#include "jepmaker/components/SoundLoop.hpp"
#include "jepmaker/components/Move.hpp"
#include "jepmaker/components/Life.hpp"
#include "jepmaker/components/Hitable2D.hpp"
#include "jepmaker/components/Drawable2D.hpp"
#include "jepmaker/components/SpriteAnimation.hpp"
#include "jepmaker/components/SpriteStatus.hpp"
#include "jepmaker/components/Velocity.hpp"
#include "jepmaker/components/Type.hpp"
#include "jepmaker/components/Enemy.hpp"
#include "jepmaker/components/DoDmg.hpp"
#include "jepmaker/components/Explosion.hpp"
#include "jepmaker/components/MoveToPlayer.hpp"
#include "jepmaker/components/MoveToPlayerTime.hpp"
#include "jepmaker/components/ShortAnimation.hpp"
#include "jepmaker/components/Colision.hpp"
#include "jepmaker/components/ScreenLimit.hpp"
#include "jepmaker/components/Shoot.hpp"
#include "jepmaker/components/LoopMove.hpp"
#include "jepmaker/components/Modules.hpp"
#include "jepmaker/components/Controllable.hpp"
#include "jepmaker/components/Reborn.hpp"
#include "jepmaker/components/DrawReborn.hpp"
#include "jepmaker/components/Exp.hpp"
#include "jepmaker/components/Points.hpp"
#include "jepmaker/components/DrawPoints.hpp"
#include "jepmaker/components/Lvl.hpp"
#include "jepmaker/components/DrawLvl.hpp"
#include "jepmaker/components/DistanceKm.hpp"
#include "jepmaker/components/DrawDistanceKm.hpp"
#include "jepmaker/components/Message.hpp"
#include "jepmaker/components/MessageTime.hpp"
#include "jepmaker/components/Invincible.hpp"
#include "jepmaker/components/InvincibleTime.hpp"
#include "jepmaker/components/Hit.hpp"
#include "jepmaker/components/Death.hpp"
#include "jepmaker/components/Dmg.hpp"
#include "jepmaker/components/BombGeneration.hpp"
#include "jepmaker/components/BombGenerationTime.hpp"
#include "jepmaker/components/AutoShoot.hpp"
#include "jepmaker/components/LvlUp.hpp"
#include "jepmaker/components/Animation2Time.hpp"
#include "jepmaker/components/Free.hpp"
#include "jepmaker/components/ToFree.hpp"
#include "jepmaker/components/MoveTo.hpp"

static void removeAll(jgo::Game &game, std::size_t entity)
{
    game.ecs.removeComponent<Positions>(entity);
    game.ecs.removeComponent<Hitable>(entity);
    game.ecs.removeComponent<Move>(entity);
    game.ecs.removeComponent<Sprite_Animation>(entity);
    game.ecs.removeComponent<Invincible>(entity);
    game.ecs.removeComponent<AutoShoot>(entity);
    game.ecs.removeComponent<Module>(entity);
    game.ecs.removeComponent<DoDmg>(entity);
    game.ecs.removeComponent<Dmg>(entity);
    game.ecs.removeComponent<Death>(entity);
    game.ecs.removeComponent<Explosion>(entity);
    game.ecs.removeComponent<Animation2Time>(entity);
    game.ecs.removeComponent<BombGeneration>(entity);
    game.ecs.removeComponent<BombGenerationTime>(entity);
    game.ecs.removeComponent<Drawable>(entity);
    game.ecs.removeComponent<Velocity>(entity);
    game.ecs.removeComponent<Type>(entity);
    game.ecs.removeComponent<Sprite_Status>(entity);
    game.ecs.removeComponent<SoundLoop>(entity);
    game.ecs.removeComponent<Short_Animation>(entity);
    game.ecs.removeComponent<Shoot>(entity);
    game.ecs.removeComponent<ScreenLimit>(entity);
    game.ecs.removeComponent<MoveToPlayerTime>(entity);
    game.ecs.removeComponent<MoveToPlayer>(entity);
    game.ecs.removeComponent<Life>(entity);
    game.ecs.removeComponent<Enemy>(entity);
    game.ecs.removeComponent<MoveToPlayer>(entity);
    game.ecs.removeComponent<MoveToPlayerTime>(entity);
    game.ecs.removeComponent<LoopMove>(entity);
    game.ecs.removeComponent<ModuleArmor>(entity);
    game.ecs.removeComponent<ModuleShoot>(entity);
    game.ecs.removeComponent<Reborn>(entity);
    game.ecs.removeComponent<DrawReborn>(entity);
    game.ecs.removeComponent<Exp>(entity);
    game.ecs.removeComponent<Points>(entity);
    game.ecs.removeComponent<DrawPoints>(entity);
    game.ecs.removeComponent<Lvl>(entity);
    game.ecs.removeComponent<DrawLvl>(entity);
    game.ecs.removeComponent<DistanceKm>(entity);
    game.ecs.removeComponent<DrawKm>(entity);
    game.ecs.removeComponent<InvincibleTime>(entity);
    game.ecs.removeComponent<Hit>(entity);
    game.ecs.removeComponent<Colision>(entity);
    game.ecs.removeComponent<Controllable>(entity);
    game.ecs.removeComponent<LvLUp>(entity);
    game.ecs.removeComponent<ToFree>(entity);
    game.ecs.removeComponent<MoveTo>(entity);
    game.ecs.emplaceComp(entity, Free());
}

exported(void) jepgoSystem(jgo::Game &game, float &time)
{
    std::size_t nbr = 0;
    auto &free = game.ecs.getComp<Free>();
    auto &life = game.ecs.getComp<Life>();
    auto &anim = game.ecs.getComp<Sprite_Animation>();
    auto &draw = game.ecs.getComp<Drawable>();
    auto &Control = game.ecs.getComp<Controllable>();
    auto &tofree = game.ecs.getComp<ToFree>();

    for (std::size_t i = 0; i < life.size(); i++) {
        if (life[i].has_value() && life[i].value()._life <= 0 && Control[i].has_value() == false && draw[i].has_value() == false)
            removeAll(game, i);
        if (tofree[i].has_value())
            removeAll(game, i);
    }
    std::cout << "nbr of entity = " << game.ecs.entityNbr() << std::endl;
    for (std::size_t i = 0; i < free.size(); i++)
        if (free[i].has_value())
            nbr++;
    std::cout << "nbr of free entity = " << nbr << std::endl;
}

