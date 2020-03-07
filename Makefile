.PHONY: all, clean, fclean, re

NAME = Nibbler
CC = clang++

FLAGS += -Wall -Wextra -Werror -std=c++14

DIR_C = ./core
DIR_S = $(DIR_C)/src
DIR_O = $(DIR_C)/obj
DIR_H = $(DIR_C)/inc

NCUL_DIR = ./ncurses
SFML_DIR = ./sfml
SDL_DIR = ./sdl

SOURCES =

SOURCES += main.cpp
SOURCES += Game.cpp
SOURCES += Snake.cpp

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.cpp=.o))

all: $(NAME)

$(NAME): build_libs  $(OBJS)
	@echo "Bulid Nibbler"
	$(CC) $(SRCS) -I $(DIR_H) $(FLAGS) -o $(NAME) -ldl

build_libs:
	@make -C $(NCUL_DIR)
	@cp ./ncurses/nculib.so ./
	@make -C $(SFML_DIR)
	@cp ./sfml/sfmllib.so ./


$(DIR_O)/%.o: $(DIR_S)/%.cpp
	@echo "Compile Nibbler"
	@mkdir -p $(DIR_O)
	$(CC) $(FLAGS) -I $(DIR_H) -o $@ -c $<

clean:
	@echo "Clean objective files"
	@rm -f $(OBJS)
	@rm -rf $(DIR_O)
	@make clean -C $(NCUL_DIR)
	@make clean -C $(SFML_DIR)

fclean: clean
	@echo "Remove Nibbler"
	@rm -f $(NAME)
	@make fclean -C $(NCUL_DIR)
	@make fclean -C $(SFML_DIR)
	@rm -rf nculib.so
	@rm -rf sfmllib.so

re: fclean all
