/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Engine
*/

#ifndef ENGINE_HPP_
    #define ENGINE_HPP_

    #include <queue>
    #include "engine/engine.hpp"
    #include "toolbox/Random.hpp"

namespace jgo {
    class Engine {
        public:
            Engine(float moveSystem): sys(moveSystem) {};
            struct _Sys {
                _Sys(float m): move(m) {};
                HitSystem hit;
                DrawSystem draw;
                AnimationSpriteSystem anim;
                MoveSystem move;
            } sys;
            Random rng;
            Register reg;
            std::queue<std::string> actions;
        protected:
        private:
    };
}

#endif /* !ENGINE_HPP_ */
