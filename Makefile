NAME = cube3D

CC = gcc
#CFLAGS = -Wall -Werror -Wextra -g -I./includes -fsanitize=address
CFLAGS = -g -I./includes
EXTRA_FLAGS = -Imlx_linux -O3 -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -fsanitize=address

RM = rm -f

#$(VERBOSE).SILENT:

HEADER = header.h

INC = -I ./includes

SRC_PATH = ./sources

OBJ_PATH = ./objects

SRC_NAME =	main.c							\
			ft_calloc.c						\
			ft_strncmp.c					\
			ft_strlen.c						\
			get_map_textures.c				\
			get_map_textures_rgb.c			\
			check_textures.c				\
			check_file.c					\
			check_file_type.c				\
			map.c							\
			map_resizer.c					\
			check_map.c						\
			check_map_walls.c				\
			check_map_elements.c			\
			get_map_content.c				\
			get_player_info.c				\
			get_map_utils.c					\
			get_next_line.c					\
			free_memory.c					\
			error_msgs.c					\
			draw_utils.c					\
			math_utils.c					\
			utils.c							\
			render_scene_2d.c				\
			render_scene_3d.c				\
			player.c						\
			ray.c							\
			raycast.c						\
			time.c							\
			key_controls.c

OBJS = $(addprefix $(OBJ_PATH)/, $(SRC_NAME:.c=.o))

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))

all: $(NAME)

$(NAME) : $(OBJS)
	cd mlx_linux && make && cd ..
	$(CC) $(CFLAGS) $(OBJS) $(INC) $(EXTRA_FLAGS) -o $(NAME)
	@echo "\033[1;36m[cub3D COMPILED]\033[0m"

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	mkdir -p objects
	$(CC) -c $(CFLAGS) $(EXTRA_FLAGS) $(INCLUDES) $< -o $@

norminette:
	clear
	@./norm.sh

clean:
	cd mlx_linux && make clean && cd ..
	rm -rf $(OBJ_PATH)
	@echo "\033[1;33mAll $(NAME).o files are removed\033[0m"

fclean: clean
	rm -f $(NAME)
	@echo "\033[1;31m$(NAME) is deleted\033[0m"

re: fclean all

.PHONY: all clean fclean re force norminette
