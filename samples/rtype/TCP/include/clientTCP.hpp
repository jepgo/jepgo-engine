/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** clientTCP
*/

#ifndef CLIENTLOGIC_HPP_
	#define CLIENTLOGIC_HPP_
	#include <string>
	#include <queue>
	#include "Socket.hpp"
	#include "IClientTCP.hpp"

using asio::ip::tcp;
 /**
  * @class Client 
  * @brief to construct a client with the protocol tcp
  * 
  */
class Client : public IClientTCP
{
public:
	Client(std::string &host, uint_least16_t port = 4242);
	~Client();
	void sendMessage(const std::string &message) override;
	std::string receiveMessage() override;
	/**
	 * @brief Current lobby client
	 * 
	 */
	int lobby_id;
	/**
	 * @brief Nb players in the current client's lobby
	 * 
	 */
	int nb_players_in_my_lobby;

private:
	/**
	 * @brief socket socket client
	 * 
	 */
	Socket socket;
	/**
	 * @brief data send by the server
	 * 
	 */
	std::string accumulated_data;
};

#endif /* !CLIENTLOGIC_HPP_ */
