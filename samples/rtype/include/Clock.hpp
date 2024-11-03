/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Clock
*/

#ifndef CLOCK_HPP_
    #define CLOCK_HPP_
    #include "raylib.h"

/**
 * @brief This class is a simple clock
 * 
 */
class Clock {
    public:
        /**
         * @brief Construct a new Clock object
         * 
         * @param tick The speed of the tick of clock
         */
        Clock(const double tick) : _tick(1 / tick), _timer(0) {};
        
        /**
         * @brief Destroy the Clock object
         * 
         */
        ~Clock() = default;


        /**
         * @brief Set the Tick object
         * 
         * @param tick The speed of the tick of clock
         */
        void setTick(const double tick) { _tick = 1 / tick; }


        /**
         * @brief Check if the clock is ticked,
         * if it is, reset the timer
         * 
         * @return true if the clock is ticked
         * @return false if the clock is not ticked
         */
        bool isTicked()
        {
            _timer += GetFrameTime();
            if (_timer > _tick) {
                _timer = 0;
                return true;
            }
            return false;
        };


    private:
        /**
         * @brief The speed of the tick of clock
         * 
         */
        double _tick;

        /**
         * @brief The timer of the clock
         * 
         */
        double _timer;
};

#endif /* !CLOCK_HPP_ */