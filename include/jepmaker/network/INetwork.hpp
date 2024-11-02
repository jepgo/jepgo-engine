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
    // static jgo::u32 const MAGIC_NUMBER = 1769630074;
    // static std::string const MAGIC_START(reinterpret_cast<char const *>(&MAGIC_NUMBER), 4);
    // static std::string const MAGIC_END(reinterpret_cast<char const *>(&MAGIC_NUMBER), 4);
    static std::string const MAGIC_START = "*start*";
    static std::string const MAGIC_END = "*end*";
    static u8 MESSAGE_BYTE = 0x42;
    static u8 COMPONENT_BYTE = 0x84;

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
    using NetMessage = std::pair<
        std::vector<jgo::u8>,
        jgo::ptr<IConnection>
    >;

    class IServer {
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

            /**
             * Send something to everyone.
             */
            virtual void
            sendToAll(std::vector<jgo::u8> const &data) = 0;
            
    };

    class IClient {
        public:
            /**
             * Connect to a server.
             * 
             * It should connect to the specified port with the specified ip.
             */
            virtual void
            connect(std::string const &ip, jgo::u16 port) = 0;

            /**
             * Stop your client.
             * 
             * It should free the ressources (if needed) and stop connections.
             */
            virtual void
            stop(void) = 0;

            /**
             * Send some data to the server.
             */
            virtual void
            sendToServer(std::vector<jgo::u8> const &data) = 0;

            /**
             * Get the most recent server message.
             *
             * If there is no message, it should reteurn an empty vector.
             */
            virtual std::vector<jgo::u8>
            getMessage(void) = 0;
    };
}

