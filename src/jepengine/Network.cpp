/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Network
*/

#include "jepmod/DLLoader.hpp"
#include "jepmod/EasyLife.hpp"
#include "jepengine/Client.hpp"
#include "jepengine/Server.hpp"

void jgo::Server::loadNetworkServer(std::string const &lib)
{
    _loaders["network"].emplace(jmod::EasyLife() / "jepgo.network." + lib);

    _server.emplace(_loaders["network"]->getFunc<jgo::ptr<IServer>>("getServer")());
}

void jgo::Client::loadNetworkClient(std::string const &lib)
{
    _loaders["network"].emplace(jmod::EasyLife() / "jepgo.network." + lib);

    _client.emplace(_loaders["network"]->getFunc<jgo::ptr<IClient>>("getClient")());
}
