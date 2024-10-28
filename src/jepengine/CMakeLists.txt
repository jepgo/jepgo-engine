CMAKE_MINIMUM_REQUIRED(VERSION 3.14) # pi

PROJECT(jepengine)

ADD_LIBRARY(jepengine STATIC
    Register.cpp
	Game.cpp
)

TARGET_INCLUDE_DIRECTORIES(jepengine PRIVATE ../../include)

ADD_CUSTOM_COMMAND(TARGET jepengine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "$<TARGET_FILE:jepengine>"
    "${CMAKE_BINARY_DIR}"
)
