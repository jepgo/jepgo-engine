/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Fedora]
** File description:
** Message
*/

#pragma once
#include "jepengine/Client.hpp"
#include "jepmaker/components/Position.hpp"

class Message {
    public:
        Message(std::string mess, Positions &&pos, std::size_t size, jgo::u32 color) : _mess(mess), _pos(pos), _size(size), _color(color) {};
        ~Message() {};
        std::string _mess;
        Positions _pos;
        std::size_t _size;
        jgo::u32 _color;
};