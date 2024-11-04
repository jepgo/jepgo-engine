CMAKE_MINIMUM_REQUIRED(VERSION 3.14) # pi

PROJECT(jepgo)

ADD_EXECUTABLE(jepgo
    main.cpp
)

TARGET_INCLUDE_DIRECTORIES(jepgo PRIVATE ../../include)
target_link_libraries(jepgo jepengine jepmod)

set(SOURCE_FOLDER "${CMAKE_SOURCE_DIR}/src/jepcli/helper")
set(DESTINATION_FOLDER "${CMAKE_BINARY_DIR}/helper")

ADD_CUSTOM_COMMAND(TARGET jepgo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${SOURCE_FOLDER}"
    "${DESTINATION_FOLDER}"
)

ADD_CUSTOM_COMMAND(TARGET jepgo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "$<TARGET_FILE:jepgo>"
    "${CMAKE_BINARY_DIR}"
)

