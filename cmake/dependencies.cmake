if(NOT raylib_FOUND)
    CPMAddPackage(
        NAME raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib
        GIT_TAG 5.0
    )
endif()

CPMAddPackage( # header only library, so no need to find_package() of check if FOUND
    NAME asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio
    GIT_TAG asio-1-31-0
)

if(NOT SQLite3_FOUND)
    CPMAddPackage(
        NAME SQLite3
        GIT_REPOSITORY https://github.com/LuaDist/libsqlite3
        GIT_TAG 3.7.7.1
    )
endif()
list(APPEND CMAKE_MODULE_PATH "${SQLite3_SOURCE_DIR}/cmake")

if(NOT SqliteOrm_FOUND)
    CPMAddPackage(
        NAME sqliteorm
        GIT_REPOSITORY https://github.com/fnc12/sqlite_orm
        GIT_TAG v1.9
    )
endif()

# if(NOT Lua_FOUND)
#     CPMAddPackage(
#         NAME Lua
#         GIT_REPOSITORY https://github.com/lua/lua
#         GIT_TAG v5.4.4
#     )
# endif()

# CPMAddPackage(
#     NAME libconfig
#     GIT_REPOSITORY https://github.com/hyperrealm/libconfig
#     GIT_TAG v1.7.3
# )