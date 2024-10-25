##
## EPITECH PROJECT, 2024
## rtype
## File description:
## Makefile
##

AR ?= ar
ARFLAGS ?= rcv

NAME = jepengine
ROOT = .
LIB = $(ROOT)/lib$(NAME).a

CFLAGS += -Wall -Wextra -Wpedantic
CXXFLAGS += -std=c++23
CPPFLAGS += -iquote./include -iquote./include/components -iquote./include/systems

SRCPATH = ./src
COMPONENTS_SRC_PARH = $(SRCPATH)/components
SYSTEMS_SRC_PARH = $(SRCPATH)/systems

SRC =	$(SRCPATH)/Register.cpp							\
		$(COMPONENTS_SRC_PARH)/Position.cpp 			\
		$(COMPONENTS_SRC_PARH)/Drawable.cpp 			\
		$(COMPONENTS_SRC_PARH)/Sprite2DMultiAnim.cpp	\
		$(COMPONENTS_SRC_PARH)/TextDrawable.cpp			\
		$(COMPONENTS_SRC_PARH)/Score.cpp				\
		$(SYSTEMS_SRC_PARH)/DrawSystem.cpp				\
		$(SYSTEMS_SRC_PARH)/Sprite2DMultiAnimSystem.cpp	\
		$(SYSTEMS_SRC_PARH)/TextDrawableSystem.cpp		\
		$(SYSTEMS_SRC_PARH)/ScoreSystem.cpp				\

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
