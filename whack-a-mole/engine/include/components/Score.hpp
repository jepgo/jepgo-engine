/*
** EPITECH PROJECT, 2024
** whack-a-mole
** File description:
** Score
*/

#ifndef SCORE_HPP_
    #define SCORE_HPP_
    #include <string>
    #include "Position.hpp"

namespace Components {

    class Score {
        public:
            Score(std::string const &title, std::size_t const &score, Positions &&pos) : _title(title), _score(score), _pos(pos) {};
            ~Score() = default;

            void setTitle(std::string const &title);
            std::string const &getTitle() const;
    
            void setScore(std::size_t const &score);
            std::size_t const &getScore() const;

            void setPos(Positions &&pos);
            Positions const &getPosition() const;

        private:
            std::string _title;
            std::size_t _score;
            Positions _pos;
    };

}

#endif /* !SCORE_HPP_ */
