CMAKE_MINIMUM_REQUIRED(VERSION 3.14) # pi

PROJECT(jepengine)
PROJECT(jepmod)
# PROJECT(r-type_client)
# PROJECT(r-type_server)

# general

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(FETCHCONTENT_QUIET FALSE)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")

# find_packages
find_package(raylib QUIET)
find_package(SQLite3 QUIET)
find_package(SqliteOrm QUIET)

# package manager
include(cmake/CPM.cmake)
include(cmake/dependencies.cmake)

add_subdirectory(src/jepengine)
add_subdirectory(src/jepmod)
add_subdirectory(src/jepmaker/systems)
add_subdirectory(src/jepmaker/graphic)
# add_subdirectory(src/jep3rdparty/lua)

# # game.client

# SET(ClientSRC sample/)
# ADD_EXECUTABLE(r-type_client
#     ${ClientSRC}/game.client.cpp
# )
# TARGET_INCLUDE_DIRECTORIES(r-type_client PRIVATE . ${raylib_SOURCE_DIR}/src ${asio_SOURCE_DIR}/asio/include)
# TARGET_LINK_LIBRARIES(r-type_client PRIVATE
#     jepengine
#     jepmod
#     raylib
# )

# # game.server

# SET(ServerSRC sample/)
# ADD_EXECUTABLE(r-type_server
#     ${ServerSRC}/game.server.cpp
# )
# TARGET_INCLUDE_DIRECTORIES(r-type_server PRIVATE . ${raylib_SOURCE_DIR}/src ${asio_SOURCE_DIR}/asio/include)
# TARGET_LINK_LIBRARIES(r-type_server PRIVATE
#     jepengine
#     jepmod
#     raylib
# )

# # copy the sprites

# ADD_CUSTOM_COMMAND(TARGET r-type_server POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy
#     "$<TARGET_FILE:r-type_server>"
#     "${CMAKE_SOURCE_DIR}"
# )


# ADD_CUSTOM_COMMAND(TARGET r-type_client POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy
#     "$<TARGET_FILE:r-type_client>"
#     "${CMAKE_SOURCE_DIR}"
# )

# ADD_CUSTOM_COMMAND(TARGET external.client POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy
#     "$<TARGET_FILE:external.client>"
#     "${CMAKE_SOURCE_DIR}"
# )

# ADD_CUSTOM_COMMAND(TARGET external.server POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy
#     "$<TARGET_FILE:external.server>"
#     "${CMAKE_SOURCE_DIR}"
# )
