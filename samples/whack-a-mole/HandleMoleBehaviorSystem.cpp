/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** HandleMoleBehaviorSystem
*/

#include <random>

#include "Global.hpp"
#include "jepengine/Client.hpp"
#include "jepengine/Game.hpp"
#include "jepmod/exported.hpp"

#include "jepmaker/components/Score.hpp"
#include "jepmaker/components/Position.hpp"
#include "jepmaker/components/Drawable2D.hpp"
#include "jepmaker/components/Clickable2D.hpp"
#include "jepmaker/components/Sprite2DMultiAnim.hpp"


static const std::vector<std::tuple<std::vector<WhackAMole::MoleStates>, int, bool, std::function<void(
                    jgo::Game &game,
                    std::optional<Sprite2DMultiAnim> &,
                    std::optional<Score> &
                )>>> MOLE_BEHAVIOR = {
    {
        {WhackAMole::SLEEP},
        2000,
        false,
        [](
                jgo::Game &game,
                std::optional<Sprite2DMultiAnim> &e,
                std::optional<Score> &
            ) {
            e.value().SetState(WhackAMole::IMMORTAL);
        }
    },
    {
        {WhackAMole::SLEEP},
        1000,
        false,
        [](
                jgo::Game &game,
                std::optional<Sprite2DMultiAnim> &e,
                std::optional<Score> &
            ) {
            e.value().SetState(WhackAMole::SPAWN_BOMB);
        }
    },
    {
        {WhackAMole::SLEEP},
        300,
        false,
        [](
                jgo::Game &game,
                std::optional<Sprite2DMultiAnim> &e,
                std::optional<Score> &
            ) {
            e.value().SetState(WhackAMole::WAKE_UP);
        }
    },
    {
        {WhackAMole::WAIT},
        2,
        true,
        [](
                jgo::Game &game,
                std::optional<Sprite2DMultiAnim> &e,
                std::optional<Score> &s
            ) {
            e.value().SetState(WhackAMole::ATTACK);
            s.value().setScore(s.value().getScore() - 100);
        }
    },
    {
        {WhackAMole::IMMORTAL},
        WhackAMole::NO_RANDOM_GEN,
        true,
        [](
                jgo::Game &game,
                std::optional<Sprite2DMultiAnim> &e,
                std::optional<Score> &
            ) {
            e.value().SetState(WhackAMole::IMMORTAL_WAIT);
            e.value().setTime(game.getTime() + 1);
        }
    },
    {
        {WhackAMole::STOP_IMMORTAL},
        WhackAMole::NO_RANDOM_GEN,
        true,
        [](
                jgo::Game &game,
                std::optional<Sprite2DMultiAnim> &e,
                std::optional<Score> &
            ) {
            e.value().SetState(WhackAMole::WAIT);
            e.value().setTime(game.getTime() + 1);
        }
    },
    {
        {WhackAMole::DEAD, WhackAMole::LEAVE, WhackAMole::LEAVE_BOMB, WhackAMole::IMMORTAL_LEAVE},
        WhackAMole::NO_RANDOM_GEN,
        true,
        [](
                jgo::Game &game,
                std::optional<Sprite2DMultiAnim> &e,
                std::optional<Score> &
            ) {
            e.value().SetState(WhackAMole::SLEEP);
        }
    },
    {
        {WhackAMole::WAKE_UP},
        WhackAMole::NO_RANDOM_GEN,
        true,
        [](
                jgo::Game &game,
                std::optional<Sprite2DMultiAnim> &e,
                std::optional<Score> &
            ) {
            e.value().SetState(WhackAMole::WAIT);
            e.value().setTime(game.getTime() + 1);
        }
    },
    {
        {WhackAMole::SPAWN_BOMB},
        WhackAMole::NO_RANDOM_GEN,
        true,
        [](
                jgo::Game &game,
                std::optional<Sprite2DMultiAnim> &e,
                std::optional<Score> &
            ) {
            e.value().SetState(WhackAMole::WAIT_BOMB);
            e.value().setTime(game.getTime() + 1);
        }
    },
    {
        {WhackAMole::ATTACK, WhackAMole::WAIT},
        WhackAMole::NO_RANDOM_GEN,
        true,
        [](
                jgo::Game &game,
                std::optional<Sprite2DMultiAnim> &e,
                std::optional<Score> &
            ) {
            e.value().SetState(WhackAMole::LEAVE);
        }
    },
    {
        {WhackAMole::WAIT_BOMB},
        WhackAMole::NO_RANDOM_GEN,
        true,
        [](
                jgo::Game &game,
                std::optional<Sprite2DMultiAnim> &e,
                std::optional<Score> &
            ) {
            e.value().SetState(WhackAMole::LEAVE_BOMB);
        }
    },
    {
        {WhackAMole::BOMB_EXPLOSION},
        WhackAMole::NO_RANDOM_GEN,
        true,
        [](
                jgo::Game &game,
                std::optional<Sprite2DMultiAnim> &e,
                std::optional<Score> &
            ) {
            e.value().SetState(WhackAMole::SLEEP);
        }
    },
    {
        {WhackAMole::IMMORTAL_WAIT},
        WhackAMole::NO_RANDOM_GEN,
        true,
        [](
                jgo::Game &game,
                std::optional<Sprite2DMultiAnim> &e,
                std::optional<Score> &
            ) {
            e.value().SetState(WhackAMole::IMMORTAL_LEAVE);
        }
    }
};

static int randomgen(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);

    return dis(gen);
}

static void setWhack(jgo::Game &game)
{
    auto &rec = game.ecs.getComp<Clickable2D>();
    auto &pos = game.ecs.getComp<Positions>();
    auto &draw = game.ecs.getComp<Drawable>();
    auto &anim = game.ecs.getComp<Sprite2DMultiAnim>();
    auto &score = game.ecs.getComp<Score>();
    auto scorei = 0;

    for (; !score[scorei].has_value(); ++scorei);
    for (std::size_t i = 0; i < rec.size(); i++) {
        if (game.getGraphicLib().get()->isMousePressing(jgo::MouseButton::LeftClick) && rec[i].has_value() && pos[i].has_value() && anim[i].has_value()
        && draw[i].has_value() && draw[i].value().getRect().has_value() && score[scorei].has_value()) {
            jgo::Rectangle const hitbox = {
                pos[i].value().x * draw[i].value().getScale()[0],
                pos[i].value().y * draw[i].value().getScale()[1],
                draw[i].value().getRect().value().width * draw[i].value().getScale()[0],
                draw[i].value().getRect().value().height * draw[i].value().getScale()[1]
            };

            if (!game.getGraphicLib().get()->CheckCollisionPointRectangle(game.getGraphicLib().get()->getMousePos(), hitbox))
                continue;
            if (anim[i].value().getState() == WhackAMole::WAKE_UP || anim[i].value().getState() == WhackAMole::WAIT) {
                anim[i].value().SetState(WhackAMole::DEAD);
                anim[i].value().setTime(0);
                score[scorei].value().setScore(score[scorei].value().getScore() + 150);
            }
            if (anim[i].value().getState() == WhackAMole::SPAWN_BOMB || anim[i].value().getState() == WhackAMole::WAIT_BOMB) {
                anim[i].value().SetState(WhackAMole::BOMB_EXPLOSION);
                anim[i].value().setTime(0);
                score[scorei].value().setScore(score[scorei].value().getScore() - 300);
            }
            if (anim[i].value().getState() == WhackAMole::IMMORTAL || anim[i].value().getState() == WhackAMole::IMMORTAL_WAIT) {
                anim[i].value().SetState(WhackAMole::STOP_IMMORTAL);
                anim[i].value().setTime(0);
                score[scorei].value().setScore(score[scorei].value().getScore() + 100);
            }
        }
    }
}

static void setStateMole(jgo::Game &game)
{
    auto &rec = game.ecs.getComp<Sprite2DMultiAnim>();
    auto &score = game.ecs.getComp<Score>();
    auto scorei = 0;

    for (; !score[scorei].has_value(); ++scorei);
    for (std::size_t i = 0; i < rec.size(); i++) {
        if (score[scorei].has_value() && rec[i].has_value() && game.getTime() >= rec[i].value().getTime()) {
            for (auto &behavior : MOLE_BEHAVIOR) {
                for (auto &s : std::get<0>(behavior)) {
                    if (rec[i].value().getState() == s
                    && (std::get<1>(behavior) == WhackAMole::NO_RANDOM_GEN || randomgen(0, std::get<1>(behavior)) == 1)
                    && (!std::get<2>(behavior) || (rec[i].value().isEnded()))) {
                        std::get<3>(behavior)(game, rec[i], score[scorei]);
                    }
                }
            }
        }
    }
}

exported(void) jepgoSystem(jgo::Game &game, float &t)
{
    setStateMole(game);
    setWhack(game);
}
