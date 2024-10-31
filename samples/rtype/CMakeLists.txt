CMAKE_MINIMUM_REQUIRED(VERSION 3.14) # pi

PROJECT(r-type_client)

SET(CMAKE_CXX_STANDARD 23)

ADD_EXECUTABLE(r-type_client
    game.client.cpp
)

LINK_DIRECTORIES(
    ${CMAKE_BINARY_DIR}/
)

TARGET_INCLUDE_DIRECTORIES(r-type_client PRIVATE
    ./
    ${CMAKE_SOURCE_DIR}/include
)

TARGET_LINK_LIBRARIES(r-type_client
    jepengine
    jepmod
)

ADD_CUSTOM_COMMAND(TARGET r-type_client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_client> ${CMAKE_SOURCE_DIR}/samples/rtype
)