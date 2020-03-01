.PHONY: all, clean, fclean, re

NAME = nculib.so
CC = clang++

FLAGS += -std=c++11 -lncurses
#-Wall -Wextra -Werror
LIBFLAGS = -shared -fPIC

DIR_S = ./src
DIR_O = ./obj
DIR_H = ./inc

SOURCES =

SOURCES += NCULIB.cpp

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Bulid lib NCURSES"
	$(CC) $(LIBFLAGS) $(SRCS) -I $(DIR_H) $(FLAGS) $(SDLFLAGS) -o $(NAME)

$(DIR_O)/%.o: $(DIR_S)/%.cpp
	@echo "Compile lib NCURSES"
	@mkdir -p $(DIR_O)
	$(CC) $(FLAGS) -I $(DIR_H) -o $@ -c $<

clean:
	@echo "Clean objective files"
	@rm -f $(OBJS)
	@rm -rf $(DIR_O)

fclean: clean
	@echo "Remove lib"
	@rm -f $(NAME)

re: fclean all
