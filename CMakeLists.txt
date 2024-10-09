cmake_minimum_required(VERSION 3.0)

### PROJECTS ############################################

# project(r-type_client VERSION 1.0 DESCRIPTION "R-Type client")
# project(r-type_server VERSION 1.0 DESCRIPTION "R-Type server")
project(jepgo VERSION 1.0 DESCRIPTION "Jepgo engine")
project(jepgame VERSION 1.0 DESCRIPTION "Jepgame library")
project(jepmod VERSION 1.0 DESCRIPTION "Jepmod library")

### VARIABLES ###########################################

set(CMAKE_CXX_STANDARD 23)
set(ENGINE_SRC_DIR engine/src)
set(CLIENT_SRC_DIR sample)
set(SERVER_SRC_DIR sample)
set(JEPGAME_SRC_DIR jepgame/)
set(JEPMOD_SRC_DIR jepmod/)
set(ASIO_INCLUDE_DIR ${asio_SOURCE_DIR}/asio/include)

### PACKAGE MANAGER #####################################

# include(cmake/CPM.cmake)

# CPMAddPackage(
#     NAME SFML
#     GIT_REPOSITORY https://github.com/SFML/SFML
#     GIT_TAG 2.6.1
# )
# CPMAddPackage(
#     NAME asio
#     GIT_REPOSITORY https://github.com/chriskohlhoff/asio
#     GIT_TAG asio-1-31-0
# )

# CPMAddPackage(
#     NAME sqlite3
#     GIT_REPOSITORY https://github.com/LuaDist/libsqlite3
#     GIT_TAG 3.7.7.1
# )

# CPMAddPackage(
#     NAME raylib
#     GIT_REPOSITORY https://github.com/raysan5/raylib
#     GIT_TAG 5.0
# )

# libjepengine.a

# PROJECT(jepengine)
# SET(EngineSRC engine/src)
# ADD_LIBRARY(jepengine STATIC
#     ${EngineSRC}/Register.cpp
#     ${EngineSRC}/Components.cpp
#     ${EngineSRC}/HitSystem.cpp
#     ${EngineSRC}/MoveSystem.cpp
#     ${EngineSRC}/DrawSystem.cpp
#     ${EngineSRC}/AnimationSpriteSystem.cpp
#     ${EngineSRC}/TestGame.cpp
#     ${EngineSRC}/Controllable.cpp
#     ${EngineSRC}/Module.cpp
#     ${EngineSRC}/Shoot.cpp
#     ${EngineSRC}/ExplosionSystem.cpp
#     ${EngineSRC}/Game.cpp
#     ${EngineSRC}/Enemy.cpp
#     ${EngineSRC}/Text.cpp
#     ${EngineSRC}/GameSystem.cpp
#     ${EngineSRC}/DestroyerSystem.cpp
#     ${EngineSRC}/LoopMoveSystem.cpp
#     ${EngineSRC}/ShortAnimationSystem.cpp
#     ${EngineSRC}/Animation2TimeSystem.cpp
#     ${EngineSRC}/MoveToPlayerSystem.cpp
#     ${EngineSRC}/MoveToPlayerTimeSystem.cpp
#     ${EngineSRC}/BombGenerationTimeSystem.cpp
#     ${EngineSRC}/BombGenerationSystem.cpp
#     ${EngineSRC}/Raylib.cpp
# )
# TARGET_INCLUDE_DIRECTORIES(jepengine PRIVATE engine/include ${raylib_SOURCE_DIR}/src)

# libjepmod.a

PROJECT(jepmod)
SET(JepmodSRC jepmod/)


ADD_LIBRARY(jepmod STATIC
    ${JepmodSRC}/DLLoader.cpp
    ${JepmodSRC}/Jepmodule.cpp
)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  target_compile_definitions(jepmod PUBLIC "LINUX")
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  target_compile_definitions(jepmod PUBLIC "WINDOWS")
endif()


PROJECT(caca)
add_executable(caca 
    ${JepmodSRC}/main.cpp)
TARGET_LINK_LIBRARIES(caca PRIVATE jepmod)
target_include_directories(caca PRIVATE .)


project(zizi)
add_library(zizi SHARED
    ${JepmodSRC}/module.cpp)
TARGET_LINK_LIBRARIES(zizi PRIVATE jepmod)
target_include_directories(zizi PRIVATE .)


# libjepgame.a

# PROJECT(jepgame)
# SET(JepgameSRC jepgame/)
# ADD_LIBRARY(jepgame STATIC
#     ${JepgameSRC}/service/UDP.cpp
#     ${JepgameSRC}/service/Builder.cpp
#     ${JepgameSRC}/service/Connections.cpp
#     ${JepgameSRC}/gamemaker/hardcoded.cpp
#     ${JepgameSRC}/gamemaker/Client.cpp
#     ${JepgameSRC}/gamemaker/Server.cpp
# )
# TARGET_INCLUDE_DIRECTORIES(jepgame PRIVATE . ${raylib_SOURCE_DIR}/src ${asio_SOURCE_DIR}/asio/include)

# # game.client

# PROJECT(client)
# SET(ClientSRC sample/)
# ADD_EXECUTABLE(client
#     ${ClientSRC}/game.client.cpp
# )
# TARGET_INCLUDE_DIRECTORIES(client PRIVATE . ${raylib_SOURCE_DIR}/src ${asio_SOURCE_DIR}/asio/include)
# TARGET_LINK_LIBRARIES(client PRIVATE
#     jepgame
#     jepengine
#     jepmod
#     sfml-graphics
#     sfml-window
#     sfml-system
#     raylib
# )

# # game.server

# PROJECT(server)
# SET(ServerSRC sample/)
# ADD_EXECUTABLE(server
#     ${ServerSRC}/game.server.cpp
# )
# TARGET_INCLUDE_DIRECTORIES(server PRIVATE . ${raylib_SOURCE_DIR}/src ${asio_SOURCE_DIR}/asio/include)
# TARGET_LINK_LIBRARIES(server PRIVATE
#     jepgame
#     jepengine
#     jepmod
#     sfml-graphics
#     sfml-window
#     sfml-system
#     raylib
# )
