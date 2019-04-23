# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/14 14:37:36 by bfalmer-          #+#    #+#              #
#    Updated: 2019/04/23 12:49:57 by thorker          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem
FLAG = -Wall -Wextra -Werror -g -O3
SRC = main.c draw_minimap.c fps.c create_struct.c read_map.c key_hooks.c utils.c SDL_utils.c menu.c
INC = -I ../libft/ -I ./includes -I ../framework/SDL2.framework/Versions/A/Headers -I ../framework/SDL2_mixer.framework/Versions/A/Headers  -I ../framework/SDL2_ttf.framework/Versions/A/Headers -I ../framework/SDL2_image.framework/Versions/A/Headers
LIB = -L ../libft/ -lft 
FRWR = -framework SDL2 -F ../framework -framework SDL2_mixer  -framework SDL2_ttf -framework SDL2_image
OBJS = $(addprefix objects/, $(SRC:.c=.o))
OBJDIR = objects
SRCDIR = src

.PHONY: all clean fclean re git_%

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	make lib_ft
	$(CC) $(FLAG) $(OBJS) $(INC) $(LIB) $(FRWR) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(FLAG) $(INC) -c $^ -o $@

lib_ft:
	make -C ../libft

clean:
	make -C ../libft/ clean
	rm -f $(OBJS)

fclean:
	rm -f $(OBJS)
	make -C ../libft/ fclean
	rm -f $(NAME)
	
re:
	make fclean
	make

git_%: clean
	git add --all
	git status
	git commit -m "$@"
	git push
