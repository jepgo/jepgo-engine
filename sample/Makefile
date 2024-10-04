##
## EPITECH PROJECT, 2024
## R-TYPE
## File description:
## Makefile
##

CXX ?= g++
RM ?= rm -rf
BIN = client
ROOT = ..

CFLAGS += -Wall -Wextra -Wpedantic -std=c++23
CXXFLAGS +=
CPPFLAGS += -iquote$(ROOT) -iquote.
LDLIBS += -lsfml-graphics -lsfml-window -lsfml-system -lraylib -ljepgame -ljepengine -ljepmod
LDFLAGS += -L$(ROOT)

MAIN = game.client.cpp
SRC +=

MAINOBJ = $(MAIN:.cpp=.o)
OBJS += $(SRC:.cpp=.o)

%.o: %.cpp
	$(CXX) $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

all: $(BIN)

$(BIN): $(OBJS) $(MAINOBJ)
	$(CXX) $(OBJS) $(MAINOBJ) -o $(BIN) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) $(OBJS)
	$(RM) $(MAINOBJ)

fclean: clean
	$(RM) $(BIN)

re: fclean all

.PHONY: all clean fclean re
