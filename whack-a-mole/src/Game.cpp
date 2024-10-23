/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game
*/

#include <random>

#include "Game.hpp"
#include "Global.hpp"

#include "Position.hpp"
#include "Drawable.hpp"
#include "Clickable2D.hpp"
#include "Sprite2DMultiAnim.hpp"

const Vector2 WhackAMole::Game::RECSIZE = {WIDTH_MOLE_SPRITE, HEIGHT_MOLE_SPRITE};

const std::map<int, std::vector<Vector2>> WhackAMole::Game::MOLES_ANIM = {
    {(int)MoleStates::SLEEP, {{0, 0}}},
    {(int)MoleStates::WAKE_UP, {{1, 0}, {2, 0}, {3, 0}, {4, 0}}},
    {(int)MoleStates::ATTACK, {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {1, 1}, {0, 1}}},
    {(int)MoleStates::DEAD, {{0, 6}, {1, 6}, {2, 6}, {0, 7}, {1, 7}, {2, 7}, {0, 0}}},
    {(int)MoleStates::SPAWN_BOMB, {{5, 2}, {0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}}},
    {(int)MoleStates::LEAVE_BOMB, {{5, 3}, {4, 3}, {3, 3}, {2, 3}, {1, 3}, {0, 3}, {5, 2}}},
    {(int)MoleStates::LEAVE, {{4, 0}, {3, 0}, {2, 0}, {1, 0}}},
    {(int)MoleStates::WAIT, {{4, 0}}},
    {(int)MoleStates::WAIT_BOMB, {{5, 3}}},
    {(int)MoleStates::IMMORTAL_WAIT, {{3, 5}}},
    {(int)MoleStates::IMMORTAL, {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {0, 5}, {1, 5}, {2, 5}, {3, 5}}},
    {(int)MoleStates::STOP_IMMORTAL, {{4, 5}, {5, 5}, {4, 5}, {5, 0}}}
};

const float WhackAMole::Game::WIDTH_MOLE_SPRITE = 190;
const float WhackAMole::Game::HEIGHT_MOLE_SPRITE = 144;

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
}

void WhackAMole::Game::setWhack(Register &r)
{
    auto &rec = r.getComp<Components::Clickable2D>();
    auto &pos = r.getComp<Components::Positions>();
    auto &draw = r.getComp<Components::Drawable>();
    auto &anim = r.getComp<Components::Sprite2DMultiAnim>();

    for (std::size_t i = 0; i < rec.size(); i++) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && rec[i].has_value() && pos[i].has_value() && anim[i].has_value()
        && draw[i].has_value() && draw[i].value().getRect().has_value()) {
            if ((anim[i].value().getState() == WAKE_UP || anim[i].value().getState() == WAIT)
            && CheckCollisionPointRec(GetMousePosition(), (Rectangle) {
                    pos[i].value().x * draw[i].value().scale[0],
                    pos[i].value().y * draw[i].value().scale[1],
                    draw[i].value().getRect().value().width * draw[i].value().scale[0],
                    draw[i].value().getRect().value().height * draw[i].value().scale[1]
                })) {
                anim[i].value().SetState(DEAD);
                anim[i].value().setTime(0);
            }
        }
    }
}

void WhackAMole::Game::setStateMole(Register &r)
{
    auto &rec = r.getComp<Components::Sprite2DMultiAnim>();

    for (std::size_t i = 0; i < rec.size(); i++) {
        if (rec[i].has_value() && GetTime() >= rec[i].value().getTime()) {
            if (rec[i].value().getState() == SLEEP && randomgen(0, 8000) == 1) {
                rec[i].value().SetState(WAKE_UP);
            } else if (rec[i].value().getState() == SLEEP && randomgen(0, 30000) == 1) {
                rec[i].value().SetState(SPAWN_BOMB);
            } else if (rec[i].value().getState() == SLEEP && randomgen(0, 80000) == 1) {
                rec[i].value().SetState(IMMORTAL);
            } else if (rec[i].value().getState() == IMMORTAL && rec[i].value().isEnded()) {
                rec[i].value().SetState(IMMORTAL_WAIT);
                rec[i].value().setTime(GetTime() + 1);
            } else if (rec[i].value().getState() == IMMORTAL_WAIT && rec[i].value().isEnded()) {
                rec[i].value().SetState(STOP_IMMORTAL);
            } else if (rec[i].value().getState() == STOP_IMMORTAL && rec[i].value().isEnded()) {
                rec[i].value().SetState(WAIT);
                rec[i].value().setTime(GetTime() + 1);
            } else if ((rec[i].value().getState() == LEAVE || rec[i].value().getState() == LEAVE_BOMB) && rec[i].value().isEnded()) {
                rec[i].value().SetState(SLEEP);
            } else if (rec[i].value().getState() == WAKE_UP && rec[i].value().isEnded()) {
                rec[i].value().SetState(WAIT);
                rec[i].value().setTime(GetTime() + 1);
            } else if (rec[i].value().getState() == SPAWN_BOMB && rec[i].value().isEnded()) {
                rec[i].value().SetState(WAIT_BOMB);
                rec[i].value().setTime(GetTime() + 1);
            } else if (rec[i].value().getState() == WAIT && rec[i].value().isEnded() && randomgen(0, 10) == 1) {
                rec[i].value().SetState(ATTACK);
            } else if ((rec[i].value().getState() == ATTACK || rec[i].value().getState() == WAIT) && rec[i].value().isEnded()) {
                rec[i].value().SetState(LEAVE);
            } else if (rec[i].value().getState() == WAIT_BOMB && rec[i].value().isEnded()) {
                rec[i].value().SetState(LEAVE_BOMB);
            }
        }
    }
}