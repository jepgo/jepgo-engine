##
## EPITECH PROJECT, 2024
## R-TYPE
## File description:
## Makefile
##

CXX = g++
BIN = R-TYPE
BIN_TESTS	=	build_tests

FILES_UNIT	=	*.gc*

CFLAGS += -Wall -Wextra -Wpedantic -std=c++17
CPPFLAGS += -iquote./engine/include
LDFLAGS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Source files

MAIN	=	engine/src/main.cpp \

SRC =	engine/src/Register.cpp	\
		engine/src/Components.cpp	\
		engine/src/HitSystem.cpp	\
		engine/src/MoveSystem.cpp	\
		engine/src/DrawSystem.cpp	\
		engine/src/AnimationSpriteSystem.cpp	\
		engine/src/TestGame.cpp	\
		engine/src/Controllable.cpp	\
		engine/src/Module.cpp	\
		engine/src/Shoot.cpp	\
		engine/src/ExplosionSystem.cpp	\
		engine/src/Game.cpp	\
		engine/src/Enemy.cpp	\
		engine/src/Text.cpp	\


OBJS += $(SRC:.cpp=.o)

MAIN_OBJ	=	$(MAIN:.cpp=.o)

TRC	=	tests/test.cpp

CFLAGS_CRITERION	=	--coverage -lcriterion

# Methods

%.o: %.cpp
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

all: $(BIN)

$(BIN): $(OBJS) $(MAIN_OBJ)
	$(CXX) $(OBJS) $(MAIN_OBJ) -o $(BIN) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)
	$(RM) $(MAIN_OBJ)
	$(RM) $(FILES_UNIT)

fclean: clean
	$(RM) $(BIN)
	$(RM) $(BIN_TESTS)

build_tests:	fclean
				$(CXX) -o $(BIN_TESTS) $(TRC) $(SRC) $(CFLAGS) $(CPPFLAGS) $(CFLAGS_CRITERION)

tests_run:	$(BIN_TESTS)
			./$(BIN_TESTS)

re: fclean all

.PHONY: all $(BIN) clean fclean re
