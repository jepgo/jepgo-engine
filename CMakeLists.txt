CMAKE_MINIMUM_REQUIRED(VERSION 3.14) # pi

PROJECT(jepengine)
PROJECT(jepgame)
PROJECT(jepmod)
PROJECT(r-type_client)
PROJECT(r-type_server)
PROJECT(solo)
# general

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(FETCHCONTENT_QUIET FALSE)

# find_packages
find_package(raylib QUIET)
find_package(SQLite3 QUIET)
find_package(SqliteOrm QUIET)

# package manager
include(cmake/CPM.cmake)
include(cmake/dependencies.cmake)

add_subdirectory(engine)
add_subdirectory(jepmod)
add_subdirectory(jepgame)

# game.client

SET(ClientSRC sample/)
ADD_EXECUTABLE(r-type_client
    ${ClientSRC}/game.client.cpp
)
TARGET_INCLUDE_DIRECTORIES(r-type_client PRIVATE . ${raylib_SOURCE_DIR}/src ${asio_SOURCE_DIR}/asio/include)
TARGET_LINK_LIBRARIES(r-type_client PRIVATE
    jepgame
    jepengine
    jepmod
    raylib
)

# game.server

SET(ServerSRC sample/)
ADD_EXECUTABLE(r-type_server
    ${ServerSRC}/game.server.cpp
)
TARGET_INCLUDE_DIRECTORIES(r-type_server PRIVATE . ${raylib_SOURCE_DIR}/src ${asio_SOURCE_DIR}/asio/include)
TARGET_LINK_LIBRARIES(r-type_server PRIVATE
    jepgame
    jepengine
    jepmod
    raylib
)

# external.server

PROJECT(external.server)
ADD_LIBRARY(external.server SHARED
    external.server.cpp
)
TARGET_INCLUDE_DIRECTORIES(
    external.server PRIVATE .
    ${raylib_SOURCE_DIR}/src
    ${asio_SOURCE_DIR}/asio/include
)
TARGET_LINK_LIBRARIES(external.server PUBLIC
    jepgame
    jepengine
    jepmod
)

# external.client

PROJECT(external.client)
ADD_LIBRARY(external.client SHARED
    external.client.cpp
)
TARGET_INCLUDE_DIRECTORIES(
    external.client PRIVATE .
    ${raylib_SOURCE_DIR}/src
    ${asio_SOURCE_DIR}/asio/include
)
TARGET_LINK_LIBRARIES(external.client PUBLIC
    jepgame
    jepengine
    jepmod
)

# copy the sprites

# SET(RessourceDir "${CMAKE_SOURCE_DIR}/sprites")
# SET(DestinationDir "${CMAKE_BINARY_DIR}/sprites")

# ADD_CUSTOM_TARGET(copy_resources ALL
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#     "${RessourceDir}"
#     "${DestinationDir}"
# )

# # copy the components

# SET(RessourceDir "${CMAKE_SOURCE_DIR}/components")
# SET(DestinationDir "${CMAKE_BINARY_DIR}/components")

# ADD_CUSTOM_TARGET(copy_components ALL
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#     "${RessourceDir}"
#     "${DestinationDir}"
# )

ADD_CUSTOM_COMMAND(TARGET r-type_server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "$<TARGET_FILE:r-type_server>"
    "${CMAKE_SOURCE_DIR}"
)


ADD_CUSTOM_COMMAND(TARGET r-type_client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "$<TARGET_FILE:r-type_client>"
    "${CMAKE_SOURCE_DIR}"
)

ADD_CUSTOM_COMMAND(TARGET external.client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "$<TARGET_FILE:external.client>"
    "${CMAKE_SOURCE_DIR}"
)

ADD_CUSTOM_COMMAND(TARGET external.server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "$<TARGET_FILE:external.server>"
    "${CMAKE_SOURCE_DIR}"
)
