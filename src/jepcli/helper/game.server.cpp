/**
 * JEPGO Project %s - Server
 * 
 * This is a generated file.
 */

#include <iostream>
#include "jepengine/Server.hpp"

/**
 * This will called at the begining of your project.
 */
exported(void) onStart(jgo::Server &game)
{
    std::cout << "Hello world from Server !" << std::endl;
}

/**
 * This will be called each tick.
 */
exported(void) onUpdate(jgo::Server &game)
{
    return;
}

/**
 * This will be called each time you have a message from any client.
 */
exported(void) onMessage(jgo::Server &game, jgo::NetMessage const &msg)
{
    return;
}
