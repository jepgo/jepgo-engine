cmake_minimum_required(VERSION 3.0)

### PROJECTS ############################################

project(r-type DESCRIPTION "R-Type")
# project(r-type_client VERSION 1.0 DESCRIPTION "R-Type client")
# project(r-type_server VERSION 1.0 DESCRIPTION "R-Type server")
# project(jepgo VERSION 1.0 DESCRIPTION "Jepgo engine")
# project(jepgame VERSION 1.0 DESCRIPTION "Jepgame library")
# project(jepmod VERSION 1.0 DESCRIPTION "Jepmod library")

### VARIABLES ###########################################

set(CMAKE_CXX_STANDARD 20)
set(ENGINE_SRC_DIR engine/src)
set(CLIENT_DIR games/rtype/client)
set(SERVER_SRC_DIR games/rtype/server)
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

add_executable(r-type
    ${ENGINE_SRC_DIR}/main.cpp
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
    ${ENGINE_SRC_DIR}/MainGame.cpp
)
    
if(MSVC)
  target_compile_options(r-type PRIVATE /W4)
else()
  target_compile_options(r-type PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_include_directories(r-type PRIVATE ./engine/include)
target_link_libraries(r-type PRIVATE raylib)

### JEPMOD LIBRARY ##############################################

# add_library(jepmod STATIC
#     ${JEPMOD_SRC_DIR}/DLLoader.cpp
#     ${JEPMOD_SRC_DIR}/Jepmodule.cpp
#     ${JEPMOD_SRC_DIR}/module.cpp
# )

### JEPGAME LIBRARY ##############################################

# add_library(jepgame STATIC
#     ${JEPGAME_SRC_DIR}/Builder.cpp
#     ${JEPGAME_SRC_DIR}/Connections.cpp
#     ${JEPGAME_SRC_DIR}/UDP.cpp
# )

# set_target_properties(jepgame PROPERTIES VERSION ${PROJECT_VERSION})
# target_include_directories(jepgame PRIVATE ./jepgame)
# target_include_directories(jepgame PRIVATE ./)
# target_include_directories(jepgame PRIVATE ./jepgame/include)
# target_include_directories(jepgame PRIVATE ${ASIO_INCLUDE_DIR})
# target_link_libraries(jepgame PRIVATE sfml-graphics)

# ### SERVER ##############################################

# add_executable(r-type_server
#     ${SERVER_SRC_DIR}/main.cpp
# )

# target_include_directories(r-type_server PRIVATE ./)
# target_include_directories(r-type_server PRIVATE ${ASIO_INCLUDE_DIR})
# target_link_libraries(r-type_server PRIVATE jepgo jepgame sfml-graphics sfml-system raylib sqlite3)

### CLIENT ##############################################

# add_executable(r-type_client
#     ${CLIENT_DIR}/main.cpp
#     ${CLIENT_DIR}/src/Client.cpp
#     ${CLIENT_DIR}/src/OPCodeHanling.cpp
#     ${CLIENT_DIR}/src/UDP.cpp
#     ${CLIENT_DIR}/src/TCP.cpp
# )

# target_include_directories(r-type_client PRIVATE ./engine/include)
# target_include_directories(r-type_client PRIVATE ./)
# target_include_directories(r-type_client PRIVATE ./games/rtype/client/include)
# target_include_directories(r-type_client PRIVATE ${ASIO_INCLUDE_DIR})
# target_link_libraries(r-type_client PRIVATE jepgo jepgame sfml-graphics sfml-system sfml-window)

#########################################################