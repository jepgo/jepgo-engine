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

# create the server

PROJECT(r-type_server)
ADD_EXECUTABLE(r-type_server
game.server.cpp
sysAndComps.cpp
)
TARGET_INCLUDE_DIRECTORIES(r-type_server PRIVATE . $ENV{JEPGO_INCLUDE})
TARGET_LINK_DIRECTORIES(r-type_server PRIVATE $ENV{JEPGO_BUILD})
TARGET_LINK_LIBRARIES(r-type_server PRIVATE jepengine jepmod)

ADD_CUSTOM_COMMAND(TARGET r-type_server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_server> ${CMAKE_SOURCE_DIR}/samples/rtype
)

# create the client

# PROJECT(client)
# ADD_EXECUTABLE(client
#     game.client.cpp
# )
# TARGET_INCLUDE_DIRECTORIES(client PRIVATE . $ENV{JEPGO_INCLUDE})
# TARGET_LINK_DIRECTORIES(client PRIVATE $ENV{JEPGO_BUILD})
# TARGET_LINK_LIBRARIES(client PRIVATE jepengine jepmod)

#

PROJECT(r-type_client)

ADD_EXECUTABLE(r-type_client
    game.client.cpp
    src/main.cpp
    src/Menu.cpp
    src/RaylibPlus.cpp
    src/LogIcon.cpp
    src/Button.cpp
    src/AnimLine.cpp
    src/Level1.cpp
)

LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/)
TARGET_LINK_DIRECTORIES(r-type_client PRIVATE $ENV{JEPGO_INCLUDE})
TARGET_INCLUDE_DIRECTORIES(r-type_client PRIVATE
    ./include
    # ${CMAKE_SOURCE_DIR}/include
    $ENV{JEPGO_INCLUDE}
)
TARGET_LINK_LIBRARIES(r-type_client
    jepengine
    jepmod
    raylib
)

ADD_CUSTOM_COMMAND(TARGET r-type_client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_client> ${CMAKE_SOURCE_DIR}/samples/rtype
)
