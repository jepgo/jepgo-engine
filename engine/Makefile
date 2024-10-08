##
## EPITECH PROJECT, 2024
## rtype
## File description:
## Makefile
##

AR ?= ar
ARFLAGS ?= rcv

NAME = jepengine
ROOT = ..
LIB = $(ROOT)/lib$(NAME).a

CFLAGS += -Wall -Wextra -Wpedantic
CXXFLAGS += -std=c++23
CPPFLAGS += -iquote./include

SRC =	src/Register.cpp	\
		src/Components.cpp	\
		src/HitSystem.cpp	\
		src/MoveSystem.cpp	\
		src/DrawSystem.cpp	\
		src/AnimationSpriteSystem.cpp	\
		src/TestGame.cpp	\
		src/Controllable.cpp	\
		src/Module.cpp	\
		src/Shoot.cpp	\
		src/ExplosionSystem.cpp	\
		src/Game.cpp	\
		src/Enemy.cpp	\
		src/Text.cpp	\
		src/GameSystem.cpp	\
		src/DestroyerSystem.cpp	\
		src/LoopMoveSystem.cpp	\
		src/ShortAnimationSystem.cpp	\
		src/Animation2TimeSystem.cpp	\
		src/MoveToPlayerSystem.cpp	\
		src/MoveToPlayerTimeSystem.cpp	\
		src/BombGenerationTimeSystem.cpp	\
		src/BombGenerationSystem.cpp	\
		src/Raylib.cpp	\

OBJS = $(SRC:.cpp=.o)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

lib: $(LIB)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $(LIB) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(LIB)

re: fclean lib

.PHONY: re fclean clean lib
