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
SET(EngineSRC src/jepengine)
ADD_LIBRARY(jepengine STATIC
    ${EngineSRC}/Register.cpp
	${EngineSRC}/Game.cpp
)
TARGET_INCLUDE_DIRECTORIES(jepengine PRIVATE include)

# libjepmod.a

PROJECT(jepmod)
SET(JepmodSRC src/jepmod)
ADD_LIBRARY(jepmod STATIC
    ${JepmodSRC}/DLLoader.cpp
    # ${JepmodSRC}/Jepmodule.cpp
    # ${JepmodSRC}/external/FileBuilder.cpp
    # ${JepmodSRC}/external/OpenInclude.cpp
    # ${JepmodSRC}/external/generation.cpp
)
TARGET_INCLUDE_DIRECTORIES(jepmod PRIVATE include)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  target_compile_definitions(jepmod PUBLIC "LINUX")
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  target_compile_definitions(jepmod PUBLIC "WINDOWS")
endif()

# jepgo.component.Poison.so

PROJECT(jepgo.component.Poison)
SET(JepmodSRC src/jepmaker/services)
ADD_LIBRARY(jepgo.component.Poison SHARED
    ${JepmodSRC}/Poison.cpp
)
ADD_COMPILE_OPTIONS(-fPIC)
TARGET_LINK_LIBRARIES(jepgo.component.Poison jepmod jepengine)
TARGET_INCLUDE_DIRECTORIES(jepgo.component.Poison PRIVATE include)
