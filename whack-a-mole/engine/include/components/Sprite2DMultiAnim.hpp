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

namespace Components {

    /**
     * @brief Component to handle a multi animation of a 2D sprite
     * 
     */
    class Sprite2DMultiAnim {
        public:
            /**
             * @brief A state
             * 
             */
            typedef int state_t;
            /**
             * @brief A `x`, `y` location of a sprite in an spritesheet
             * 
             */
            typedef std::pair<int, int> sploc_t;

            /**
             * @brief Construct a new Sprite 2 D Multi Anim object
             * 
             * @param recSize The size of an sprite on a spritesheet
             * @param states The differents states whith this associate animation sprite location
             * @param currentState The current state
             * @param speed The speed of the update
             * @param loop If at the end of an animation, the animation must be reset
             */
            Sprite2DMultiAnim(
                std::pair<float, float> recSize,
                std::map<state_t, std::vector<sploc_t>> states,
                state_t currentState,
                double speed,
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
            void SetState(state_t state);

            /**
             * @brief Get the State object
             * 
             * @return state_t The state
             */
            state_t getState() const;



            /**
             * @brief Update the sprite location
             * 
             * @return sploc_t The new sprite location
             */
            sploc_t updateSpriteLocation();
    

            /**
             * @brief Set the Speed object
             * 
             * @param speed The new speed
             */
            void SetSpeed(double speed);

            /**
             * @brief If the animation is endend
             * 
             * @return true If it ended
             * @return false otherwise
             */
            bool isEnded() const;

        private:
            /**
             * @brief The size of an sprite on a spritesheet
             * 
             */
            std::pair<float, float> _recSize;

            /**
             * @brief The differents states whith this associate animation sprite location
             * 
             */
            std::map<state_t, std::vector<sploc_t>> _states;

            /**
             * @brief The current state
             * 
             */
            state_t _currentState;

            /**
             * @brief The speed of the update
             * 
             */
            double _speed;

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
