# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/14 14:37:36 by bfalmer-          #+#    #+#              #
#    Updated: 2019/11/01 17:23:12 by bfalmer-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem
BMP_DIR = bmp_reader
FLAG = -Wall -Wextra -Werror -g -O3
SRC = draw_floor.c draw_ceil.c sound.c main.c draw_minimap.c fps.c create_struct.c read_map.c key_hooks.c \
utils.c sdl_utils.c math_utils.c render.c start_menu.c tab_menu.c hud.c  multiplayer_menu.c \
hud_utils.c menu_utils.c read_map_utils.c load_images.c\
draw_img.c init_client.c $(BMP_DIR)/array_file_type.c $(BMP_DIR)/bmp_info.c \
$(BMP_DIR)/get_blocks.c $(BMP_DIR)/glob_texture_funks.c $(BMP_DIR)/rle_file_type.c \
$(BMP_DIR)/texture_add_funks.c print_text.c
INC = -I ../libft/ \
-I ./includes \
-I ../framework/SDL2.framework/Versions/A/Headers \
-I ../framework/SDL2_mixer.framework/Versions/A/Headers \
-I ../framework/SDL2_ttf.framework/Versions/A/Headers \
-I ../framework/SDL2_image.framework/Versions/A/Headers
LIB = -L ../libft/ -lft 
FRWR = -framework SDL2 -F ../framework \
-framework SDL2_mixer  \
-framework SDL2_ttf \
-framework SDL2_image
OBJS = $(addprefix objects/, $(SRC:.c=.o))
OBJDIR = objects
SRCDIR = src

.PHONY: all clean fclean re git_%

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	make lib_ft
	$(CC) $(FLAG) $(OBJS) $(INC) $(LIB) $(FRWR) -o $(NAME)
	@install_name_tool -change @rpath/SDL2.framework/Versions/A/SDL2 ../framework/SDL2.framework/Versions/A/SDL2 $(NAME)
	@install_name_tool -change @rpath/SDL2_mixer.framework/Versions/A/SDL2_mixer ../framework/SDL2_mixer.framework/Versions/A/SDL2_mixer $(NAME)
	@install_name_tool -change @rpath/SDL2_image.framework/Versions/A/SDL2_image ../framework/SDL2_image.framework/Versions/A/SDL2_image $(NAME)
	@install_name_tool -change @rpath/SDL2_ttf.framework/Versions/A/SDL2_ttf ../framework/SDL2_ttf.framework/Versions/A/SDL2_ttf $(NAME)

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

zip:
	rm -r imgs map2

unzip:
	unzip -q game.zip
	
my_zip:
	zip -r -q game.zip imgs map2
	rm -r imgs map2
