CMAKE_MINIMUM_REQUIRED(VERSION 3.14) # pi

PROJECT(jepgame)

ADD_LIBRARY(jepgame STATIC
    service/UDP.cpp
    service/Builder.cpp
    service/Connections.cpp
    gamemaker/hardcoded.cpp
    gamemaker/Client.cpp
    gamemaker/Server.cpp
)

TARGET_INCLUDE_DIRECTORIES(jepgame PRIVATE 
    ../ 
    ${raylib_SOURCE_DIR}/src
    ${asio_SOURCE_DIR}/asio/include
)
