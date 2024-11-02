CMAKE_MINIMUM_REQUIRED(VERSION 3.14) # pi

SET(CMAKE_CXX_STANDARD 23)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(Systems
    systemA.cpp
    systemB.cpp
    systemC.cpp
)

foreach(file ${Systems})
    get_filename_component(basename ${file} NAME_WLE)
    string(CONCAT finalName "jepgo.system." ${basename})
    project(${finalName})
    message(${finalName})
    # message(${file})
    add_library(${finalName} SHARED ${file})
    TARGET_INCLUDE_DIRECTORIES(${finalName} PRIVATE . $ENV{JEPGO_INCLUDE})
    TARGET_LINK_DIRECTORIES(${finalName} PRIVATE $ENV{JEPGO_BUILD})
    target_link_libraries(${finalName} jepengine jepmod)
    ADD_CUSTOM_COMMAND(TARGET ${finalName} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE:${finalName}>"
        "${CMAKE_BINARY_DIR}"
    )
endforeach()

PROJECT(prio)
ADD_EXECUTABLE(prio
    game.client.cpp
)
TARGET_INCLUDE_DIRECTORIES(prio PRIVATE . $ENV{JEPGO_INCLUDE})
TARGET_LINK_DIRECTORIES(prio PRIVATE $ENV{JEPGO_BUILD})
TARGET_LINK_LIBRARIES(prio PRIVATE jepengine jepmod)
