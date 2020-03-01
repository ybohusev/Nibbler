.PHONY: all, clean, fclean, re

NAME = sfmllib.so
CC = clang++

FLAGS += -Wall -Wextra -Werror
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-audio
LIBFLAGS = -shared -fPIC

DIR_S = ./src
DIR_O = ./obj
DIR_H = ./inc

SOURCES =

SOURCES += SFML.cpp

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Bulid lib"
	$(CC) $(LIBFLAGS) $(SRCS) -I $(DIR_H) $(FLAGS) $(SFMLFLAGS) -o $(NAME)

$(DIR_O)/%.o: $(DIR_S)/%.cpp
	@echo "Compile lib"
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
