/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Lobby
*/

#ifndef LOBBY_HPP_
    #define LOBBY_HPP_
    #include <vector>
    #include <asio.hpp>
    #include "Socket.hpp"

using asio::ip::tcp;

/**
 * @struct Lobby
 * @brief a struct that defines a lobby
 * 
 */
struct Lobby
{
    /**
     * @brief id_lobby the id given to the lobby by the server
     * 
     */
    int id_lobby;
    /**
     * @brief players present in the lobby
     * 
     */
    std::vector<Socket *> players;
    /**
     * @brief the name of the lobby
     * 
     */
    std::string lobby_name;
};


#endif /* !LOBBY_HPP_ */
