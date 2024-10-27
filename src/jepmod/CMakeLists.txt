CMAKE_MINIMUM_REQUIRED(VERSION 3.14) # pi

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

PROJECT(jepmod)

ADD_LIBRARY(jepmod STATIC
    DLLoader.cpp
)

TARGET_INCLUDE_DIRECTORIES(jepmod PRIVATE ../../include)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  target_compile_definitions(jepmod PUBLIC "LINUX")
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  target_compile_definitions(jepmod PUBLIC "WINDOWS")
endif()

ADD_CUSTOM_COMMAND(TARGET jepmod POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "$<TARGET_FILE:jepmod>"
    "${CMAKE_BINARY_DIR}"
)