CMAKE_MINIMUM_REQUIRED(VERSION 3.14) # pi

# general

SET(CMAKE_CXX_STANDARD 23)

# packages

include(cmake/CPM.cmake)

CPMAddPackage(
    NAME SFML
    GIT_REPOSITORY https://github.com/SFML/SFML
    GIT_TAG 2.6.1
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

CPMAddPackage(
    NAME raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib
    GIT_TAG 5.0
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
TARGET_INCLUDE_DIRECTORIES(jepengine PRIVATE engine/include)

# libjepmod.a

PROJECT(jepmod)
SET(JepmodSRC jepmod/)
ADD_LIBRARY(jepmod STATIC
    ${JepmodSRC}/DLLoader.cpp
    ${JepmodSRC}/Jepmodule.cpp
)

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
TARGET_INCLUDE_DIRECTORIES(jepgame PRIVATE .)

# game.client

PROJECT(client)
SET(ClientSRC sample/)
ADD_EXECUTABLE(client
    ${ClientSRC}/game.client.cpp
)
TARGET_INCLUDE_DIRECTORIES(client PRIVATE .)
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
TARGET_INCLUDE_DIRECTORIES(server PRIVATE .)
TARGET_LINK_LIBRARIES(server PRIVATE
    jepgame
    jepengine
    jepmod
    sfml-graphics
    sfml-window
    sfml-system
    raylib
)
