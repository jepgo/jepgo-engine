##
## EPITECH PROJECT, 2024
## Bootstrap
## File description:
## Makefile
##

SRC	=	src/clientLogic.cpp \
		src/clientTCP.cpp

SRC_S	=	src/serverTCP.cpp \
			src/ParsingFile.cpp

OBJ	=	$(SRC:.cpp=.o)

OBJ_S	=	$(SRC_S:.cpp=.o)

CXX	=	g++

NAME	=	clientTCP

NAME2	=	serverTCP

CPPFLAGS	=	-I /opt/homebrew/include -std=c++20 -lsqlite3 -lconfig++ -lraylib -iquote./include

%.o: %.cpp
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

all:	$(NAME) $(NAME2)

$(NAME):	$(OBJ)
	$(CXX) $(OBJ) -o $(NAME) $(CFLAGS) $(CPPFLAGS)


$(NAME2):	$(OBJ_S)
	$(CXX) $(OBJ_S) -o $(NAME2) $(CFLAGS) $(CPPFLAGS)

clean:
	$(RM) $(OBJ)
	$(RM) $(OBJ_S)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME2)

reset_db:
			$(RM) jepgo.db && sqlite3 Database/jepgo.db < Database/jepgo.sql

re: fclean all

.PHONY: all $(NAME) $(NAME2) clean fclean re