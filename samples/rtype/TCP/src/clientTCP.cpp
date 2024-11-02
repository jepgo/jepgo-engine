/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** clientTCP
*/

#include <iostream>
#include <map>
#include "clientTCP.hpp"

/**
 * @brief Construct a new Client::Client object
 *
 * @param host address host server
 * @param port port's server
 */
Client::Client(std::string &host, uint_least16_t port)
	: socket(port, host)
{
	lobby_id = 0;
	nb_players_in_my_lobby = 0;
}

/**
 * @brief Destroy the Client::Client object
 *
 */
Client::~Client()
{
	socket.socket.close();
}

/**
 * @brief send Message to the server
 *
 * @param message message you to send to the server
 */
void Client::sendMessage(const std::string &message)
{
	socket.send(message, '\x03');
}

/**
 * @brief receive msg from server
 *
 * @return std::string the message you received from the server
 */
std::string Client::receiveMessage()
{
	return socket.receive('\x03');
}