/*
** EPITECH PROJECT, 2024
** whack-a-mole
** File description:
** ScoreSystem
*/

#ifndef SCORESYSTEM_HPP_
    #define SCORESYSTEM_HPP
    #include "Register.hpp"

namespace Systems {

    class ScoreSystem {
        public:
            ScoreSystem() {};
            ~ScoreSystem() = default;

            void system(Register &r);
        protected:
        private:
    };

}

#endif /* !SCORESYSTEM_HPP_ */
