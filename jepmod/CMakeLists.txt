CMAKE_MINIMUM_REQUIRED(VERSION 3.14) # pi

PROJECT(jepmod)

ADD_LIBRARY(jepmod STATIC
    DLLoader.cpp
    Jepmodule.cpp
    external/FileBuilder.cpp
    external/OpenInclude.cpp
    external/generation.cpp
)

TARGET_INCLUDE_DIRECTORIES(jepmod PRIVATE ../)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  target_compile_definitions(jepmod PUBLIC "LINUX")
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  target_compile_definitions(jepmod PUBLIC "WINDOWS")
endif()