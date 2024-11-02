/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** KeySystem
*/


#include "jepmod/exported.hpp"
#include "jepengine/Game.hpp"
#include "jepmaker/components/Colision.hpp"
#include "jepmaker/components/Controllable.hpp"
#include "jepmaker/components/Move.hpp"
#include "jepmaker/components/Shoot.hpp"
#include "jepmaker/components/Position.hpp"
#include "jepmaker/components/Game.hpp"
#include "jepmaker/components/EnumDirection.hpp"

static bool IsKeyDown(std::vector<jgo::u32> &key, jgo::u32 find)
{
    for (auto &i : key) {
        if (i == find)
            return true;
    }
    return false;
}

static std::array<float, 2> getDirectionVector(std::vector<jgo::u32> &vec)
{
    std::array<float, 2> res;    

    res[0] = static_cast<float>(IsKeyDown(vec, 262) - IsKeyDown(vec, 263));
    res[1] = static_cast<float>(IsKeyDown(vec, 264) - IsKeyDown(vec, 265));
    return res;
}

static void ToShoot(jgo::Game &game, Positions &pos, Direction &_direction, int &_decal)
{
    if (_direction == LEFT) {
        Game::CreateShipShoot(game, pos + Positions(0 - _decal, 0));
    }
    else if (_direction == RIGHT) {
        Game::CreateShipShoot(game, pos + Positions(0 + _decal, 0));
    }
    else if (_direction == UP)
        Game::CreateShipShoot(game, pos + Positions(0, 0 - _decal));
    else if (_direction == DOWN)
        Game::CreateShipShoot(game, pos + Positions(0, 0 + _decal));
}

static void moveStatus(std::optional<Sprite_Status> &stat, std::optional<Drawable> &draw, int key)
{
    if (key != 262 && key != 263 && key != 264 && key != 265)
        return;
    if (stat.has_value() && draw.has_value() && draw.value().getRect().has_value())
        draw.value().getRect().value().x = stat.value().status(ASSOCIATIVE_KEYS.at(key));
};

static bool SearchKey(int key, std::vector<jgo::u32> tmp)
{
    for (auto &t : tmp) {
        if (key == t)
            return true;
    }
    return false;
}

/**
 * @brief The Controllable system
 * 
 * @param r The Registry
 * @param key The keyboard key who's pressed
 */
exported(void) jepgoSystem(jgo::Game &game, float &time)
{
    auto &control = game.ecs.getComp<Controllable>();
    auto &vel = game.ecs.getComp<Velocity>();
    auto &pos = game.ecs.getComp<Positions>();
    auto &stat = game.ecs.getComp<Sprite_Status>();
    auto &draw = game.ecs.getComp<Drawable>();
    auto &shoot = game.ecs.getComp<Shoot>();

    std::vector<jgo::u32> &key = std::any_cast<std::vector<jgo::u32>&>(game.storage["keys"]);

    for (std::size_t i = 0; i < control.size(); i++)
    {
        if (!control[i].has_value() || !vel[i].has_value() || !pos[i].has_value())
            continue;
        if (SearchKey(65, key) && shoot[i].has_value() && shoot[i].value().verif(game.getTime())) {
            //SetSoundVolume(sounds[shoot[i].value()._ind], 0.1);
            //PlaySound(sounds[shoot[i].value()._ind]);
            ToShoot(game, pos[i].value(), shoot[i].value()._direction, shoot[i].value()._decal);
            //shoot[i].value().shoot(r, pos[i].value());
            shoot[i].value()._time = game.getTime();
        }
        if (stat[i].has_value() && draw[i].has_value() && !key.empty())
            moveStatus(stat[i], draw[i], key[0]);
        //control[i].value().moveStatus(stat[i], draw[i], key);
        vel[i].value().setVel(getDirectionVector(key));
        game.ecs.emplaceComp(i, Move(vel[i].value().getVel()));
    }
}
