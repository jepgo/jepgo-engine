##
## EPITECH PROJECT, 2024
## R-TYPE
## File description:
## Makefile
##

CXX = g++
BIN = whack-a-mole-game

FILES_UNIT	=	*.gc*

CFLAGS += -Wall -Wextra -Wpedantic -std=c++20
INC_ENGINE = -iquote./engine/include/ -iquote./engine/include/components -iquote./engine/include/systems
CPPFLAGS += -iquote./include $(INC_ENGINE)
LIBPATH += ./engine/
LDFLAGS += -lraylib -L$(LIBPATH) -ljepengine

# Source files

MAIN	=	./src/main.cpp

SRC_PATH =	./src/
SRC =	$(SRC_PATH)/WhackAMole.cpp	\
		$(SRC_PATH)/Game.cpp		\

OBJS += $(SRC:.cpp=.o)
MAIN_OBJ	=	$(MAIN:.cpp=.o)

# Methods

%.o: %.cpp
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

all: $(BIN)

$(BIN): $(OBJS) $(MAIN_OBJ)
	$(MAKE) -C ./engine
	$(CXX) $(OBJS) $(MAIN_OBJ) -o $(BIN) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)

clean:
	$(MAKE) -C ./engine clean
	$(RM) $(OBJS) $(MAIN_OBJ) $(FILES_UNIT)

fclean: clean
	$(MAKE) -C ./engine fclean
	$(RM) $(BIN) $(BIN_TESTS)

re: fclean all

.PHONY: all $(BIN) clean fclean re
