.PHONY: all, clean, fclean, re

NAME = sdllib.so
CC = clang++

FLAGS += `sdl2-config --cflags`
SDLFLAGS = `sdl2-config --libs` -lSDL2_image
LIBFLAGS = -shared -fPIC

DIR_S = ./src
DIR_O = ./obj
DIR_H = ./inc

SOURCES =

SOURCES += SDLLIB.cpp

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Bulid lib SDL"
	$(CC) $(LIBFLAGS) $(SRCS) -I $(DIR_H) $(FLAGS) $(SDLFLAGS) -o $(NAME)

$(DIR_O)/%.o: $(DIR_S)/%.cpp
	@echo "Compile lib SDL"
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
