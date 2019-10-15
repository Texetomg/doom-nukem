# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ramory-l <ramory-l@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 14:23:06 by twitting          #+#    #+#              #
#    Updated: 2019/10/15 16:05:15 by ramory-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = map_editor

SRC = ./main.c \
	./putline.c \
	./initedit.c \
	./portals.c \
	./portals_calcs.c \
	./save.c \
	./vertexes.c \
	./buttons.c \
	./save2.c \
	./vertexes_extra.c \
	./vertexes_extra2.c \
	./main_support.c \
	./rules.c

LIB = -L ../libft/ -lft

OBJS = $(SRC:.c=.o)

FLAG = -Wall -Wextra -Werror -Ofast

INC = -I ../libft/ \
	-I ../framework/SDL2.framework/Versions/A/Headers \
	-I ../framework/SDL2_mixer.framework/Versions/A/Headers \
	-I ../framework/SDL2_ttf.framework/Versions/A/Headers \
	-I ../framework/SDL2_image.framework/Versions/A/Headers \
	-I ../kiss_sdl

FRWR = -framework SDL2 -F ../framework \
-framework SDL2_mixer  \
-framework SDL2_ttf \
-framework SDL2_image

all: $(NAME)

$(NAME): $(OBJS) libft kiss_sdl
	$(CC) $(FLAG) $(OBJS) $(INC) $(LIB) $(FRWR) -o $(NAME) -L ../kiss_sdl -l kisssdl
	@install_name_tool -change @rpath/SDL2.framework/Versions/A/SDL2 ../framework/SDL2.framework/Versions/A/SDL2 $(NAME)
	@install_name_tool -change @rpath/SDL2_mixer.framework/Versions/A/SDL2_mixer ../framework/SDL2_mixer.framework/Versions/A/SDL2_mixer $(NAME)
	@install_name_tool -change @rpath/SDL2_image.framework/Versions/A/SDL2_image ../framework/SDL2_image.framework/Versions/A/SDL2_image $(NAME)
	@install_name_tool -change @rpath/SDL2_ttf.framework/Versions/A/SDL2_ttf ../framework/SDL2_ttf.framework/Versions/A/SDL2_ttf $(NAME)

%.o: %.c
	@$(CC) $(FLAG) $(INC) -F ../framework -c $^ -o $@

libft:
	make -C ../libft

kiss_sdl:
	make -C ../kiss_sdl

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f ./save

re: fclean all
