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

static void removeAll(jgo::Game &game, std::size_t entity)
{
    game.ecs.removeEntity(entity);
    game.ecs.emplaceComp(entity, Free());
}

exported(void) jepgoSystem(jgo::Game &game, float time)
{
    std::size_t nbr = 0;
    auto &free = game.ecs.getComp<Free>();
    auto &life = game.ecs.getComp<Life>();
    auto &anim = game.ecs.getComp<Sprite_Animation>();
    auto &draw = game.ecs.getComp<Drawable>();
    auto &Control = game.ecs.getComp<Controllable>();
    auto &tofree = game.ecs.getComp<ToFree>();
    auto &type = game.ecs.getComp<Type>();

    for (std::size_t i = 0; i < life.size(); i++) {
        if (life[i].has_value() && life[i].value()._life <= 0 && type[i].has_value() && type[i].value().getType() != CONTRO)
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

