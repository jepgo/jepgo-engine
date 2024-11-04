CMAKE_MINIMUM_REQUIRED(VERSION 3.14) # pi

SET(CMAKE_CXX_STANDARD 23)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(Systems
    systems/PersoSystem.cpp
)

foreach(file ${Systems})
    get_filename_component(basename ${file} NAME_WLE)
    string(CONCAT finalName "jepgo.system." ${basename})
    project(${finalName})
    message(${finalName})
    add_library(${finalName} SHARED ${file})
    TARGET_INCLUDE_DIRECTORIES(${finalName} PRIVATE . ${CMAKE_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/include)
    TARGET_LINK_DIRECTORIES(${finalName} PRIVATE $ENV{JEPGO_BUILD})
    target_link_libraries(${finalName} jepengine jepmod)
    ADD_CUSTOM_COMMAND(TARGET ${finalName} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE:${finalName}>"
        "${CMAKE_BINARY_DIR}"
    )
endforeach()

PROJECT(project_name)
ADD_EXECUTABLE(project_name
    game.client.cpp
)
TARGET_INCLUDE_DIRECTORIES(project_name PRIVATE . ${CMAKE_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/include)
TARGET_LINK_DIRECTORIES(project_name PRIVATE $ENV{JEPGO_BUILD})
TARGET_LINK_LIBRARIES(project_name PRIVATE jepengine jepmod)

ADD_CUSTOM_COMMAND(TARGET project_name POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:project_name> ${CMAKE_SOURCE_DIR}/project_name
)
