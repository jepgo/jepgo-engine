/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** serverTCP
*/

#ifndef SERVERTCP_HPP_
#define SERVERTCP_HPP_
#include "IServerTCP.hpp"
#include "Socket.hpp"
#include <iostream>
#include <map>
#include "Lobby.hpp"
#include "serverLogic.hpp"
#include "Acceptor.hpp"

class Server : public IServerTCP
{
public:
    Server(uint_least16_t port_num);
    ~Server() = default;
    std::string receiveMessage(Socket &socket) override;
    void sendMessage(Socket &socket, const std::string &buff) override;
    void accept() override;
    void reactActionsClient(Socket socket);
    /**
     * @brief Create a Lobby
     *
     * @param lobby_name the lobby name
     * @param player author of the lobby
     * @return int lobby id create
     */
    int createLobby(const std::string lobby_name, Socket &player);
    /**
     * @brief join a Looby
     *
     * @param lobby_id the lobby id you want to join
     * @param player socket of the one who want to join the lobby
     * @return true you have successfully joined the lobby
     * @return false you failed to join the lobby
     */
    bool joinLobby(int lobby_id, Socket &player);
    /**
     * @brief leave a lobby
     *
     * @param lobby_id the lobby id you want to leave
     * @param player the player who want to left the lobby
     * @return int lobby id left
     */
    int leaveLobby(int lobby_id, Socket &player);
    /**
     * @brief broadcast to all users in the lobby
     *
     * @param lobby_id the lobby id
     * @param message the message you want to send to all the users in the lobby
     */
    void broadcastLobby(int lobby_id, const std::string &message);

    asio::io_context io_context;
private:
    Acceptor _accept;
    /**
     * @brief all lobbies managed by the server
     * 
     */
    std::map<int, Lobby> lobbies;
    /**
     * @brief mutex used to secure data from different threads created by the server (clients)
     * 
     */
    std::mutex lobbies_mutex;
    /**
     * @brief id auto increment
     * 
     */
    int lobby_id_counter;
};

#endif /* !SERVERTCP_HPP_ */
