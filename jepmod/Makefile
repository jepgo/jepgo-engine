##
## EPITECH PROJECT, 2024
## rtype
## File description:
## Makefile
##

AR ?= ar
ARFLAGS ?= rcv

NAME = jepmod
ROOT = ..
LIB = $(ROOT)/lib$(NAME).a

CFLAGS += -Wall -Wextra -Wpedantic
CXXFLAGS += -std=c++23
CPPFLAGS += -iquote./

SRC = DLLoader.cpp

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

