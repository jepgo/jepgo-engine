/*
** EPITECH PROJECT, 2024
** whack-a-mole
** File description:
** Sprite2DMultiAnim
*/

#include "Sprite2DMultiAnim.hpp"

Components::Sprite2DMultiAnim::Sprite2DMultiAnim(
        Vector2 const &recSize,
        std::map<int, std::vector<Vector2>> const &states,
        int currentState,
        float time,
        float speed,
        bool loop
    ) :
        _recSize(recSize),
        _states(states),
        _currentState(currentState),
        _time(time),
        _speed(1 / speed),
        _loop(loop),
        _currentFrame(0),
        _ended(false)
{
}

void Components::Sprite2DMultiAnim::SetState(int state)
{
    _currentState = state;
    _currentFrame = 0;
}

Vector2 Components::Sprite2DMultiAnim::updateSpriteLocation()
{
    auto &frames = _states.at(_currentState);

    if ((std::size_t)(_currentFrame + 1) < frames.size())
        _currentFrame += 1;
    else if (_loop)
        _currentFrame = 0;
    else
        _ended = true;
    return frames[_currentFrame];
}

void Components::Sprite2DMultiAnim::setTime(float time)
{
    _time = time;
}

void Components::Sprite2DMultiAnim::setSpeed(float speed)
{
    _speed = 1 / speed;
}

bool Components::Sprite2DMultiAnim::isEnded() const
{
    return _ended;
}

int Components::Sprite2DMultiAnim::getState() const
{
    return _currentState;
}
