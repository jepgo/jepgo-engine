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

    static unsigned int const &&maxBufferSize = 128ul;
    using port = std::uint16_t;
    using cppBuffer = std::array<char, maxBufferSize>;
}

namespace jgo {
    using Reply = std::tuple<std::string, udp::endpoint>;
}

