/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Components
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>

class Register;

class Positions
{
public:
    /**
     * @brief Construct a new Positions object
     * 
     * @param x Position x of the object
     * @param y Position y of the Object
     */
    Positions(int x, int y): x(x), y(y) {}
    ~Positions() {};
    Positions operator+(Positions const &pos) const {
        return Positions(this->x + pos.x, this->y + pos.y);
    }
    int x;
    int y;
};

class Move {
    public:
        /**
         * @brief Construct a new Move object
         * 
         * @param pos The Nex Position of the Object
         */
        Move(Positions const &pos): _pos(pos) {};
        inline auto getPos() const noexcept -> Positions const & {
            return _pos;
        }
    private: Positions _pos;
};

struct Speed
{
    std::size_t up;
    std::size_t down;
    std::size_t left;
    std::size_t right;
};

enum Direction {
    DOWN,
    UP,
    RIGHT,
    LEFT,
    MID,
};

class Velocity {
    public:
        Velocity(std::vector<double> const &s): _speed(s) {}
        ~Velocity() = default;

        auto press(Direction s) -> void {
            auto p = _getValues(s);
            p.first = std::clamp<int>(p.first + p.second * _speed[s], -_speed[s], _speed[s]);
        }

        auto unpress(Direction s) -> void {
            auto p = _getValues(s);
            p.first = std::clamp<int>(p.first - p.second * _speed[s], -_speed[s], _speed[s]);
        }

        inline auto getVel() const noexcept -> Positions const & {
            return _vel;
        }

    private:
        auto _getValues(Direction s) -> std::pair<int &, int> {
            int &ref = (s < Direction::RIGHT) ? _vel.y : _vel.x;
            int const mul = !(s % 2) * 2 - 1;

            return { ref, mul };
        }
        std::vector<double> _speed;
        Positions _vel { 0, 0 };
};

class SoloMove
{
    public:
        SoloMove(Direction dir): direction(dir) {};
        ~SoloMove() {};
    private:
        Direction direction;
};

class Drawable 
{
public:
    /**
     * @brief Construct a new Drawable object
     * 
     * @param ind The index of the texture in the List of all the texture
     * @param r optional rectangle for The Sprite to Draw
     * @param s A Optional Vector of 2 float for the Scale
     */
    Drawable(std::size_t ind, std::optional<sf::IntRect> r = std::nullopt, std::optional<std::vector<float>> s = std::nullopt)
    {
        rect = r;
        index = ind;
        if (r.has_value())
            start = r.value().left;
        if (s.has_value())
            scale = s.value();
        else {
            scale.push_back(1);
            scale.push_back(1);
        }
        sprite.setScale(scale[0], scale[1]);
    };
    ~Drawable() {};
    void draw(sf::RenderWindow &window, sf::Texture &texture, Positions &pos)
    {
        sprite.setTexture(texture);
        if (rect.has_value())
            sprite.setTextureRect(rect.value());
        sprite.setPosition(sf::Vector2f(pos.x, pos.y));
        window.draw(sprite);
    }
    void change_ind(std::size_t ind) { index = ind; };
    std::size_t getIndex() { return index; };
    std::optional<sf::IntRect> &getRect() { return rect; };
    int start;

private:
    sf::Sprite sprite;
    std::size_t index;
    std::vector<float> scale;
    std::optional<sf::IntRect> rect;
};


class Sprite_Animation
{
public:
    /**
     * @brief Construct a new Sprite_Animation object
     * 
     * @param sta The number of Status for the Sprite
     * @param value The value to be increase for the Sprite
     * @param res The time for the Sprite to be reseted
     * @param dead A Bool to know if the Sprite animation need to be delete after the max status
     */
    Sprite_Animation(int sta, int value, double res, std::optional<bool> dead = std::nullopt)
    {
        status = sta;
        if (value < 0)
            isneg = true;
        else
            isneg = false;
        val = value;
        reset = res;
        t = 0;
        if (dead.has_value())
            deadAnimation = true;
        else
            deadAnimation = false;
    };
    ~Sprite_Animation() {};
    void setTime(sf::Time &time)
    {
        t = time.asSeconds();
    };
    bool isneg;
    int status;
    int val;
    double reset;
    float t;
    bool deadAnimation;
};

static std::map<sf::Keyboard::Key, Direction> const ASSOCIATIVE_KEYS = {
    {sf::Keyboard::Up, UP},
    {sf::Keyboard::Down, DOWN},
    {sf::Keyboard::Left, LEFT},
    {sf::Keyboard::Right, RIGHT},
};

class Sprite_Status {
    public:
        /**
         * @brief Construct a new Sprite_Status object
         * 
         * @param s The directions of the Sprite
         */
        Sprite_Status(std::map<Direction, int> s) : stat(s) {};
        ~Sprite_Status() {};
        int status(Direction s) {
            return stat.at(s);
        };
        int mid() {return stat.at(MID);};
    private:
        std::map<Direction, int> stat;
};

class Explosion
{
    public:
        /**
         * @brief Construct a new Explosion object
         * 
         * @param ind The index for the list of Texture
         * @param status The number of the status of the New Sprite
         * @param val The value to be increase for the left Sprite rectangle
         * @param t The time fo the Sprite to be refresh
         * @param r The optional rectangle
         * @param s The optional scale of the Sprite
         */
        Explosion(std::size_t ind, int status, int val, double t, std::optional<sf::IntRect> r = std::nullopt, std::optional<std::vector<float>> s = std::nullopt) : index(ind), rect(r), scale(s), stat(status), time(t) {
            value = val;
        };
        ~Explosion() {};
        /**
         * @brief The action for the explosion
         * 
         * @param r The Registry
         * @param entity The entity to be found
         */
        void explose(Register &r, std::size_t entity);
    private:
        std::size_t index;
        std::optional<sf::IntRect> rect;
        std::optional<std::vector<float>> scale;
        int stat;
        double time;
        int value;
};

class Hitable
{
    public:
        /**
         * @brief Construct a new Hitable object
         * 
         * @param w the width of the object
         * @param h the hight of the object
         */
        Hitable(int w, int h) : width(w), height(h) {};
        ~Hitable() {};
        
        /**
         * @brief Methode to know if 2 hitable object touch each others
         * 
         * @param hit the other Hitable object
         * @param him The position of the second Hitable
         * @param me The Position of this Hitable
         * @return true 
         * @return false 
         */
        bool isHit(Hitable &hit, Positions &him, Positions &me) {
            return !(me.x + width < him.x || me.x > him.x + hit.width || me.y + height < him.y || me.y > him.y + hit.height);
        };
        /**
         * @brief 
         * 
         * @param entity The entity to be found
         * @param r The Registry
         * @param list The list of all the texture
         */
        void Whenhit(std::size_t entity, Register &r, std::vector<sf::Texture> &list);
    private:
        int width;
        int height;
};

class Colision
{
    public:
        /**
         * @brief Construct a new Colision object
         * 
         * @param w the width of the object
         * @param h the hight of the object
         */
        Colision(int w, int h) : width(w), height(h) {};
        ~Colision() {};
        
        /**
         * @brief Methode to know if 2 colision object touch each others
         * 
         * @param hit the other Controllable object
         * @param him The position of the second Hitable
         * @param me The Position of this Hitable
         * @return true 
         * @return false 
         */
        bool isCol(Colision &col, Positions const &him, Positions const &me) {
            return (me.x + width < him.x || me.x > him.x + col.width || me.y + height < him.y || me.y > him.y + col.height);
        }
    private:
        int width;
        int height;
};

/**
 * Component that reacts to an input:
 * 
 * Examples:
 * `Space`  Shoot
 * `Z`      Go UP
 * ...
 */
class Controllable {
    public:
        auto onKeyDown(sf::Keyboard::Key key, Velocity &vel) {
            vel.press(ASSOCIATIVE_KEYS.at(key));
        }

        void onKeyUp(sf::Keyboard::Key key, Velocity &vel) {
            vel.unpress(ASSOCIATIVE_KEYS.at(key));
        }

        void moveStatus(std::optional<Sprite_Status> &stat, std::optional<Drawable> &draw, sf::Keyboard::Key key) {
            if (key != sf::Keyboard::Up && key != sf::Keyboard::Down && key != sf::Keyboard::Right && key != sf::Keyboard::Left)
                return;
            if (stat.has_value() && draw.has_value() && draw.value().getRect().has_value())
                draw.value().getRect().value().left = stat.value().status(ASSOCIATIVE_KEYS.at(key));
        };
};

