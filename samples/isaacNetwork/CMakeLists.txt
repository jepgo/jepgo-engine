CMAKE_MINIMUM_REQUIRED(VERSION 3.14) # pi

SET(CMAKE_CXX_STANDARD 23)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

# create the ressources

SET(Ressources
    isaac.png
)

ADD_CUSTOM_TARGET(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/${Resources}
        ${CMAKE_CURRENT_BINARY_DIR}/${Resources}
    DEPENDS ${Resources}
)

# create the systems

SET(Systems
    Movement.cpp
    Display.cpp
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

# create the client

PROJECT(client)
ADD_EXECUTABLE(client
    game.client.cpp
)
TARGET_INCLUDE_DIRECTORIES(client PRIVATE . $ENV{JEPGO_INCLUDE})
TARGET_LINK_DIRECTORIES(client PRIVATE $ENV{JEPGO_BUILD})
TARGET_LINK_LIBRARIES(client PRIVATE jepengine jepmod)

# create the server

PROJECT(server)
ADD_EXECUTABLE(server
    game.server.cpp
)
TARGET_INCLUDE_DIRECTORIES(server PRIVATE . $ENV{JEPGO_INCLUDE})
TARGET_LINK_DIRECTORIES(server PRIVATE $ENV{JEPGO_BUILD})
TARGET_LINK_LIBRARIES(server PRIVATE jepengine jepmod)
