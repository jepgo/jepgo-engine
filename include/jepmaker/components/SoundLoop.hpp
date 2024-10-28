/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** SoundLoop
*/

#pragma once
#include <string>

class SoundLoop {
    public:
        SoundLoop(std::string ind) : _ind(ind) {
        };
        ~SoundLoop() {
        };
        SoundLoop(const SoundLoop &s) {
            _time = s._time;
            _ind = s._ind;
        };
        SoundLoop(SoundLoop &&s) {
            _time = s._time;
            _ind = s._ind;
        };
        SoundLoop &operator=(const SoundLoop &s)
        {
            _time = s._time;
            _ind = s._ind;
            return *this;
        }
        void ChangeSong(std::size_t ind) {
            _ind = ind;
        };
        std::string getInd() {return _ind;};
        bool _play = false;
    private:
        float _time = 0;
        std::string _ind;
};