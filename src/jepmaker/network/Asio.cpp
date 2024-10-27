/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Asio
*/

#include <asio.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <thread>
#include <chrono>
#include "jepengine/types.hpp"
#include "jepmaker/network/INetwork.hpp"

using udp = asio::ip::udp;

class AsioConnection: public jgo::IConnection {
    public:
        AsioConnection(udp::endpoint const &ep) {
            _endpoint = ep;
        }

        jgo::u16 getPort(void) const override;
        std::string getIP(void) const override;
    private:
        udp::endpoint _endpoint;
};

class AsioServer: public jgo::INetwork {
    using Buffer = std::shared_ptr<std::array<char, jgo::BUFFER_SIZE>>;

    public:
        inline AsioServer() : _socket(_context) {
            return;
        }

        void host(jgo::u16 port);

        void stop(void);

        std::vector<jgo::NetMessage> getAllMessages(void);

    private:
        void _startReceiving(void);
        void _handleReceive(std::error_code const &err, std::size_t bytes, Buffer buf);
        void _processMessage(udp::endpoint const &endpoint);
        asio::io_context _context;
        udp::socket _socket;
        udp::endpoint _endpoint;
        std::map<udp::endpoint, std::string> _buffers;
        std::vector<jgo::NetMessage> _messages;
};

void AsioServer::_processMessage(udp::endpoint const &endpoint)
{
    std::string &buf = _buffers[endpoint];
    std::size_t start = 0;
    std::size_t end = 0;
    std::string message;

    while (true) {
        start = buf.find(jgo::MAGIC_START, start);
        if (start == std::string::npos)
            break;
        end = buf.find(jgo::MAGIC_END, start + jgo::MAGIC_START.length());
        if (end == std::string::npos)
            break;
        end += jgo::MAGIC_END.length();
        message.assign(buf.substr(
            start + jgo::MAGIC_START.length(),
            end - start - jgo::MAGIC_START.length() - jgo::MAGIC_END.length()
        ));
        _messages.emplace_back(message, std::make_shared<AsioConnection>(endpoint));
        buf.erase(0, end);
        start = 0;
    }
}

/* Connection */

jgo::u16 AsioConnection::getPort(void) const
{
    return _endpoint.port();
}

std::string AsioConnection::getIP(void) const
{
    return _endpoint.address().to_string();
}

/* Server */

void AsioServer::_handleReceive(std::error_code const &err, std::size_t bytes, Buffer buf)
{
    if (err)
        throw std::runtime_error(err.message());
    std::string data(reinterpret_cast<char *>(buf->data()), bytes);
    _buffers[_endpoint].append(data);
    _processMessage(_endpoint);
    _startReceiving();
}

void AsioServer::_startReceiving(void)
{
    Buffer buf = std::make_shared<std::array<char, jgo::BUFFER_SIZE>>();
    _socket.async_receive_from(
        asio::buffer(*buf), _endpoint,
        [this, buf](std::error_code err, std::size_t bytes) {
            _handleReceive(err, bytes, buf);
        }
    );
}

void AsioServer::stop(void)
{
    _context.stop();
}

void AsioServer::host(jgo::u16 port)
{
    _socket = udp::socket(_context, udp::endpoint(udp::v4(), port));
    _startReceiving();
    _context.run();
}

std::vector<jgo::NetMessage> AsioServer::getAllMessages(void)
{
    std::vector<jgo::NetMessage> tmp = _messages;

    _messages.clear();
    return tmp;
}

int main(void)
{
    std::shared_ptr<jgo::INetwork> server = std::make_shared<AsioServer>();
    
    std::thread serverThread([&server]() {
        server->host(8080);
    });
    std::cout << "hello" << std::endl;
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        for (auto const &msg : server->getAllMessages())
            std::cout << "=> " << msg.first << std::endl;
    }
    server->stop();
    serverThread.join();
    return 0;
}