CMAKE_MINIMUM_REQUIRED(VERSION 3.14) # pi

SET(CMAKE_CXX_STANDARD 23)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(NNAME foo)

#=====# Create your ressources #=====#

SET(Ressources
    # Add your ressources here
)

ADD_CUSTOM_TARGET(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/${Resources}
        ${CMAKE_CURRENT_BINARY_DIR}/${Resources}
    DEPENDS ${Resources}
)

#=====# Create your systems #=====#

SET(Systems
    # Add your systems here
)

foreach(file ${Systems})
    get_filename_component(basename ${file} NAME_WLE)
    string(CONCAT finalName "jepgo.system." ${basename})
    project(${finalName})
    message(${finalName})
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

#=====# Create your server #=====#

# PROJECT(${NNAME}_server)
# ADD_EXECUTABLE(
#     game.server.cpp # Uncomment to use server
# )
# TARGET_INCLUDE_DIRECTORIES(${NNAME}_server PRIVATE . $ENV{JEPGO_INCLUDE})
# TARGET_LINK_DIRECTORIES(${NNAME}_server PRIVATE $ENV{JEPGO_BUILD})
# TARGET_LINK_LIBRARIES(${NNAME}_server PRIVATE jepengine jepmod)

#=====# Create your client #=====#

PROJECT(client)
ADD_LIBRARY(client SHARED
    game.client.cpp # Uncomment to use client
)
TARGET_INCLUDE_DIRECTORIES(client PRIVATE . $ENV{JEPGO_INCLUDE})
TARGET_LINK_DIRECTORIES(client PRIVATE $ENV{JEPGO_BUILD})
TARGET_LINK_LIBRARIES(client PRIVATE jepengine jepmod)

