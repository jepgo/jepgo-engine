/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** INetwork
*/

#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <string>
#include "jepengine/types.hpp"

namespace jgo {

    static int const BUFFER_SIZE = 1024;
    static std::string const MAGIC_START = "*start*";
    static std::string const MAGIC_END = "*end*";

    /**
     * A connection is a wrapper around a Port and an IP
     */
    class IConnection {
        public:
            /**
             * Get the connection port.
             */
            virtual jgo::u16 getPort(void) const = 0;

            /**
             * Get the IP.
             */
            virtual std::string getIP(void) const = 0;
    };

    /**
     * A Message is a pair of string and Connection.
     */
    using NetMessage = std::pair<std::string, std::shared_ptr<IConnection>>;

    class INetwork {
        public:
            /**
             * Host a server.
             * 
             * It should begin listening on the specified port.
             */
            virtual void
            host(jgo::u16 port) = 0;

            /**
             * Stop your server.
             * 
             * It should free the ressources (if needed) and stop connections.
             */
            virtual void
            stop(void) = 0;

            /**
             * Get all messages.
             * 
             * A message is a duo variable containing a string and a shared
             * pointer to a IConnection.
             */
            virtual std::vector<NetMessage>
            getAllMessages(void) = 0;
            
    };
}

