/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game
*/

#include <random>

#include "Game.hpp"
#include "Global.hpp"

#include "Score.hpp"
#include "Position.hpp"
#include "Drawable.hpp"
#include "Clickable2D.hpp"
#include "TextDrawable.hpp"

const float WhackAMole::Game::WIDTH_MOLE_SPRITE = 190.0f;
const float WhackAMole::Game::HEIGHT_MOLE_SPRITE = 144.0f;
const int WhackAMole::Game::NO_RANDOM_GEN = -1;

const Vector2 WhackAMole::Game::RECSIZE = {WIDTH_MOLE_SPRITE, HEIGHT_MOLE_SPRITE};

const std::map<int, std::vector<Vector2>> WhackAMole::Game::MOLES_ANIM = {
    {(int)MoleStates::SLEEP, {{3, 7}}},
    {(int)MoleStates::WAKE_UP, {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}}},
    {(int)MoleStates::ATTACK, {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {1, 1}, {0, 1}}},
    {(int)MoleStates::DEAD, {{0, 6}, {1, 6}, {2, 6}, {0, 7}, {1, 7}, {2, 7}, {0, 0}}},
    {(int)MoleStates::SPAWN_BOMB, {{0, 0}, {5, 2}, {0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}}},
    {(int)MoleStates::LEAVE_BOMB, {{5, 3}, {4, 3}, {3, 3}, {2, 3}, {1, 3}, {0, 3}, {5, 2}, {0, 0}}},
    {(int)MoleStates::LEAVE, {{4, 0}, {3, 0}, {2, 0}, {1, 0}, {0, 0}}},
    {(int)MoleStates::WAIT, {{4, 0}}},
    {(int)MoleStates::WAIT_BOMB, {{5, 3}}},
    {(int)MoleStates::IMMORTAL_WAIT, {{3, 5}}},
    {(int)MoleStates::IMMORTAL_LEAVE, {{5, 5}, {4, 0}, {3, 0}, {2, 0}, {1, 0}, {0, 0}}},
    {(int)MoleStates::IMMORTAL, {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {0, 5}, {1, 5}, {2, 5}, {3, 5}}},
    {(int)MoleStates::STOP_IMMORTAL, {{4, 5}, {5, 5}, {4, 5}, {5, 0}}},
    {(int)MoleStates::BOMB_EXPLOSION, {{4, 3}, {4, 3}, {4, 3}, {5, 6}, {4, 6}, {3, 6}, {3, 6}, {4, 6}, {5, 6}, {0, 0}}}
};

const std::vector<std::tuple<std::vector<WhackAMole::Game::MoleStates>, int, bool, std::function<void(std::optional<Components::Sprite2DMultiAnim> &, std::optional<Components::TextDrawable> &, std::optional<Components::Score> &)>>> WhackAMole::Game::MOLE_BEHAVIOR = {
    {
        {MoleStates::SLEEP},
        80000,
        false,
        [](
                std::optional<Components::Sprite2DMultiAnim> &e,
                std::optional<Components::TextDrawable> &,
                std::optional<Components::Score> &
            ) {
            e.value().SetState(WhackAMole::Game::IMMORTAL);
        }
    },
    {
        {MoleStates::SLEEP},
        50000,
        false,
        [](
                std::optional<Components::Sprite2DMultiAnim> &e,
                std::optional<Components::TextDrawable> &,
                std::optional<Components::Score> &
            ) {
            e.value().SetState(WhackAMole::Game::SPAWN_BOMB);
        }
    },
    {
        {MoleStates::SLEEP},
        4000,
        false,
        [](
                std::optional<Components::Sprite2DMultiAnim> &e,
                std::optional<Components::TextDrawable> &,
                std::optional<Components::Score> &
            ) {
            e.value().SetState(WhackAMole::Game::WAKE_UP);
        }
    },
    {
        {MoleStates::WAIT},
        2,
        true,
        [](
                std::optional<Components::Sprite2DMultiAnim> &e,
                std::optional<Components::TextDrawable> &p,
                std::optional<Components::Score> &s
            ) {
            e.value().SetState(MoleStates::ATTACK);
            p.value().mess = "-100";
            s.value().setScore(s.value().getScore() - 100);
        }
    },
    {
        {MoleStates::IMMORTAL},
        NO_RANDOM_GEN,
        true,
        [](
                std::optional<Components::Sprite2DMultiAnim> &e,
                std::optional<Components::TextDrawable> &,
                std::optional<Components::Score> &
            ) {
            e.value().SetState(MoleStates::IMMORTAL_WAIT);
            e.value().setTime(GetTime() + 1);
        }
    },
    {
        {MoleStates::STOP_IMMORTAL},
        NO_RANDOM_GEN,
        true,
        [](
                std::optional<Components::Sprite2DMultiAnim> &e,
                std::optional<Components::TextDrawable> &,
                std::optional<Components::Score> &
            ) {
            e.value().SetState(MoleStates::WAIT);
            e.value().setTime(GetTime() + 1);
        }
    },
    {
        {MoleStates::DEAD, MoleStates::LEAVE, MoleStates::LEAVE_BOMB, MoleStates::IMMORTAL_LEAVE},
        NO_RANDOM_GEN,
        true,
        [](
                std::optional<Components::Sprite2DMultiAnim> &e,
                std::optional<Components::TextDrawable> &p,
                std::optional<Components::Score> &
            ) {
            e.value().SetState(MoleStates::SLEEP);
            p.value().mess = "";
        }
    },
    {
        {MoleStates::WAKE_UP},
        NO_RANDOM_GEN,
        true,
        [](
                std::optional<Components::Sprite2DMultiAnim> &e,
                std::optional<Components::TextDrawable> &,
                std::optional<Components::Score> &
            ) {
            e.value().SetState(MoleStates::WAIT);
            e.value().setTime(GetTime() + 1);
        }
    },
    {
        {MoleStates::SPAWN_BOMB},
        NO_RANDOM_GEN,
        true,
        [](
                std::optional<Components::Sprite2DMultiAnim> &e,
                std::optional<Components::TextDrawable> &,
                std::optional<Components::Score> &
            ) {
            e.value().SetState(MoleStates::WAIT_BOMB);
            e.value().setTime(GetTime() + 1);
        }
    },
    {
        {MoleStates::ATTACK, MoleStates::WAIT},
        NO_RANDOM_GEN,
        true,
        [](
                std::optional<Components::Sprite2DMultiAnim> &e,
                std::optional<Components::TextDrawable> &,
                std::optional<Components::Score> &
            ) {
            e.value().SetState(MoleStates::LEAVE);
        }
    },
    {
        {MoleStates::WAIT_BOMB},
        NO_RANDOM_GEN,
        true,
        [](
                std::optional<Components::Sprite2DMultiAnim> &e,
                std::optional<Components::TextDrawable> &,
                std::optional<Components::Score> &
            ) {
            e.value().SetState(MoleStates::LEAVE_BOMB);
        }
    },
    {
        {MoleStates::BOMB_EXPLOSION},
        NO_RANDOM_GEN,
        true,
        [](
                std::optional<Components::Sprite2DMultiAnim> &e,
                std::optional<Components::TextDrawable> &p,
                std::optional<Components::Score> &
            ) {
            e.value().SetState(MoleStates::SLEEP);
            p.value().mess = "";
        }
    },
    {
        {MoleStates::IMMORTAL_WAIT},
        NO_RANDOM_GEN,
        true,
        [](
                std::optional<Components::Sprite2DMultiAnim> &e,
                std::optional<Components::TextDrawable> &,
                std::optional<Components::Score> &
            ) {
            e.value().SetState(MoleStates::IMMORTAL_LEAVE);
        }
    }
};

int WhackAMole::Game::randomgen(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);

    return dis(gen);
}

void WhackAMole::Game::createBackground(Register &r)
{
    Rectangle REC = {0, 50, DEFFAULT_WIDTH, DEFFAULT_HEIGHT};

    r.creatEntity();
    r.emplace_comp(r.currentEntity, Components::Drawable(GAME_BACKGROUND, REC, std::vector<float>{1, 1}));
    r.emplace_comp(r.currentEntity, Components::Positions(0, 0));
}

void WhackAMole::Game::createMole(Register &r, Components::Positions &&pos)
{
    const Rectangle REC = {WIDTH_MOLE_SPRITE * 0, HEIGHT_MOLE_SPRITE * 0, WIDTH_MOLE_SPRITE, HEIGHT_MOLE_SPRITE};

    r.creatEntity();
    r.emplace_comp(r.currentEntity, std::move(pos));
    r.emplace_comp(r.currentEntity, Components::Clickable2D());
    r.emplace_comp(r.currentEntity, Components::Drawable(MOLE_SPRITE, REC, std::vector<float>{0.5, 0.5}));
    r.emplace_comp(r.currentEntity, Components::Sprite2DMultiAnim(RECSIZE, MOLES_ANIM, MoleStates::SLEEP, 0.2f, 11));
    r.emplace_comp(r.currentEntity, Components::TextDrawable("", Components::Positions(pos.x * 0.5, pos.y * 0.5), 20, BLUE));
}

void WhackAMole::Game::createScore(Register &r)
{
    r.creatEntity();
    r.emplace_comp(r.currentEntity, Components::Score("Score", 0, Components::Positions(10, 10)));
}

void WhackAMole::Game::setWhack(Register &r)
{
    auto &rec = r.getComp<Components::Clickable2D>();
    auto &pos = r.getComp<Components::Positions>();
    auto &draw = r.getComp<Components::Drawable>();
    auto &anim = r.getComp<Components::Sprite2DMultiAnim>();
    auto &point = r.getComp<Components::TextDrawable>();
    auto &score = r.getComp<Components::Score>();
    auto scorei = 0;

    for (; !score[scorei].has_value(); ++scorei);
    for (std::size_t i = 0; i < rec.size(); i++) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && rec[i].has_value() && pos[i].has_value() && anim[i].has_value()
        && draw[i].has_value() && draw[i].value().getRect().has_value() && point[i].has_value() && score[scorei].has_value()) {
            Rectangle const hitbox = {
                pos[i].value().x * draw[i].value().scale[0],
                pos[i].value().y * draw[i].value().scale[1],
                draw[i].value().getRect().value().width * draw[i].value().scale[0],
                draw[i].value().getRect().value().height * draw[i].value().scale[1]
            };

            if (!CheckCollisionPointRec(GetMousePosition(), hitbox))
                continue;
            if (anim[i].value().getState() == WAKE_UP || anim[i].value().getState() == WAIT) {
                anim[i].value().SetState(DEAD);
                anim[i].value().setTime(0);
                score[scorei].value().setScore(score[scorei].value().getScore() + 150);
                point[i].value().mess = "+150";
            }
            if (anim[i].value().getState() == SPAWN_BOMB || anim[i].value().getState() == WAIT_BOMB) {
                anim[i].value().SetState(BOMB_EXPLOSION);
                anim[i].value().setTime(0);
                score[scorei].value().setScore(score[scorei].value().getScore() - 300);
                point[i].value().mess = "-300";
            }
            if (anim[i].value().getState() == IMMORTAL || anim[i].value().getState() == IMMORTAL_WAIT) {
                anim[i].value().SetState(STOP_IMMORTAL);
                anim[i].value().setTime(0);
                score[scorei].value().setScore(score[scorei].value().getScore() + 100);
                point[i].value().mess = "+100";
            }
        }
    }
}



void WhackAMole::Game::setStateMole(Register &r)
{
    auto &rec = r.getComp<Components::Sprite2DMultiAnim>();
    auto &point = r.getComp<Components::TextDrawable>();
    auto &score = r.getComp<Components::Score>();
    auto scorei = 0;

    for (; !score[scorei].has_value(); ++scorei);
    for (std::size_t i = 0; i < rec.size(); i++) {
        if (score[scorei].has_value() && rec[i].has_value() && point[i].has_value() && GetTime() >= rec[i].value().getTime()) {
            for (auto &behavior : MOLE_BEHAVIOR) {
                for (auto &s : std::get<0>(behavior)) {
                    if (rec[i].value().getState() == s
                    && (std::get<1>(behavior) == NO_RANDOM_GEN || randomgen(0, std::get<1>(behavior)) == 1)
                    && (!std::get<2>(behavior) || (rec[i].value().isEnded()))) {
                        std::get<3>(behavior)(rec[i], point[i], score[scorei]);
                    }
                }
            }
        }
    }
}