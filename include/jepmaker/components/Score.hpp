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

class Score {
    public:
        Score(std::string const &title, long int const &score, Positions &&pos) : _title(title), _score(score), _pos(pos) {};
        ~Score() = default;

        void setTitle(std::string const &title) { _title = title; }
        std::string const &getTitle() const { return _title; };

        void setScore(long int const &score) { _score = score; }
        long int const &getScore() const { return _score; }

        void setPos(Positions &&pos) { _pos = pos; }
        Positions const &getPosition() const { return _pos; }

    private:
        std::string _title;
        long int _score;
        Positions _pos;
};

#endif /* !SCORE_HPP_ */
