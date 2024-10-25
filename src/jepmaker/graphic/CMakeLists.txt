cmake_minimum_required(VERSION 3.14) # pi

file(GLOB files "./*.cpp")
foreach(file ${files})
    get_filename_component(basename ${file} NAME_WLE)
    string(CONCAT finalName "jepgo.graphic." ${basename})
    project(${finalName})
    message(${finalName})
    # message(${file})
    add_library(${finalName} SHARED ${file})
    target_include_directories(${finalName} PRIVATE ../../../include)
    target_link_libraries(${finalName} jepengine jepmod raylib)
    # string(CONCAT zizi "<TARGET_FILE:" ${finalName} ">")
    ADD_CUSTOM_COMMAND(TARGET ${finalName} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE:${finalName}>"
        "${CMAKE_BINARY_DIR}"
    )
endforeach()