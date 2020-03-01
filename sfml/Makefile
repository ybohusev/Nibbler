.PHONY: all, clean, fclean, re

NAME = sfmllib.so
CC = clang++

FLAGS += -Wall -Wextra -Werror -std=c++14
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-audio
LIBFLAGS = -shared -fPIC -rpath $(PWD)/sfml/$(SFML_FRM) -nostartfiles -dynamiclib

DIR_S = ./src
DIR_O = ./obj
DIR_H = ./inc

SFML_DIR 	=	sfml
SFML_INC 	=	$(SFML_DIR)/SFML-2.5.0-macOS-clang/include
SFML_FRM	=	$(SFML_DIR)/SFML-2.5.0-macOS-clang/Frameworks
SFML_LINK 	=	-F$(SFML_FRM) -framework SFML -framework sfml-graphics -framework sfml-window -framework sfml-system -framework sfml-audio

SOURCES =

SOURCES += SFML.cpp

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.cpp=.o))

all: sfml $(NAME)

$(NAME): $(OBJS)
	@echo "Bulid lib"
	$(CC) $(LIBFLAGS) $(SRCS) $(SFML_LINK) -I $(DIR_H) -I $(SFML_INC) $(FLAGS) -o $(NAME)

$(DIR_O)/%.o: $(DIR_S)/%.cpp
	@echo "Compile lib"
	@mkdir -p $(DIR_O)
	$(CC) $(FLAGS) -I $(DIR_H) -I $(SFML_INC) -o $@ -c $<

sfml_download:
	curl -OL http://www.sfml-dev.org/files/SFML-2.5.0-macOS-clang.tar.gz
	tar zxvfC 'SFML-2.5.0-macOS-clang.tar.gz' $(SFML_DIR)
	rm -rf 'SFML-2.5.0-macOS-clang.tar.gz'
	cd $(SFML_FRM) && cp -R ../extlibs/* ./
	echo "\033[32m[ ✔ ] "SFML downloaded" \033[0m"

sfml:
	mkdir -p $(SFML_DIR)
	test -d SFML/SFML-2.5.0-macOS-clang && echo "\033[31m[ × ] "SFML already exist" \033[0m" || make sfml_download


clean:
	@echo "Clean objective files"
	@rm -f $(OBJS)
	@rm -rf $(DIR_O)
	@rm -rf $(SFML_DIR)

fclean: clean
	@echo "Remove lib"
	@rm -f $(NAME)

re: fclean all
