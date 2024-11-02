/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** server
*/

#ifndef SERVERLOGIC_HPP_
#define SERVERLOGIC_HPP_
#include <string>

/**
 * @struct User
 * @brief user struct for sqlite orm
 *
 */
struct User
{
    /**
     * @brief user id
     *
     */
    int id;
    /**
     * @brief user's username
     *
     */
    std::string username;
    /**
     * @brief user's password
     *
     */
    std::size_t password;
    /**
     * @brief user port in server
     *
     */
    int port;
};

#endif /* !SERVERLOGIC_HPP_ */
