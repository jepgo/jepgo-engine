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
    jmod::DLLoader loader(jmod::EasyLife() / "jepgo.network." + lib);

    _server.emplace(loader.getFunc<std::shared_ptr<IServer>>("getServer")());
}
