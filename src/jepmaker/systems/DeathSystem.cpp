/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** DeathSystem
*/

#include "jepengine/Client.hpp"
#include "jepmod/exported.hpp"
#include "jepmaker/components/Controllable.hpp"
#include "jepmaker/components/Hitable2D.hpp"
#include "jepmaker/components/Shoot.hpp"
#include "jepmaker/components/Life.hpp"
#include "jepmaker/components/Type.hpp"
#include "jepmaker/components/Colision.hpp"
#include "jepmaker/components/Enemy.hpp"
#include "jepmaker/components/Death.hpp"
#include "jepmaker/components/Points.hpp"
#include "jepmaker/components/Exp.hpp"
#include "jepmaker/components/Move.hpp"
#include "jepmaker/components/SpriteStatus.hpp"
#include "jepmaker/components/Drawable2D.hpp"
#include "jepmaker/components/Message.hpp"

/**
 * @brief Death for the Player
 * 
 * @param game 
 * @param entity 
 */
static void ControlDeath(jgo::Game &game, std::size_t entity)
{
    //game.ecs.removeComponent<Drawable>(entity);
    //game.ecs.removeComponent<Position2D>(entity);
    //game.ecs.removeComponent<Model3D>(entity);
    game.ecs.removeComponent<Controllable>(entity);
    game.ecs.removeComponent<Hitable>(entity);
    game.ecs.removeComponent<Shoot>(entity);
    game.ecs.removeComponent<Move>(entity);
    game.ecs.removeComponent<Sprite_Status>(entity);
    //game.ecs.creatEntity();
    game.ecs.emplaceComp(game.ecs.currentEntity, Message("You are dead...", Position2D(200, 200), 50, 0xffff0000));
}

static void ModulesDeath(jgo::Game &game, std::size_t entity)
{
    //game.ecs.removeComponent<Drawable>(entity);
    //game.ecs.removeComponent<Position2D>(entity);
    //game.ecs.removeComponent<Model3D>(entity);
    game.ecs.removeComponent<Move>(entity);
    game.ecs.removeComponent<Controllable>(entity);
    game.ecs.removeComponent<Hitable>(entity);
}

/**
 * @brief DeletAll
 * 
 * @param game Game
 * @param entity entity player
 */
static void DeletAll(jgo::Game &game, std::size_t entity)
{
    // game.ecs.removeComponent<Drawable>(entity);
    // game.ecs.removeComponent<Position2D>(entity);
    game.ecs.removeComponent<Hitable>(entity);
    //game.ecs.removeComponent<Life>(entity);
    game.ecs.removeComponent<Colision>(entity);
    game.ecs.removeComponent<Move>(entity);
    //game.ecs.removeComponent<Model3D>(entity);
}

/**
 * @brief The Death obj
 * 
 * @param game 
 * @param entity 
 */
static void deathObj(jgo::Game &game, std::size_t entity)
{
    auto &type = game.ecs.getComp<Type>();

    if (type[entity].has_value() == false)
        return;
    if (type[entity].value().getType() == CONTRO)
        return ControlDeath(game, entity);
    if (type[entity].value().getType() == MODULE || type[entity].value().getType() == MODULE_ARM)
        return ModulesDeath(game, entity);
    return DeletAll(game, entity);
}

/**
 * @brief The DeathSystem
 * 
 */
exported(void) jepgoSystem(jgo::Game &game, float time)
{
    std::vector<std::size_t> playerEntity;
    auto &control = game.ecs.getComp<Controllable>();
    auto &life = game.ecs.getComp<Life>();
    auto &enemy = game.ecs.getComp<Enemy>();
    auto &death = game.ecs.getComp<Death>();
    auto &exp = game.ecs.getComp<Exp>();
    auto &points = game.ecs.getComp<Points>();

    for (std::size_t i = 0; i < control.size(); i++) {
        if (control[i].has_value())
            playerEntity.push_back(i);
    }

    for (std::size_t i = 0; i < life.size(); i++) {
        if (life[i].has_value() && life[i].value()._life <= 0)
        {
            deathObj(game, i);
            if (enemy[i].has_value() && death[i].has_value()) {
                for (auto &it : playerEntity) {
                    exp[it].value()._exp += enemy[i].value()._exp;
                    points[it].value()._point += enemy[i].value()._point;
                }
            }
            game.ecs.removeComponent<Death>(i);
            //game.getGraphicLib()->drawImage
        }
    }
}