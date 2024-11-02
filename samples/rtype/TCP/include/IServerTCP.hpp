/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** IServerTCP
*/

#ifndef ISERVERTCP_HPP_
#define ISERVERTCP_HPP_
#include <string>
#include "Socket.hpp"

class IServerTCP {
    public:
        virtual ~IServerTCP() = default;
        virtual std::string receiveMessage(Socket &socket) = 0;
        virtual void sendMessage(Socket &socket, const std::string &buff) = 0;
        virtual void accept() = 0;
};

#endif /* !ISERVERTCP_HPP_ */
