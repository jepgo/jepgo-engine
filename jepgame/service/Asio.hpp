/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Asio
*/

#pragma once

#include <asio.hpp>

using asio::ip::udp;

namespace asio::ip {
    #include <cstdint>
    #include <array>

    static unsigned int const &&MAX_BUFFER_SIZE = 32768ul;
    using port = std::uint16_t;
    using cppBuffer = std::array<char, MAX_BUFFER_SIZE>;
}

namespace jgo {
    using Reply = std::tuple<std::string, udp::endpoint>;
}

