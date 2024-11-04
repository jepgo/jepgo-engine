/**
 * JEPGO Project %s - Client
 * 
 * This is a generated file.
 */

#include <iostream>
#include "jepengine/Client.hpp"

/**
 * This will called at the begining of your project.
 */
exported(void) onStart(jgo::Client &game)
{
    std::cout << "Hello world from Client !" << std::endl;
}

/**
 * This will be called each tick.
 */
exported(void) onUpdate(jgo::Client &game)
{
    return;
}
