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

### JEPGO ENGINE ##############################################

# add_executable(jepgo
#     ${ENGINE_SRC_DIR}/main.cpp
#     ${ENGINE_SRC_DIR}/MainGame.cpp
#     ${ENGINE_SRC_DIR}/Register.cpp
#     ${ENGINE_SRC_DIR}/Components.cpp
#     ${ENGINE_SRC_DIR}/HitSystem.cpp
#     ${ENGINE_SRC_DIR}/MoveSystem.cpp
#     ${ENGINE_SRC_DIR}/DrawSystem.cpp
#     ${ENGINE_SRC_DIR}/AnimationSpriteSystem.cpp
#     ${ENGINE_SRC_DIR}/TestGame.cpp
#     ${ENGINE_SRC_DIR}/Controllable.cpp
#     ${ENGINE_SRC_DIR}/Module.cpp
#     ${ENGINE_SRC_DIR}/Shoot.cpp
#     ${ENGINE_SRC_DIR}/ExplosionSystem.cpp
#     ${ENGINE_SRC_DIR}/Game.cpp
#     ${ENGINE_SRC_DIR}/Enemy.cpp
#     ${ENGINE_SRC_DIR}/Text.cpp
#     ${ENGINE_SRC_DIR}/GameSystem.cpp
#     ${ENGINE_SRC_DIR}/DestroyerSystem.cpp
#     ${ENGINE_SRC_DIR}/LoopMoveSystem.cpp
#     ${ENGINE_SRC_DIR}/ShortAnimationSystem.cpp
#     ${ENGINE_SRC_DIR}/Animation2TimeSystem.cpp
#     ${ENGINE_SRC_DIR}/MoveToPlayerSystem.cpp
#     ${ENGINE_SRC_DIR}/MoveToPlayerTimeSystem.cpp
#     ${ENGINE_SRC_DIR}/BombGenerationTimeSystem.cpp
#     ${ENGINE_SRC_DIR}/BombGenerationSystem.cpp
#     ${ENGINE_SRC_DIR}/Raylib.cpp
#     ${ENGINE_SRC_DIR}/DetachModulesSystem.cpp
#     ${ENGINE_SRC_DIR}/MoveToSystem.cpp
#     ${ENGINE_SRC_DIR}/MoveTo.cpp
#     ${ENGINE_SRC_DIR}/DeathSystem.cpp
#     ${ENGINE_SRC_DIR}/AutoShootSystem.cpp
#     ${ENGINE_SRC_DIR}/Menu.cpp
#     ${ENGINE_SRC_DIR}/AnimLine.cpp
#     ${ENGINE_SRC_DIR}/LogIcon.cpp
#     ${ENGINE_SRC_DIR}/Button.cpp
# )

add_library(jepgo STATIC
    # ${ENGINE_SRC_DIR}/main.cpp
    # ${ENGINE_SRC_DIR}/MainGame.cpp
    ${ENGINE_SRC_DIR}/Register.cpp
    ${ENGINE_SRC_DIR}/Components.cpp
    ${ENGINE_SRC_DIR}/HitSystem.cpp
    ${ENGINE_SRC_DIR}/MoveSystem.cpp
    ${ENGINE_SRC_DIR}/DrawSystem.cpp
    ${ENGINE_SRC_DIR}/AnimationSpriteSystem.cpp
    ${ENGINE_SRC_DIR}/TestGame.cpp
    ${ENGINE_SRC_DIR}/Controllable.cpp
    ${ENGINE_SRC_DIR}/Module.cpp
    ${ENGINE_SRC_DIR}/Shoot.cpp
    ${ENGINE_SRC_DIR}/ExplosionSystem.cpp
    ${ENGINE_SRC_DIR}/Game.cpp
    ${ENGINE_SRC_DIR}/Enemy.cpp
    ${ENGINE_SRC_DIR}/Text.cpp
    ${ENGINE_SRC_DIR}/GameSystem.cpp
    ${ENGINE_SRC_DIR}/DestroyerSystem.cpp
    ${ENGINE_SRC_DIR}/LoopMoveSystem.cpp
    ${ENGINE_SRC_DIR}/ShortAnimationSystem.cpp
    ${ENGINE_SRC_DIR}/Animation2TimeSystem.cpp
    ${ENGINE_SRC_DIR}/MoveToPlayerSystem.cpp
    ${ENGINE_SRC_DIR}/MoveToPlayerTimeSystem.cpp
    ${ENGINE_SRC_DIR}/BombGenerationTimeSystem.cpp
    ${ENGINE_SRC_DIR}/BombGenerationSystem.cpp
    ${ENGINE_SRC_DIR}/Raylib.cpp
    ${ENGINE_SRC_DIR}/DetachModulesSystem.cpp
    ${ENGINE_SRC_DIR}/MoveToSystem.cpp
    ${ENGINE_SRC_DIR}/MoveTo.cpp
    ${ENGINE_SRC_DIR}/DeathSystem.cpp
    ${ENGINE_SRC_DIR}/AutoShootSystem.cpp
    ${ENGINE_SRC_DIR}/Menu.cpp
    ${ENGINE_SRC_DIR}/AnimLine.cpp
    ${ENGINE_SRC_DIR}/LogIcon.cpp
    ${ENGINE_SRC_DIR}/Button.cpp
)

target_link_libraries(jepgo PRIVATE raylib)
target_include_directories(jepgo PRIVATE ./engine/include)

### JEPMOD LIBRARY ##############################################

add_library(jepmod STATIC
    ${JEPMOD_SRC_DIR}/DLLoader.cpp
    ${JEPMOD_SRC_DIR}/Jepmodule.cpp
    ${JEPMOD_SRC_DIR}/module.cpp
)

### JEPGAME LIBRARY ##############################################

add_library(jepgame STATIC
  ${JEPGAME_SRC_DIR}/service/UDP.cpp
  ${JEPGAME_SRC_DIR}/service/Builder.cpp
  ${JEPGAME_SRC_DIR}/service/Connections.cpp
  ${JEPGAME_SRC_DIR}/gamemaker/hardcoded.cpp
  ${JEPGAME_SRC_DIR}/gamemaker/Client.cpp
  ${JEPGAME_SRC_DIR}/gamemaker/Server.cpp 
)

set_target_properties(jepgame PROPERTIES VERSION ${PROJECT_VERSION})
target_include_directories(jepgame PRIVATE ./ ${asio_SOURCE_DIR}/asio/include)
target_link_libraries(jepgame PRIVATE raylib)

# ### SERVER ##############################################

add_executable(r-type_server
    ${SERVER_SRC_DIR}/game.server.cpp
)

target_include_directories(r-type_server PRIVATE ./ ${asio_SOURCE_DIR}/asio/include)
target_link_libraries(r-type_server PRIVATE jepgame jepgo jepmod raylib)

### CLIENT ##############################################

add_executable(r-type_client
    ${CLIENT_SRC_DIR}/game.client.cpp
)

target_include_directories(r-type_client PRIVATE ./ ${asio_SOURCE_DIR}/asio/include)
target_link_libraries(r-type_client PRIVATE jepgame jepgo jepmod sfml-graphics sfml-system sfml-window raylib)

#########################################################