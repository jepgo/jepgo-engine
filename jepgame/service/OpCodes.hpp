/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Enums
*/

#ifndef ENUMS_HPP_
    #define ENUMS_HPP_

    #include "jepgame/toolbox/Either.hpp"
    #include <variant>

namespace jgo::enums {
    enum FromClient {
        Connect = 1,
        Arrows,
    };
    enum FromServer {
        EntityCheck = 1,
        Apply,
    };
    using FromAny = Either<enums::FromClient, enums::FromServer>;
}

#endif /* !ENUMS_HPP_ */
