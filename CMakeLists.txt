CMAKE_MINIMUM_REQUIRED(VERSION 3.14) # pi

# general

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(FETCHCONTENT_QUIET FALSE)
set(ENGINE_SRC_DIR engine/src)
set(CLIENT_SRC_DIR sample)
set(SERVER_SRC_DIR sample)
set(JEPGAME_SRC_DIR jepgame/)
set(JEPMOD_SRC_DIR jepmod/)
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
    NAME SQLite3
    GIT_REPOSITORY https://github.com/LuaDist/libsqlite3
    GIT_TAG 3.7.7.1
)
list(APPEND CMAKE_MODULE_PATH "${SQLite3_SOURCE_DIR}/cmake")

CPMAddPackage(
    NAME sqliteorm
    GIT_REPOSITORY https://github.com/fnc12/sqlite_orm
    GIT_TAG v1.9
)
CPMAddPackage(
    NAME libconfig
    GIT_REPOSITORY https://github.com/hyperrealm/libconfig
    GIT_TAG v1.7.3
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
	${EngineSRC}/DetachModulesSystem.cpp
	${EngineSRC}/MoveToSystem.cpp
	${EngineSRC}/MoveTo.cpp
	${EngineSRC}/DeathSystem.cpp
	${EngineSRC}/AutoShootSystem.cpp
	${EngineSRC}/Menu.cpp
	${EngineSRC}/AnimLine.cpp
	${EngineSRC}/LogIcon.cpp
	${EngineSRC}/Button.cpp
	${EngineSRC}/MainGame.cpp
	${EngineSRC}/RaylibPlus.cpp
	${EngineSRC}/Draw3DSystem.cpp
	${EngineSRC}/Rotation3DSystem.cpp
)
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
TARGET_INCLUDE_DIRECTORIES(jepmod PRIVATE .)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  target_compile_definitions(jepmod PUBLIC "LINUX")
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  target_compile_definitions(jepmod PUBLIC "WINDOWS")
endif()

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
TARGET_INCLUDE_DIRECTORIES(jepgame PRIVATE . ${raylib_SOURCE_DIR}/src ${asio_SOURCE_DIR}/asio/include)

# game.client

PROJECT(r-type_client)
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

PROJECT(r-type_server)
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
