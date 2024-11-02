/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Score
*/

#ifndef SCORE_HPP_
    #define SCORE_HPP_
    #include <string>

class Score {
    public:
        Score(std::string const &title, long int const &score = 0) : _title(title), _score(score) {};
        ~Score() = default;

        void setTitle(std::string const &title) { _title = title; };
        std::string const &getTitle() const { return _title; };

        void setScore(long int const &score) { _score = score; };
        long int const &getScore() const { return _score; };
    private:
        std::string _title;
        long int _score;
};

#endif /* !SCORE_HPP_ */
