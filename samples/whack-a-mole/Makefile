##
## EPITECH PROJECT, 2024
## R-Type
## File description:
## Makefile
##

CXX ?= g++

BIN = whack-a-mole-game

CPPFLAGS = -iquote ../../include -iquote ./include/ -std=c++23 
LDFLAGS = -L $(JEPGO_BUILD) -l jepengine -l jepmod

SRC = 	game.client.cpp

OBJ = $(SRC:.cpp=.o)

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) -o $(BIN) $(OBJ) $(LDFLAGS)

clean:
	$(RM) -f $(OBJ)

fclean: clean
	$(RM) -f $(BIN)

re: fclean $(BIN)

.PHONY: $(BIN) all clean fclean re