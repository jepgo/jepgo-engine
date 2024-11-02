/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Socket
*/

#ifndef SOCKET_HPP_
#define SOCKET_HPP_
#include "ISocket.hpp"
#include <string>
#include <asio.hpp>

using asio::ip::tcp;

class Socket : public ISocket
{
public:
    Socket(int port, std::string &address, asio::io_context io_context = asio::io_context()) : socket(io_context)
    {
        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve(address, std::to_string(port));
        asio::connect(socket, endpoints);
    };
    Socket(asio::io_context io_context = asio::io_context()) : socket(io_context) {};
    Socket(tcp::socket &sock, asio::io_context &io_context) : socket(io_context) {
        socket = std::move(sock);
    };
    ~Socket() = default;
    void send(const std::string &message, char separator = '\n')
    {
        std::string m = message + separator;
        asio::write(socket, asio::buffer(m));
    }
    std::string receive(char separator = '\n')
    {
        std::array<char, 128> buf;
        asio::error_code error;

        if (accumulated_data.empty() == false)
        {
            size_t separator_pos = accumulated_data.find(separator);
            if (separator_pos != std::string::npos)
            {
                std::string message = accumulated_data.substr(0, separator_pos);
                accumulated_data.erase(0, separator_pos + 1);
                return message;
            }
        }

        size_t len = socket.read_some(asio::buffer(buf), error);
        if (error && error != asio::error::would_block)
        {
            throw asio::system_error(error);
        }
        accumulated_data.append(buf.data(), len);
        size_t separator_pos = accumulated_data.find(separator);
        if (separator_pos != std::string::npos)
        {
            std::string message = accumulated_data.substr(0, separator_pos);
            accumulated_data.erase(0, separator_pos + 1);
            return message;
        }
        return "";
    }
    tcp::socket socket;
private:
    std::string accumulated_data;
};

#endif /* !SOCKET_HPP_ */
