/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** IClientTCP
*/

#ifndef ICLIENTTCP_HPP_
#define ICLIENTTCP_HPP_
#include <string>
#include "Socket.hpp"

class IClientTCP {
    public:
        virtual ~IClientTCP() = default;
        virtual void sendMessage(const std::string &message) = 0;
        virtual std::string receiveMessage() = 0;
};

#endif /* !ICLIENTTCP_HPP_ */
