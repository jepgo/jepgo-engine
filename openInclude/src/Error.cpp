/*
** EPITECH PROJECT, 2024
** ImageTranslation [WSL: Fedora]
** File description:
** Error
*/

#include "Error.hpp"

/**
 * @brief Destroy the Error:: Error object
 * 
 */
Error::~Error()
{

}

/**
 * @brief The message Error returned
 * 
 * @return const char* 
 */
const char *Error::what() const noexcept
{
    return _msg.c_str();
}
