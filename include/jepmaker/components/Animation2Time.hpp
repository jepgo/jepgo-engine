/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Animation2Time
*/

#pragma once
#include <vector>
#include "jepmaker/components/ShortAnimation.hpp"

class Animation2Time {
    public:
        Animation2Time(Short_Animation &&anim1, Short_Animation &&anim2, std::vector<float> const &animsTime, float time)
        : _anim1(anim1), _anim2(anim2), _time(time) {
            _animsTime[0] = animsTime[0];
            _animsTime[1] = animsTime[1];
            _reset = 0;
        };
        ~Animation2Time() {};
        Short_Animation &getAnim1() {return _anim1;};
        Short_Animation &getAnim2() {return _anim2;};
        float getAnimation1Time() {return _animsTime[0];};
        float getAnimation2Time() {return _animsTime[1];};
        float getAnimationTime() {return _time;};
        bool &getstatus() {return _status;};
        float _lastTime = 0;
        float _reset;
    private:
        Short_Animation _anim1;
        Short_Animation _anim2;
        float _animsTime[2];
        float _time;
        bool _status = false;
};