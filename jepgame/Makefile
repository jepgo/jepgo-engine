##
## EPITECH PROJECT, 2024
## rtype
## File description:
## Makefile
##

AR ?= ar
ARFLAGS ?= rcv

NAME = jepgame
ROOT = ..
LIB = $(ROOT)/lib$(NAME).a

CFLAGS += -Wall -Wextra -Wpedantic -std=c++17
CPPFLAGS += -iquote./ -iquote$(ROOT)
LDFLAGS += -lsfml-graphics

SRC = service/UDP.cpp \
	service/Builder.cpp \
	service/Connections.cpp \
	gamemaker/hardcoded.cpp \
	gamemaker/Client.cpp \
	gamemaker/Server.cpp \

OBJS = $(SRC:.cpp=.o)

%.o: %.cpp
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

lib: $(LIB)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $(LIB) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(LIB)

re: fclean lib

.PHONY: re fclean clean lib

