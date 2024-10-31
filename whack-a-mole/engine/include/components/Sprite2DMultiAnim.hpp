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
    #include <raylib.h>

namespace Components {

    /**
     * @brief Component to handle a multi animation of a 2D sprite
     * 
     */
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
                Vector2 const &recSize,
                std::map<int, std::vector<Vector2>> const &states,
                int currentState,
                float time,
                float speed,
                bool loop = false
            );

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
            void SetState(int state);

            /**
             * @brief Get the State object
             * 
             * @return int The state
             */
            int getState() const;



            /**
             * @brief Update the sprite location
             * 
             * @return Vector2 The new sprite location
             */
            Vector2 updateSpriteLocation();
    

            /**
             * @brief Set the Speed object
             * 
             * @param time The new time
             */
            void setTime(float time);

            void setSpeed(float speed);

            /**
             * @brief If the animation is endend
             * 
             * @return true If it ended
             * @return false otherwise
             */
            bool isEnded() const;

            /**
             * @brief Get the Rec Size object
             * 
             * @return Vector2 The size of an sprite on a spritesheet
             */
            Vector2 getRecSize() const { return _recSize; }

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
            Vector2 _recSize;

            /**
             * @brief The differents states whith this associate animation sprite location
             * 
             */
            std::map<int, std::vector<Vector2>> _states;

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

}

#endif /* !SPRITE2DMULTIANIM */
