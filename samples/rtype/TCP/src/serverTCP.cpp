/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** serverTCP
*/

#include "serverTCP.hpp"
#include "ParsingFile.hpp"
#include <cstddef>
#include <iostream>
#include <array>
#include <sqlite_orm/sqlite_orm.h>
#include <thread>

using namespace sqlite_orm;

auto storage = make_storage("Database/jepgo.db", make_table("USERS",
                                                   make_column("id", &User::id, primary_key().autoincrement()),
                                                   make_column("username", &User::username),
                                                   make_column("password", &User::password),
                                                   make_column("port", &User::port)));

Server::Server(uint_least16_t port_num) : io_context(), _accept(port_num, io_context)
{
}

std::string Server::receiveMessage(Socket &socket)
{
    return socket.receive('\x03');
}

void Server::sendMessage(Socket &socket, const std::string &buff)
{
    socket.send(buff, '\x03');
    return;
}

void Server::accept()
{
    _accept._acceptor.async_accept([this](std::error_code error, tcp::socket socket)
        {
            if (!error)
            {
                std::cout << "Client connected from: " << socket.remote_endpoint() << std::endl;
                std::thread([this, socket = std::move(socket)]() mutable {
                    reactActionsClient(Socket(socket, io_context));
                }).detach();
            }
            else
            {
                std::cerr << "Error accepting connection: " << error.message() << std::endl;
            }
            accept(); 
        }
    );
}

void Server::reactActionsClient(Socket client)
{
    try
    {
        User temp;
        temp.id = 0;

        ParsingFile file("exemple.cfg");
        ParsingPathLevel l;
        l.getAllPathsFromFile(file);
        std::vector<std::string> current_level = l.getListOfPathsLevel(1);

        std::string action = receiveMessage(client);

        while (action != "21" && action != "42")
        {
            sendMessage(client, "409 Invalid choice. Please type R to register or L to login.");
            action = receiveMessage(client);
        }

        bool rl_loop = false;
        while (!rl_loop)
        {
            sendMessage(client, "100 USERNAME=");
            temp.username = receiveMessage(client);
            while (temp.username == "21" || temp.username == "42")
            {
                action = temp.username;
                temp.username = receiveMessage(client);
            }
            std::cout << "Username: " << temp.username << std::endl;

            auto existingUser = storage.get_all<User>(where(c(&User::username) == temp.username));

            sendMessage(client, "110 PASSWORD=");
            std::string pwd = receiveMessage(client);
            while (pwd == "21" || pwd == "42")
            {
                action = temp.username;
                pwd = receiveMessage(client);
            }
            temp.password = std::hash<std::string>{}(pwd);
            std::cout << "Password (hashed): " << temp.password << std::endl;

            temp.port = client.socket.remote_endpoint().port();

            if (action == "21")
            {
                if (!existingUser.empty())
                {
                    sendMessage(client, "420 Username already exists.");
                }
                else
                {
                    storage.insert(temp);
                    std::cout << "New user inserted in DB." << std::endl;
                    rl_loop = true;
                    sendMessage(client, "220 Registration successful!");
                }
            }
            else if (action == "42")
            {
                if (existingUser.empty() || existingUser[0].password != temp.password)
                {
                    sendMessage(client, "410 Username does not exist or Incorrect password.");
                }
                else
                {
                    storage.update_all(set(c(&User::port) = temp.port), where(c(&User::username) == temp.username));
                    std::cout << "User logged in and port updated in DB." << std::endl;
                    rl_loop = true;
                    sendMessage(client, "210 Login successful!");
                }
            }
        }

        while (true)
        {
            std::string command = receiveMessage(client);

            if (command.starts_with("250 CREATE_LOBBY")) {
                std::string lobby_name = command.substr(12);
                int lobby_id = createLobby(lobby_name, client);
                sendMessage(client, "255 Lobby created with ID: " + std::to_string(lobby_id));
                broadcastLobby(lobby_id, "000 Player count: " + std::to_string(lobbies[lobby_id].players.size()));
            }
            else if (command.starts_with("260 JOIN_LOBBY")) {
                int lobby_id = std::stoi(command.substr(15));
                if (joinLobby(lobby_id, client)) {
                    sendMessage(client, "265 Lobby joined.");
                    broadcastLobby(lobby_id, "000 Player count: " + std::to_string(lobbies[lobby_id].players.size()));
                } else {
                    sendMessage(client, "465 Lobby not found.");
                }
            }
            else if (command.starts_with("270 LEAVE_LOBBY")) {
                int lobby_id = std::stoi(command.substr(16));
                leaveLobby(lobby_id, client);
                sendMessage(client, "275 Left lobby with ID: " + std::to_string(lobby_id));
            }
            else if (command == "290 PLAY") {
                sendMessage(client, "200 TEXTURES nb=" + std::to_string(current_level.size()));
                for (const auto &texture : current_level) {
                    sendMessage(client, texture);
                }
                sendMessage(client, "202");
            } 
            else {
                sendMessage(client, "400 Unknown command");
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error while handling client: " << e.what() << std::endl;
    }
    return;
}


int Server::createLobby(const std::string lobby_name, Socket &player)
{
    std::lock_guard<std::mutex> lock(lobbies_mutex);

    Lobby new_lobby;
    new_lobby.id_lobby = lobby_id_counter++;
    new_lobby.lobby_name = lobby_name;
    new_lobby.players.push_back(&player);
    lobbies[new_lobby.id_lobby] = std::move(new_lobby);

    return new_lobby.id_lobby;
}

bool Server::joinLobby(int lobby_id, Socket &player)
{
    std::lock_guard<std::mutex> lock(lobbies_mutex);

    auto which = lobbies.find(lobby_id);
    if (which != lobbies.end()) {
        which->second.players.push_back(&player);
        return true;
    }
    return false;
}

int Server::leaveLobby(int lobby_id, Socket &player)
{
    auto which = lobbies.find(lobby_id);
    if (which != lobbies.end()) {
        auto& players = which->second.players;

        players.erase(std::remove(players.begin(), players.end(), &player), players.end());
        if (players.empty())
            lobbies.erase(which);
        else
            broadcastLobby(lobby_id, "000 Player count: " + std::to_string(lobbies[lobby_id].players.size()));
    }
    return lobby_id;
}

void Server::broadcastLobby(int lobby_id, const std::string &message)
{
    auto it = lobbies.find(lobby_id);
    if (it != lobbies.end()) {
        for (auto player_socket : it->second.players) {
            sendMessage(*player_socket, message);
        }
    }
}


int main(int ac, char **av)
{
    try
    {
        Server server(std::atoi(av[1]));
        server.accept();
        server.io_context.run();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception in main: " << e.what() << std::endl;
    }
    return 0;
}