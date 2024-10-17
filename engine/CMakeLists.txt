CMAKE_MINIMUM_REQUIRED(VERSION 3.14) # pi

ADD_LIBRARY(jepengine STATIC
    src/Register.cpp
	src/Components.cpp
	src/HitSystem.cpp
	src/MoveSystem.cpp
	src/DrawSystem.cpp
	src/AnimationSpriteSystem.cpp
	src/TestGame.cpp
	src/Controllable.cpp
	src/Module.cpp
	src/Shoot.cpp
	src/ExplosionSystem.cpp
	src/Game.cpp
	src/Enemy.cpp
	src/Text.cpp
	src/GameSystem.cpp
	src/DestroyerSystem.cpp
	src/LoopMoveSystem.cpp
	src/ShortAnimationSystem.cpp
	src/Animation2TimeSystem.cpp
	src/MoveToPlayerSystem.cpp
	src/MoveToPlayerTimeSystem.cpp
	src/BombGenerationTimeSystem.cpp
	src/BombGenerationSystem.cpp
	src/Raylib.cpp
	src/DetachModulesSystem.cpp
	src/MoveToSystem.cpp
	src/MoveTo.cpp
	src/DeathSystem.cpp
	src/AutoShootSystem.cpp
	src/Menu.cpp
	src/AnimLine.cpp
	src/LogIcon.cpp
	src/Button.cpp
	src/MainGame.cpp
	src/RaylibPlus.cpp
	src/Draw3DSystem.cpp
	src/Rotation3DSystem.cpp
)

TARGET_INCLUDE_DIRECTORIES(jepengine PRIVATE ./include)
TARGET_LINK_LIBRARIES(jepengine raylib)

add_executable(solo
    src/Register.cpp
    src/Components.cpp
    src/HitSystem.cpp
    src/MoveSystem.cpp
    src/DrawSystem.cpp
    src/AnimationSpriteSystem.cpp
    src/TestGame.cpp
    src/Controllable.cpp
    src/Module.cpp
    src/Shoot.cpp
    src/ExplosionSystem.cpp
    src/Game.cpp
    src/Enemy.cpp
    src/Text.cpp
    src/GameSystem.cpp
    src/DestroyerSystem.cpp
    src/LoopMoveSystem.cpp
    src/ShortAnimationSystem.cpp
    src/Animation2TimeSystem.cpp
    src/MoveToPlayerSystem.cpp
    src/MoveToPlayerTimeSystem.cpp
    src/BombGenerationTimeSystem.cpp
    src/BombGenerationSystem.cpp
    src/Raylib.cpp
    src/DetachModulesSystem.cpp
    src/MoveToSystem.cpp
    src/MoveTo.cpp
    src/DeathSystem.cpp
    src/AutoShootSystem.cpp
    src/Menu.cpp
    src/AnimLine.cpp
    src/LogIcon.cpp
    src/Button.cpp
    src/MainGame.cpp
    src/RaylibPlus.cpp
    src/Draw3DSystem.cpp
    src/Rotation3DSystem.cpp
    src/main.cpp
)

target_include_directories(solo PRIVATE include ${raylib_SOURCE_DIR}/src)
target_link_libraries(solo PRIVATE raylib)

ADD_CUSTOM_COMMAND(TARGET solo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "$<TARGET_FILE:solo>"
    "${CMAKE_SOURCE_DIR}"
)