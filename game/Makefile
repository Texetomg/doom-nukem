# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/14 14:37:36 by bfalmer-          #+#    #+#              #
#    Updated: 2019/03/29 13:54:41 by bfalmer-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem
FLAG = -Wall -Wextra -Werror -g -O
SRC = main.c draw_wall.c fps.c create_struct.c read_map.c vectors_utils.c
INC = -I ../libft/ -I ./includes -I ../framework/SDL2.framework/Versions/A/Headers
LIB = -L ../libft/ -lft 
FRWR = -framework SDL2 -F ../framework/
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
