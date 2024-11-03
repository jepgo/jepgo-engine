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

/**
 * @brief The KeyDownFunction
 * 
 * The function is here to know if a key was pressed
 * 
 * @param key The list of the key
 * @param find The key to find
 * @return true 
 * @return false 
 */
static bool IsKeyDown(std::vector<jgo::u32> &key, jgo::u32 find)
{
    for (auto &i : key) {
        if (i == find)
            return true;
    }
    return false;
}

/**
 * @brief Get the Direction Vector object
 * 
 * @param vec 
 * @return std::array<float, 2> 
 */
static std::array<float, 2> getDirectionVector(std::vector<jgo::u32> &vec)
{
    std::array<float, 2> res;    

    res[0] = static_cast<float>(IsKeyDown(vec, 262) - IsKeyDown(vec, 263));
    res[1] = static_cast<float>(IsKeyDown(vec, 264) - IsKeyDown(vec, 265));
    return res;
}

/**
 * @brief The Shoot Function
 * 
 * @param game 
 * @param pos 
 * @param _direction 
 * @param _decal 
 */
static void ToShoot(jgo::Game &game, Position2D &pos, Direction &_direction, int &_decal)
{
    if (_direction == LEFT) {
        Game::CreateShipShoot(game, pos + Position2D(0 - _decal, 0));
    }
    else if (_direction == RIGHT) {
        Game::CreateShipShoot(game, pos + Position2D(0 + _decal, 0));
    }
    else if (_direction == UP)
        Game::CreateShipShoot(game, pos + Position2D(0, 0 - _decal));
    else if (_direction == DOWN)
        Game::CreateShipShoot(game, pos + Position2D(0, 0 + _decal));
}

/**
 * @brief The move Status
 * 
 * @param stat 
 * @param draw 
 * @param key 
 */
static void moveStatus(std::optional<Sprite_Status> &stat, std::optional<Drawable> &draw, int key)
{
    if (key != 262 && key != 263 && key != 264 && key != 265)
        return;
    if (stat.has_value() && draw.has_value() && draw.value().getRect().has_value())
        draw.value().getRect().value().x = stat.value().status(ASSOCIATIVE_KEYS.at(key));
};

/**
 * @brief Search a Key
 * 
 * @param key 
 * @param tmp 
 * @return true 
 * @return false 
 */
static bool SearchKey(int key, std::vector<jgo::u32> tmp)
{
    for (auto &t : tmp) {
        if (key == t)
            return true;
    }
    return false;
}

using KMap = std::map<size_t, std::vector<jgo::u32>>;

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
    auto &pos = game.ecs.getComp<Position2D>();
    auto &stat = game.ecs.getComp<Sprite_Status>();
    auto &draw = game.ecs.getComp<Drawable>();
    auto &shoot = game.ecs.getComp<Shoot>();

    auto &keys = std::any_cast<KMap &>(game.storage["keys"]);
    for (std::size_t i = 0; i < control.size(); i++)
    {
        if (!control[i].has_value() || !vel[i].has_value() || !pos[i].has_value())
            continue;
        try {
            auto &key = keys[i];
            if (key.empty())
                continue;
            std::cout << key.size() << std::endl;
            if (SearchKey(65, key) && shoot[i].has_value() && shoot[i].value().verif(game.getTime())) {
                ToShoot(game, pos[i].value(), shoot[i].value()._direction, shoot[i].value()._decal);
                shoot[i].value()._time = game.getTime();
            }
            if (stat[i].has_value() && draw[i].has_value() && !key.empty())
                moveStatus(stat[i], draw[i], key[0]);
            vel[i].value().setVel(getDirectionVector(key));
            game.ecs.emplaceComp(i, Move(vel[i].value().getVel()));
        } catch (std::exception const &) {
            continue;
        }

    }
}
