/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Acceptor
*/

#ifndef ACCEPTOR_HPP_
#define ACCEPTOR_HPP_
#include "IAcceptor.hpp"

#include <asio.hpp>

using asio::ip::tcp;

class Acceptor : public IAcceptor {
    public:
        Acceptor(uint_least16_t port, asio::io_context &io_context) :  _acceptor(io_context, tcp::endpoint(tcp::v4(), port)) {};
        ~Acceptor() = default;
        tcp::acceptor _acceptor;
    private:
};

#endif /* !ACCEPTOR_HPP_ */
