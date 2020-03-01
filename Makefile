.PHONY: all, clean, fclean, re

NAME = Nibbler
CC = clang++

FLAGS += -Wall -Wextra -Werror -std=c++14

DIR_C = ./core
DIR_S = $(DIR_C)/src
DIR_O = $(DIR_C)/obj
DIR_H = $(DIR_C)/inc

NCUL_DIR = ./sfml
SDL_DIR = ./sdl
NCUL_DIR = ./ncurses

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
	#@make -C $(SFML_DIR)
	#@make -C $(SDL_DIR)
	@make -C $(NCUL_DIR)
	#@cp ./sfml/sfmllib.so ./
	#@cp ./sdl/sdllib.so ./
	@cp ./ncurses/nculib.so ./


$(DIR_O)/%.o: $(DIR_S)/%.cpp
	@echo "Compile Nibbler"
	@mkdir -p $(DIR_O)
	$(CC) $(FLAGS) -I $(DIR_H) -o $@ -c $<

clean:
	@echo "Clean objective files"
	@rm -f $(OBJS)
	@rm -rf $(DIR_O)
	#@make clean -C $(SFML_DIR)
	#@make clean -C $(SDL_DIR)
	@make clean -C $(NCUL_DIR)

fclean: clean
	@echo "Remove Nibbler"
	@rm -f $(NAME)
	#@make fclean -C $(SFML_DIR)
	#@make fclean -C $(SDL_DIR)
	@make fclean -C $(NCUL_DIR)
	#@rm -rf sfmllib.so
	#@rm -rf sdllib.so
	@rm -rf nculib.so

re: fclean all
