CMAKE_MINIMUM_REQUIRED(VERSION 3.14) # pi

# general

SET(CMAKE_CXX_STANDARD 23)
set(ENGINE_SRC_DIR engine/src)
set(CLIENT_DIR games/rtype/client)
set(SERVER_SRC_DIR games/rtype/server)
set(JEPGAME_SRC_DIR jepgame/)
set(JEPMOD_SRC_DIR jepmod/)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
set(ASIO_INCLUDE_DIR ${asio_SOURCE_DIR}/asio/include)

# packages

include(cmake/CPM.cmake)

CPMAddPackage(
    NAME raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib
    GIT_TAG 5.0
)
CPMAddPackage(
    NAME asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio
    GIT_TAG asio-1-31-0
)

CPMAddPackage(
    NAME sqlite3
    GIT_REPOSITORY https://github.com/LuaDist/libsqlite3
    GIT_TAG 3.7.7.1
)


# libjepengine.a

PROJECT(jepengine)
SET(EngineSRC engine/src)
ADD_LIBRARY(jepengine STATIC
    ${EngineSRC}/Register.cpp
    ${EngineSRC}/Components.cpp
    ${EngineSRC}/HitSystem.cpp
    ${EngineSRC}/MoveSystem.cpp
    ${EngineSRC}/DrawSystem.cpp
    ${EngineSRC}/AnimationSpriteSystem.cpp
    ${EngineSRC}/TestGame.cpp
    ${EngineSRC}/Controllable.cpp
    ${EngineSRC}/Module.cpp
    ${EngineSRC}/Shoot.cpp
    ${EngineSRC}/ExplosionSystem.cpp
    ${EngineSRC}/Game.cpp
    ${EngineSRC}/Enemy.cpp
    ${EngineSRC}/Text.cpp
    ${EngineSRC}/GameSystem.cpp
    ${EngineSRC}/DestroyerSystem.cpp
    ${EngineSRC}/LoopMoveSystem.cpp
    ${EngineSRC}/ShortAnimationSystem.cpp
    ${EngineSRC}/Animation2TimeSystem.cpp
    ${EngineSRC}/MoveToPlayerSystem.cpp
    ${EngineSRC}/MoveToPlayerTimeSystem.cpp
    ${EngineSRC}/BombGenerationTimeSystem.cpp
    ${EngineSRC}/BombGenerationSystem.cpp
    ${EngineSRC}/Raylib.cpp
)
TARGET_COMPILE_OPTIONS(jepengine PRIVATE -fPIC)
TARGET_INCLUDE_DIRECTORIES(jepengine PRIVATE engine/include ${raylib_SOURCE_DIR}/src)

# libjepmod.a

PROJECT(jepmod)
SET(JepmodSRC jepmod/)

ADD_LIBRARY(jepmod STATIC
    ${JepmodSRC}/DLLoader.cpp
    ${JepmodSRC}/Jepmodule.cpp
    ${JepmodSRC}/external/FileBuilder.cpp
    ${JepmodSRC}/external/OpenInclude.cpp
    ${JepmodSRC}/external/generation.cpp
)
TARGET_COMPILE_OPTIONS(jepmod PRIVATE -fPIC)
TARGET_INCLUDE_DIRECTORIES(jepmod PRIVATE .)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  target_compile_definitions(jepmod PUBLIC "LINUX")
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  target_compile_definitions(jepmod PUBLIC "WINDOWS")
endif()


# PROJECT(caca)
# add_executable(caca 
#     ${JepmodSRC}/main.cpp)
# TARGET_LINK_LIBRARIES(caca PRIVATE jepmod)
# target_include_directories(caca PRIVATE .)


# project(zizi)
# add_library(zizi SHARED
#     ${JepmodSRC}/module.cpp)
# TARGET_LINK_LIBRARIES(zizi PRIVATE jepmod)
# target_include_directories(zizi PRIVATE .)


# libjepgame.a

PROJECT(jepgame)
SET(JepgameSRC jepgame/)
ADD_LIBRARY(jepgame STATIC
    ${JepgameSRC}/service/UDP.cpp
    ${JepgameSRC}/service/Builder.cpp
    ${JepgameSRC}/service/Connections.cpp
    ${JepgameSRC}/gamemaker/hardcoded.cpp
    ${JepgameSRC}/gamemaker/Client.cpp
    ${JepgameSRC}/gamemaker/Server.cpp
)
TARGET_COMPILE_OPTIONS(jepgame PRIVATE -fPIC)
TARGET_INCLUDE_DIRECTORIES(jepgame PRIVATE . ${raylib_SOURCE_DIR}/src ${asio_SOURCE_DIR}/asio/include)

# game.client

PROJECT(client)
SET(ClientSRC sample/)
ADD_EXECUTABLE(client
    ${ClientSRC}/game.client.cpp
)
TARGET_INCLUDE_DIRECTORIES(client PRIVATE . ${raylib_SOURCE_DIR}/src ${asio_SOURCE_DIR}/asio/include)
TARGET_LINK_LIBRARIES(client PRIVATE
    jepgame
    jepengine
    jepmod
    sfml-graphics
    sfml-window
    sfml-system
    raylib
)

# game.server

PROJECT(server)
SET(ServerSRC sample/)
ADD_EXECUTABLE(server
    ${ServerSRC}/game.server.cpp
)
TARGET_COMPILE_OPTIONS(jepmod PRIVATE -fPIC)
TARGET_INCLUDE_DIRECTORIES(server PRIVATE . ${raylib_SOURCE_DIR}/src ${asio_SOURCE_DIR}/asio/include)
TARGET_LINK_LIBRARIES(server PRIVATE
    jepgame
    jepengine
    jepmod
    sfml-graphics
    sfml-window
    sfml-system
    raylib
)

# external.server

PROJECT(external.server)
ADD_LIBRARY(external.server SHARED
    external.server.cpp
)
TARGET_COMPILE_OPTIONS(external.server PRIVATE -fPIC)
TARGET_INCLUDE_DIRECTORIES(
    external.server PRIVATE .
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
TARGET_COMPILE_OPTIONS(external.client PRIVATE -fPIC)
TARGET_INCLUDE_DIRECTORIES(
    external.client PRIVATE .
)
TARGET_LINK_LIBRARIES(external.client PUBLIC
    jepgame
    jepengine
    jepmod
)

# copy the sprites

SET(RessourceDir "${CMAKE_SOURCE_DIR}/sprites")
SET(DestinationDir "${CMAKE_BINARY_DIR}/sprites")

ADD_CUSTOM_TARGET(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${RessourceDir}"
    "${DestinationDir}"
)

# copy the components

SET(RessourceDir "${CMAKE_SOURCE_DIR}/components")
SET(DestinationDir "${CMAKE_BINARY_DIR}/components")

ADD_CUSTOM_TARGET(copy_components ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${RessourceDir}"
    "${DestinationDir}"
)
