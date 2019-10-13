# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ramory-l <ramory-l@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/14 14:37:36 by bfalmer-          #+#    #+#              #
#    Updated: 2019/10/13 14:54:25 by ramory-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = server
FLAG = -Wall -Wextra -Werror -g -O3
SRC = server.c
INC = -I ../../libft/ \
-I ../includes \
-I ../../framework/SDL2.framework/Versions/A/Headers \
-I ../../framework/SDL2_mixer.framework/Versions/A/Headers \
-I ../../framework/SDL2_ttf.framework/Versions/A/Headers \
-I ../../framework/SDL2_image.framework/Versions/A/Headers
LIB = -L ../../libft/ -lft 
FRWR = -framework SDL2 -F ../../framework \
-framework SDL2_mixer  \
-framework SDL2_ttf \
-framework SDL2_image
OBJS = $(addprefix objects/, $(SRC:.c=.o))
OBJDIR = objects
SRCDIR = .

.PHONY: all clean fclean re git_%

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	make lib_ft
	$(CC) $(FLAG) $(OBJS) $(INC) $(LIB) $(FRWR) -o $(NAME)
	@install_name_tool -change @rpath/SDL2.framework/Versions/A/SDL2 ../../framework/SDL2.framework/Versions/A/SDL2 $(NAME)
	@install_name_tool -change @rpath/SDL2_mixer.framework/Versions/A/SDL2_mixer ../../framework/SDL2_mixer.framework/Versions/A/SDL2_mixer $(NAME)
	@install_name_tool -change @rpath/SDL2_image.framework/Versions/A/SDL2_image ../../framework/SDL2_image.framework/Versions/A/SDL2_image $(NAME)
	@install_name_tool -change @rpath/SDL2_ttf.framework/Versions/A/SDL2_ttf ../../framework/SDL2_ttf.framework/Versions/A/SDL2_ttf $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(FLAG) $(INC) -c $^ -o $@

lib_ft:
	make -C ../../libft

clean:
	make -C ../../libft/ clean
	rm -f $(OBJS)

fclean:
	rm -f $(OBJS)
	make -C ../../libft/ fclean
	rm -f $(NAME)
	
re:
	make fclean
	make

frame:
	cp -r ../../framework ~/Library/Frameworks

git_%: clean
	git add --all
	git status
	git commit -m "$@"
	git push
