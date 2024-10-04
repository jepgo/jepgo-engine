/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Components
*/

#pragma once

#include <iostream>
#include <optional>
#include <vector>
#include <map>

#include <iomanip>

#include "Raylib.hpp"

class Register;

class Stage {
    public:
        Stage() {};
        ~Stage() {};
    private:

};

class DistanceKm {
    public:
        DistanceKm() {};
        ~DistanceKm() {};
        std::size_t _dist = 0;
};

class Exp {
    public:
        Exp(std::size_t exp) : _exp(exp) {};
        ~Exp() {};
        std::size_t _exp;
};

class Points {
    public:
        Points() {
            _point = 0;
        };
        ~Points() {};
        std::size_t _point;
};


class Lvl {
    public:
        Lvl(std::size_t lvl) : _lvl(lvl) {};
        ~Lvl() {};
        std::size_t _lvl;
};

class Life {
    public:
        Life(int life) : _life(life) {};
        ~Life(){};
        int _life;
    private:
};

class SoundEffect {
    public:
        SoundEffect(std::size_t ind) : _ind(ind) {};
        ~SoundEffect() {};
        void Play(std::vector<Sound> &buffer) {
            PlaySound(buffer[_ind]);
        };
    private:
        std::size_t _ind;
        // sf::Sound _sound;
};

class SoundLoop {
    public:
        SoundLoop(std::size_t ind) : _ind(ind) {
        };
        ~SoundLoop() {
        };
        SoundLoop(const SoundLoop &s) {
            _time = s._time;
            _ind = s._ind;
            std::cout << "copy ctor" << std::endl;
        };
        SoundLoop(SoundLoop &&s) {
            _time = s._time;
            _ind = s._ind;
        };
        SoundLoop &operator=(const SoundLoop &s)
        {
            _time = s._time;
            _ind = s._ind;
            return *this;
        }
        void Play(std::vector<Sound> &buffer) {
            if (!IsSoundPlaying(buffer[_ind]))
                PlaySound(buffer[_ind]);
        };
        void Stop(Sound &sound) {
            StopSound(sound);
        };
        void ChangeSong(std::size_t ind) {
            _ind = ind;
        };
        std::size_t getInd() {return _ind;};
        bool _play = false;
    private:
        float _time = 0;
        std::size_t _ind;
        // sf::Sound _sound;
};


class Positions {
public:
    /**
     * @brief Construct a new Positions object
     *
     * @param x Position x of the object
     * @param y Position y of the Object
     */
    Positions(float x = 0, float y = 0) : x(x), y(y) {}
    ~Positions() {};
    Positions operator+(Positions const &pos) const
    {
        return Positions(this->x + pos.x, this->y + pos.y);
    }
    float x;
    float y;
};

class Move {
public:
    /**
     * @brief Construct a new Move object
     *
     * @param pos The Nex Position of the Object
     */
    Move(Positions const &pos) : _pos(pos) {};
    inline auto getPos() const noexcept -> Positions const &
    {
        return _pos;
    }

private:
    Positions _pos;
};

class DrawKm {
    public:
        DrawKm(Positions &&pos, std::size_t size, Color color) : _pos(pos), _size(size), _color(color) {};
        ~DrawKm() {};
        Positions _pos;
        std::size_t _size;
        Color _color;
};

class DrawPoints {
    public:
        DrawPoints(Positions &&pos, std::size_t size, Color color) : _pos(pos), _size(size), _color(color) {};
        ~DrawPoints() {};
        Positions _pos;
        std::size_t _size;
        Color _color;
};

class DrawLvl {
    public:
        DrawLvl(Positions &&pos, std::size_t size, Color color) : _pos(pos), _size(size), _color(color) {};
        ~DrawLvl() {};
        Positions _pos;
        std::size_t _size;
        Color _color;
};

class DrawReborn {
    public:
        DrawReborn(Positions &&pos, std::size_t size, Color color) : _pos(pos), _size(size), _color(color) {};
        ~DrawReborn() {};
        Positions _pos;
        std::size_t _size;
        Color _color;
};

class Message {
    public:
        Message(std::string mess, Positions &&pos, std::size_t size, Color color) : _mess(mess), _pos(pos), _size(size), _color(color) {};
        ~Message() {};
        std::string _mess;
        Positions _pos;
        std::size_t _size;
        Color _color;
};

class Reborn {
    public:
        Reborn(std::size_t live) : _live(live) {};
        ~Reborn() {};
        std::size_t &getLive() {return _live;};
    private:
        std::size_t _live;
};

class GameLvl {
    public:
        GameLvl(std::size_t lvl) : _lvl(lvl) {};
        ~GameLvl() {};
        std::size_t &GetLvl() {return _lvl;};
    private:
        std::size_t _lvl;
};

class LoopMove {
    public:
        LoopMove(Positions &&pos) : _pos(pos) {};
        ~LoopMove() {};
        Positions _pos;        
};

struct Speed
{
    std::size_t up;
    std::size_t down;
    std::size_t left;
    std::size_t right;
};

enum Direction
{
    DOWN,
    UP,
    RIGHT,
    LEFT,
    MID,
    TIR,
};

class MoveToPlayer {
    public:
        MoveToPlayer(int speed) : _speed(speed) {};
        ~MoveToPlayer() {};
        int _speed;
};

class BombGeneration {
    public:
        BombGeneration(float time, float reset, Positions &&pos, float trac) : _time(time), _reset(reset), _pos(pos), _trac(trac) {};
        ~BombGeneration() {};
        Positions &getPos() {return _pos;};
        float &getTime() {return _time;};
        float &getReset() {return _reset;};
        float &getTrac() {return _trac;};
    private:
        float _time;
        float _reset;
        Positions _pos;
        float _trac;
};

class BombGenerationTime {
    public:
        BombGenerationTime(float time, float during) : _time(time), _during(during) {};
        ~BombGenerationTime() {};
        float getTime() {return _time;};
        float getDuring() {return _during;};
    private:
        float _time;
        float _during;
};

class MoveToPlayerTime {
    public:
        MoveToPlayerTime(float time, float reset) : _time(time), _reset(reset) {};
        ~MoveToPlayerTime() {};
        float _time;
        float _reset;
};

class Velocity {
public:
    Velocity(std::vector<double> const &s) : _speed(s) {}
    ~Velocity() = default;

    // auto press(Direction s) -> void
    // {
    //     auto p = _getValues(s);
    //     p.first = std::clamp<int>(p.first + p.second * _speed[s], -_speed[s], _speed[s]);
    // }

    // auto unpress(Direction s) -> void
    // {
    //     auto p = _getValues(s);
    //     p.first = std::clamp<int>(p.first - p.second * _speed[s], -_speed[s], _speed[s]);
    // }

    inline auto setVel(Vector2 const &v) -> void {
        _vel.x = v.x * _speed[0];
        _vel.y = v.y * _speed[1];
    }

    inline auto getVel() const noexcept -> Positions const &
    {
        return _vel;
    }

private:
    // auto _getValues(Direction s) -> std::pair<float &, float>
    // {
    //     float &ref = (s < Direction::RIGHT) ? _vel.y : _vel.x;
    //     int const mul = !(s % 2) * 2 - 1;

    //     return {ref, mul};
    // }
    std::vector<double> _speed;
    Positions _vel{0, 0};
};

class ScreenLimit{
    public:
        ScreenLimit(int height, int width) : _height(height),  _width(width) {};
        ~ScreenLimit() {};
        int _height;
        int _width;
    private:    

};

class Drawable {
public:
    /**
     * @brief Construct a new Drawable object
     *
     * @param ind The index of the texture in the List of all the texture
     * @param r optional rectangle for The Sprite to Draw
     * @param s A Optional Vector of 2 float for the Scale
     */
    Drawable(std::size_t ind = 0, std::optional<Rectangle> r = std::nullopt, std::vector<float> s = {1, 1}) : index(ind), rect(r)
    {
        if (r.has_value())
            start = r.value().x;
        scale[0] = s[0];
        scale[1] = s[1];
    };
    ~Drawable() {
    };
    void draw(std::vector<Texture2D> &textures, Positions &pos)
    {
        if (rect.has_value()) {
            float a = (rect.value().width * scale[0]);
            float b = (rect.value().height * scale[1]);
            DrawTexturePro(textures[index], rect.value(), Rectangle{pos.x, pos.y, a, b}, {pos.x / 2, pos.y / 2}, 0, WHITE);
        } else {
            DrawTextureEx(textures[index], {pos.x, pos.y}, 0.0f, scale[0], WHITE);
        }
    }
    void change_ind(std::size_t ind) { index = ind; };
    std::size_t getIndex() { return index; };
    std::optional<Rectangle> &getRect() { return rect; };
    int start;

private:
    std::size_t index;
    float scale[2] = { 1, 1 };
    std::optional<Rectangle> rect;
};

class Sprite_Animation {
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

    bool isneg;
    int status;
    int val;
    double reset;
    float t;
    bool deadAnimation;
};

class Short_Animation {
public:
    /**
     * @brief Construct a new Sprite_Animation object
     *
     * @param sta The number of Status for the Sprite
     * @param value The value to be increase for the Sprite
     * @param res The time for the Sprite to be reseted
     * @param dead A Bool to know if the Sprite animation need to be delete after the max status
     */
    Short_Animation(int sta, int value, double res, std::optional<std::size_t> start = std::nullopt)
    {
        status = sta;
        if (value < 0)
            isneg = true;
        else
            isneg = false;
        val = value;
        reset = res;
        t = 0;
        if (start.has_value())
            _start = start.value();
        else
            _start = 0;
    };
    ~Short_Animation() {};

    std::size_t getStart() {return _start;};
    bool isneg;
    int status;
    int val;
    double reset;
    std::size_t _start;
    float t;
};

class Animation2Time {
    public:
        Animation2Time(Short_Animation &&anim1, Short_Animation &&anim2, std::vector<float> const &animsTime, float time)
        : _anim1(anim1), _anim2(anim2), _time(time) {
            _animsTime[0] = animsTime[0];
            _animsTime[1] = animsTime[1];
            _reset = 0;
        };
        ~Animation2Time() {};
        Short_Animation &getAnim1() {return _anim1;};
        Short_Animation &getAnim2() {return _anim2;};
        float getAnimation1Time() {return _animsTime[0];};
        float getAnimation2Time() {return _animsTime[1];};
        float getAnimationTime() {return _time;};
        bool &getstatus() {return _status;};
        float _lastTime = 0;
        float _reset;
    private:
        Short_Animation _anim1;
        Short_Animation _anim2;
        float _animsTime[2];
        float _time;
        bool _status = false;
};

static std::map<int, Direction> const ASSOCIATIVE_KEYS = {
    {KeyboardKey::KEY_UP, DOWN},
    {KeyboardKey::KEY_DOWN, UP},
    {KeyboardKey::KEY_LEFT, RIGHT},
    {KeyboardKey::KEY_RIGHT, LEFT},
    {KeyboardKey::KEY_A, TIR},
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
    int status(Direction s)
    {
        return stat.at(s);
    };
    int mid() { return stat.at(MID); };

private:
    std::map<Direction, int> stat;
};

class Shoot {
public:
    /**
     * @brief Construct a new Shoot object
     * 
     * @param fireRate The time gap between each shot
     * @param dir The direction of the shoot
     * @param decal The decal of the shoot and the obj who are shooting
     */
    Shoot(float fireRate, Direction dir, int decal, std::size_t ind);
    ~Shoot();
    /**
     * @brief Verif if the reset time is repected
     * 
     * @param time The current time
     * @return true: The current time respect the reset timer
     * @return false: The curent time not respect the reset timer
     */
    bool verif(float time);
    void shoot(Register &r, Positions &pos);
    float _fireRate;
    float _time;
    std::size_t _ind;

private:
    Direction _direction;
    int _decal;
};

class Hit {
    public:
        /**
         * @brief Construct a new Hit object
         * 
         * @param entity The entity B who's hit (A is the current get this components)
         */
        Hit(int entity) : _entity(entity) {};
        ~Hit() {};
        /**
         * @brief Get the Entity object
         * 
         * @return int The entity contained by the Hit object
         */
        int GetEntity() {return _entity;};
    private:
        int _entity;

};

enum TYPE {
    BOMB,
    SHIPSHOOT,
    CONTRO,
    COLISION,
    MODULE,
    MINIBOSS,
    NEUTRAL,
};

class Type {
    public:
        Type(TYPE type) : _type(type) {};
        ~Type() {};
        TYPE &getType() {return _type;};
        private:
            TYPE _type;
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
    Explosion(std::size_t ind, int status, int val, double t, std::size_t dmg, TYPE ty, std::optional<Rectangle> r = std::nullopt, std::vector<float> s = {})
    : _dmg(dmg), type(ty), index(ind), rect(r), stat(status), time(t), value(val) {
        if (s.empty())
            return;
        scale[0] = s[0];
        scale[1] = s[1];
        return;
    }
    ~Explosion() {};
    /**
     * @brief The action for the explosion
     *
     * @param r The Registry
     * @param entity The entity to be found
     */
    void explose(Register &r, std::size_t entity);
    std::size_t _dmg;
    TYPE type;
private:
    std::size_t index;
    std::optional<Rectangle> rect;
    float scale[2] = {1, 1};
    int stat;
    double time;
    int value;
};

class Death {
    public:
        Death() {};
        ~Death() {};
};

class Dmg {
    public:
        /**
         * @brief Construct a new Dmg object (ephemeral component)
         * 
         * @param dmg The dmg deal
         */
        Dmg(std::size_t dmg) : _dmg(dmg) {};
        ~Dmg() {};
        std::size_t _dmg;
    private:
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
    Hitable(int w, int h, std::optional<Positions> &&pos = std::nullopt) : width(w), height(h), _pos(pos) {};
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
    bool isHit(Hitable &hit, Positions &him, Positions &me, std::optional<Positions> &himDecal)
    {
        if (_pos.has_value() && himDecal.has_value()) {
            Positions &tmp = _pos.value();
            Positions &tmp2 = himDecal.value();
            return !(me.x + width + tmp.x < him.x + tmp2.x || me.x + tmp.x > him.x + hit.width + tmp2.x || me.y + height + tmp.y < him.y + tmp2.y || me.y + tmp.y > him.y + hit.height + tmp2.y);
        }
        else if (himDecal.has_value()) {
            Positions &tmp2 = himDecal.value();
            return !(me.x + width < him.x + tmp2.x || me.x > him.x + hit.width + tmp2.x || me.y + height < him.y + tmp2.y || me.y > him.y + hit.height + tmp2.y);
        }
        else if (_pos.has_value()) {
            Positions &tmp = _pos.value();
            return !(me.x + width + tmp.x < him.x || me.x + tmp.x > him.x + hit.width || me.y + height + tmp.y < him.y || me.y + tmp.y > him.y + hit.height);
        }
         return !(me.x + width < him.x || me.x > him.x + hit.width || me.y + height < him.y || me.y > him.y + hit.height);
    };
    /**
     * @brief
     *
     * @param entity The entity to be found
     * @param r The Registry
     * @param list The list of all the texture
     */
    void Whenhit(std::size_t entity, Register &r);
    int width;
    int height;
    std::optional<Positions> _pos;

private:
};

class DoDmg {
    public:
        DoDmg(std::size_t dmg) : _dmg(dmg) {};
        ~DoDmg() {};
        std::size_t &getDmg() {return _dmg;};
    private:
        std::size_t _dmg;
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
    bool isCol(Colision &col, Positions const &him, Positions const &me)
    {
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
class Controllable
{
public:
    // void onKeyDown(int key, Velocity &vel);
    // void onKeyUp(int key, Velocity &vel);
    // void updateDirection(Vector2 const &v);
    void Tir(Register &r, Positions &pos, int);
    void moveStatus(std::optional<Sprite_Status> &stat, std::optional<Drawable> &draw, int key);
};

class Invincible {
    public:
        Invincible() {};
        ~Invincible() {};
};

class LvLUp {
    public:
        LvLUp(std::size_t lvl) : _lvl(lvl) {};
        ~LvLUp() {};
        std::size_t _lvl;
};

class InvincibleTime {
    public:
        InvincibleTime(float time, float reset) : _time(time), _reset(reset) {};
        ~InvincibleTime() {};
    float _time;
    float _reset;
};
