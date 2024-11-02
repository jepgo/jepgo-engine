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
#include "jepengine/exceptions.hpp"
#include "jepmaker/network/INetwork.hpp"
#include "jepmod/exported.hpp"
#include "jepmod/SizedQueue.hpp"

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

using Buffer = std::shared_ptr<std::array<char, jgo::BUFFER_SIZE>>;

class AsioServer: public jgo::IServer {

    public:
        inline AsioServer() : _socket(_context) {
            return;
        }
        void host(jgo::u16 port) override;
        void stop(void) override;
        std::vector<jgo::NetMessage> getAllMessages(void) override;
        void sendToAll(std::vector<jgo::u8> const &data) override;

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

class AsioClient: public jgo::IClient {
    public:
        inline AsioClient(): _socket(_service) {
            return;
        }
        void connect(std::string const &ip, jgo::u16 port) override;
        void stop(void) override;
        void sendToServer(std::vector<jgo::u8> const &data) override;
        std::vector<jgo::u8> getMessage(void) override;

    private:
        void _startReceiving(void);
        void _handleReceive(std::error_code const &err, std::size_t bytes, Buffer buf);
        void _processMessages(void);
        // asio::io_context _context;
        asio::io_service _service;
        udp::socket _socket;
        udp::endpoint _serverEndpoint;
        std::string _buffer; 
};

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
        _messages.emplace_back(
            std::vector<jgo::u8>(message.begin(), message.end()),
            std::make_shared<AsioConnection>(endpoint)
        );
        buf.erase(0, end);
        start = 0;
    }
}

void AsioServer::_handleReceive(std::error_code const &err, std::size_t bytes, Buffer buf)
{
    if (err)
        throw jgo::errors::NetworkError("asio", err.message());

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

void AsioServer::sendToAll(std::vector<jgo::u8> const &vec)
{
    std::string const message(vec.begin(), vec.end());
    std::string const fullMessage = jgo::MAGIC_START + message + jgo::MAGIC_END;

    for (auto const &e : _buffers) {
        _socket.async_send_to(asio::buffer(fullMessage), e.first,
            [this](std::error_code err, std::size_t bytes) -> void {
                return;
            });
    }
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

/* Client */

void AsioClient::connect(std::string const &ip, jgo::u16 port) {
    _serverEndpoint = udp::endpoint(asio::ip::address::from_string(ip), port);
    _socket.open(udp::v4());
    _startReceiving();
}

void AsioClient::_startReceiving(void)
{
    Buffer buf = std::make_shared<std::array<char, jgo::BUFFER_SIZE>>();
    
    std::cout << "waiting" << std::endl;
    _socket.receive_from(asio::buffer(*buf), _serverEndpoint);
    std::cout << "test" << std::endl;
    // _socket.async_receive_from(
    //     asio::buffer(*buf), _serverEndpoint,
    //     [this, buf](std::error_code err, std::size_t bytes) {
    //         std::cout << "test" << std::endl;
    //         _handleReceive(err, bytes, buf);
    //     }
    // );
}

void AsioClient::_handleReceive(std::error_code const &err, std::size_t bytes, Buffer buf)
{
    if (err)
        throw jgo::errors::NetworkError("asio", err.message());

    _buffer.append(reinterpret_cast<char*>(buf->data()), bytes);
    // _processMessages();
    _startReceiving();
}

void AsioClient::_processMessages(void) {
    // std::size_t start = 0;
    // std::size_t end = 0;

    // while (true) {
    //     start = _buffer.find(jgo::MAGIC_START, start);
    //     if (start == std::string::npos)
    //         break;
    //     end = _buffer.find(jgo::MAGIC_END, start + jgo::MAGIC_START.length());
    //     if (end == std::string::npos)
    //         break;
    //     end += jgo::MAGIC_END.length();
    //     std::string message = _buffer.substr(
    //         start + jgo::MAGIC_START.length(),
    //         end - start - jgo::MAGIC_START.length() - jgo::MAGIC_END.length()
    //     );

    //     // Process message as needed (e.g., store it or call a handler)

    //     _buffer.erase(0, end);
    //     start = 0;
    // }
}

void AsioClient::sendToServer(std::vector<jgo::u8> const &data) {
    std::string const message(data.begin(), data.end());
    std::string const fullMessage = jgo::MAGIC_START + message + jgo::MAGIC_END;

    _socket.async_send_to(asio::buffer(fullMessage), _serverEndpoint,
        [](std::error_code err, std::size_t bytes) {
            return;
        });
}

std::vector<jgo::u8> AsioClient::getMessage(void) {
    std::vector<jgo::u8> result;
    
    std::cout << _buffer << std::endl;
    if (_buffer.find(jgo::MAGIC_START) != std::string::npos) {
        std::size_t start = _buffer.find(jgo::MAGIC_START) + jgo::MAGIC_START.length();
        std::size_t end = _buffer.find(jgo::MAGIC_END, start);
        if (end != std::string::npos) {
            std::string message = _buffer.substr(start, end - start);
            result = std::vector<jgo::u8>(message.begin(), message.end());
            _buffer.erase(0, end + jgo::MAGIC_END.length());
        }
    }
    return result;
}

void AsioClient::stop(void) {
    _socket.close();
    _service.stop();
}

exported(std::shared_ptr<jgo::IServer>) getServer(void)
{
    return std::make_shared<AsioServer>();
}

exported(std::shared_ptr<jgo::IClient>) getClient(void)
{
    return std::make_shared<AsioClient>();
}

// int main(void)
// {
//     std::shared_ptr<jgo::IServer> server = std::make_shared<AsioServer>();
//     std::string str;
//     std::string const msg = "Hello client !";
//     std::vector<jgo::u8> const bytes(msg.begin(), msg.end());
    
//     std::thread serverThread([&server]() {
//         server->host(8080);
//     });
//     while (true) {
//         std::this_thread::sleep_for(std::chrono::seconds(1));
//         server->sendToAll(bytes);
//         for (auto const &msg : server->getAllMessages()) {
//             str = std::string(msg.first.begin(), msg.first.end());
//             std::cout << "=> " << str << std::endl;
//         }
//     }
//     server->stop();
//     serverThread.join();
//     return 0;
// }
