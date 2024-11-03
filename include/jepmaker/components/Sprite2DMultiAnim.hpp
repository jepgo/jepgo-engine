/*
** EPITECH PROJECT, 2024
** whack-a-mole
** File description:
** Sprite2DMultiAnim
*/

#ifndef SPRITE2DMULTIANIM
    #define SPRITE2DMULTIANIM
    #include <map>
    #include <vector>
    #include <utility>
    #include "jepengine/types.hpp"

class Sprite2DMultiAnim {
    public:
        /**
         * @brief Construct a new Sprite 2 D Multi Anim object
         * 
         * @param recSize The size of an sprite on a spritesheet
         * @param states The differents states whith this associate animation sprite location
         * @param currentState The current state
         * @param time The time of the update
         * @param speed The speed of the update
         * @param loop If at the end of an animation, the animation must be reset
         */
        Sprite2DMultiAnim(
            jgo::Vector2 const &recSize,
            std::map<int, std::vector<jgo::Vector2>> const &states,
            int currentState,
            float time,
            float speed,
            bool loop = false
        )  :
            _recSize(recSize),
            _states(states),
            _currentState(currentState),
            _time(time),
            _speed(1 / speed),
            _loop(loop),
            _currentFrame(0),
            _ended(false)
        {};

        /**
         * @brief Destroy the Sprite 2 D Multi Anim object
         * 
         */
        ~Sprite2DMultiAnim() = default;



        /**
         * @brief Set the State object
         * 
         * @param state The new current state
         */
        void SetState(int state)
        {
            _currentState = state;
            _currentFrame = 0;
            _ended = false;
        }


        /**
         * @brief Get the State object
         * 
         * @return int The state
         */
        int getState() const { return _currentState; }



        /**
         * @brief Update the sprite location
         * 
         * @return Vector2 The new sprite location
         */
        jgo::Vector2 updateSpriteLocation()
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


        /**
         * @brief Set the Speed object
         * 
         * @param time The new time
         */
        void setTime(float time) { _time = time; }

        void setSpeed(float speed) { _speed = 1 / speed; }

        /**
         * @brief If the animation is endend
         * 
         * @return true If it ended
         * @return false otherwise
         */
        bool isEnded() const { return _ended; }

        /**
         * @brief Get the Rec Size object
         * 
         * @return Vector2 The size of an sprite on a spritesheet
         */
        jgo::Vector2 getRecSize() const { return _recSize; }

        /**
         * @brief Get the Time object
         * 
         * @return float The time of the update
         */
        float getTime() const { return _time; }

        /**
         * @brief Get the Speed object
         * 
         * @return float The speed
         */
        float getSpeed() const { return _speed; }

    private:
        /**
         * @brief The size of an sprite on a spritesheet
         * 
         */
        jgo::Vector2 _recSize;

        /**
         * @brief The differents states whith this associate animation sprite location
         * 
         */
        std::map<int, std::vector<jgo::Vector2>> _states;

        /**
         * @brief The current state
         * 
         */
        int _currentState;

        /**
         * @brief The time of the update
         * 
         */
        float _time;

        /**
         * @brief The speed of the update
         * 
         */
        float _speed;

        /**
         * @brief If at the end of an animation, the animation must be reset
         * 
         */
        bool _loop;

        /**
         * @brief The current frame
         * 
         */
        int _currentFrame;

        /**
         * @brief If the animation is endend
         * 
         */
        bool _ended;
};

#endif /* !SPRITE2DMULTIANIM */
