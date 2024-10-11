/*
** EPITECH PROJECT, 2024
** whack-a-mole
** File description:
** Sprite2DMultiAnim
*/

#include "Sprite2DMultiAnim.hpp"

Components::Sprite2DMultiAnim::Sprite2DMultiAnim(
        std::pair<float, float> recSize,
        std::map<state_t, std::vector<sploc_t>> states,
        state_t currentState,
        double speed,
        bool loop
    ) :
        _recSize(recSize),
        _states(states),
        _currentState(currentState),
        _speed(speed),
        _loop(loop),
        _currentFrame(0),
        _ended(false)
{
}

void Components::Sprite2DMultiAnim::SetState(state_t state)
{
    _currentState = state;
    _currentFrame = 0;
}

Components::Sprite2DMultiAnim::sploc_t Components::Sprite2DMultiAnim::updateSpriteLocation()
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

void Components::Sprite2DMultiAnim::SetSpeed(double speed)
{
    _speed = speed;
}

bool Components::Sprite2DMultiAnim::isEnded() const
{
    return _ended;
}

Components::Sprite2DMultiAnim::state_t Components::Sprite2DMultiAnim::getState() const
{
    return _currentState;
}
